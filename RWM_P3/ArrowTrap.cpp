#include <ArrowTrap.h>

ArrowTrap::ArrowTrap(b2World* world, 
			 b2Vec2 dimensions, 
			 b2Vec2 position, 
			 SDL_Renderer* renderer,
			 int type) 
	: m_renderer(renderer), 
	m_dimensions(dimensions),
	m_type(type),
	canFire(false),
	m_count(0),
	hasFired(false)
{
	if (m_type == 24)
	{
		m_texture = TileBase::getBase()->m_textureArrowTrapLeft;
		flipType = SDL_FLIP_NONE;
	}
	else if (m_type == 23)
	{
		m_texture = TileBase::getBase()->m_textureArrowTrapRight;
		flipType = SDL_FLIP_HORIZONTAL;
	}
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -(position.y + 50) * PIXELSTOMETRES);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.userData = this;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((m_dimensions.x/2) * PIXELSTOMETRES, (m_dimensions.y/2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
//	m_fixtureDef.filter.groupIndex = -500;
	m_fixtureDef.userData = "arrowTrap";
	m_body->CreateFixture(&m_fixtureDef);

	if (24 == m_type)
	{
		m_sensorShape.SetAsBox((CONSTANTS::ARROW_TRIGGER_DISTANCE / 2) * PIXELSTOMETRES, 
			((m_dimensions.y / 2) - 10) * PIXELSTOMETRES, b2Vec2(-((CONSTANTS::ARROW_TRIGGER_DISTANCE / 2) + (m_dimensions.x / 2)) * PIXELSTOMETRES, 0), 0);
	}
	else if (23 == m_type)
	{
		m_sensorShape.SetAsBox((CONSTANTS::ARROW_TRIGGER_DISTANCE / 2) * PIXELSTOMETRES, 
			((m_dimensions.y / 2) - 10) * PIXELSTOMETRES, b2Vec2(((CONSTANTS::ARROW_TRIGGER_DISTANCE / 2) + (m_dimensions.x / 2)) * PIXELSTOMETRES, 0), 0);
	}

	m_sensorDef.shape = &m_sensorShape;
	m_sensorDef.isSensor = true;
	m_sensorDef.userData = "arrowSensor";
	m_body->CreateFixture(&m_sensorDef);
	m_arrow = NULL;
}


ArrowTrap::~ArrowTrap(void)
{
	for (b2Fixture* f = m_body->GetFixtureList(); f; )
	{
		b2Fixture* fixtureToDestroy = f;
		f = f->GetNext();
		m_body->DestroyFixture( fixtureToDestroy );
	}	
	
	m_body->GetWorld()->DestroyBody(m_body);
	if(m_arrow != NULL)
	{
		
		delete m_arrow;		
	}
}

void ArrowTrap::Render(b2Vec2 offset) 
{
	if (canFire)
	{
		m_count++;
	}

	if (canFire && !hasFired && m_count > 50)
	{
		if (24 == m_type)
		{
			m_arrow = new Arrow(m_body->GetWorld(), b2Vec2(40, 30), b2Vec2(m_body->GetWorldCenter().x - (50 * PIXELSTOMETRES), m_body->GetWorldCenter().y), m_renderer, b2Vec2(-75, 0));
		}
		else if (23 == m_type)
		{
			m_arrow = new Arrow(m_body->GetWorld(), b2Vec2(40, 30), b2Vec2(m_body->GetWorldCenter().x + (50 * PIXELSTOMETRES), m_body->GetWorldCenter().y), m_renderer, b2Vec2(75, 0));
		}
		SoundManager::getSoundManager()->PlayArrowFire();
		hasFired = true;
	}
	if (hasFired)
	{
		m_arrow->Render(offset);
	}

	SDL_Rect stretchRect;
	if (hasFired)
	{
		stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (m_dimensions.x/2) - offset.x;
		stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (m_dimensions.y/2) + offset.y;
		stretchRect.w = m_dimensions.x;
		stretchRect.h = m_dimensions.y;
		SDL_RenderCopyEx ( m_renderer, m_texture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}
	else
	{
		stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (m_dimensions.x/2) - offset.x;
		stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (m_dimensions.y/2) + offset.y;
		stretchRect.w = m_dimensions.x;
		stretchRect.h = m_dimensions.y;
		SDL_Rect stretchRect2;
		stretchRect2.x = 0;
		if (flipType == SDL_FLIP_NONE)
		{
			stretchRect2.x = stretchRect.x -25;
		}
		else
		{
			stretchRect2.x = stretchRect.x + 42;
		}
		stretchRect2.y = stretchRect.y + 16;
		stretchRect2.w = 33;
		stretchRect2.h = 18;
		SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_textureArrowHead, NULL, &stretchRect2, 0, NULL, flipType );
		SDL_RenderCopyEx ( m_renderer, m_texture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}
}

b2Body* ArrowTrap::GetBody() 
{
	return m_body;
}

void ArrowTrap::FireArrow()
{
	if (!canFire)
	{
		canFire = true;
	}
}