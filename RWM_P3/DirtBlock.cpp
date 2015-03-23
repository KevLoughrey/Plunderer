#include <DirtBlock.h>

DirtBlock::DirtBlock()
{
}

DirtBlock::DirtBlock(b2World* world, 
					 b2Vec2 dimensions, 
					 b2Vec2 position, 
					 SDL_Renderer* renderer,
					 int type)
	: m_isBodyDestroyed(false)
{	
	m_renderer = renderer; 
	m_dimensions = dimensions;
	m_alive = true;
	m_numParticles = 30;//CONSTANTS::BLOCK_EXPLOSION_PARTICLES;
	m_blockType = type;

	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.userData = this;
	m_body = world->CreateBody(&m_bodyDef);
	m_shape.SetAsBox((m_dimensions.x/2) * PIXELSTOMETRES, (m_dimensions.y/2) * PIXELSTOMETRES);
	
	m_fixtureDef.friction = 1;
	if (type == 0)
	{
		m_fixtureDef.userData = "block";
	}
	else if (type == 60)
	{
		m_fixtureDef.userData = "solidBlock";
	}
	m_fixtureDef.filter.groupIndex  = -1000;
	m_fixtureDef.shape = &m_edgeShape;

	m_edgeShape.Set(b2Vec2(m_shape.GetVertex(0).x + (10*PIXELSTOMETRES), 
						   m_shape.GetVertex(0).y), 
					b2Vec2(m_shape.GetVertex(1).x - (10*PIXELSTOMETRES), 
						   m_shape.GetVertex(1).y));
	m_fixture = m_body->CreateFixture(&m_fixtureDef);
	
	m_edgeShape.Set(b2Vec2(m_shape.GetVertex(1).x, 
						   m_shape.GetVertex(1).y), 
					b2Vec2(m_shape.GetVertex(2).x, 
						   m_shape.GetVertex(2).y));
	m_fixture = m_body->CreateFixture(&m_fixtureDef);

	m_edgeShape.Set(b2Vec2(m_shape.GetVertex(2).x - (10*PIXELSTOMETRES),
						   m_shape.GetVertex(2).y), 
					b2Vec2(m_shape.GetVertex(3).x + (10*PIXELSTOMETRES), 
						   m_shape.GetVertex(3).y));
	m_fixture = m_body->CreateFixture(&m_fixtureDef);

	m_edgeShape.Set(b2Vec2(m_shape.GetVertex(3).x, 
						   m_shape.GetVertex(3).y), 
					b2Vec2(m_shape.GetVertex(0).x, 
						   m_shape.GetVertex(0).y));
	m_fixture = m_body->CreateFixture(&m_fixtureDef);
}

DirtBlock::~DirtBlock()
{
	if (!m_isBodyDestroyed)
	{
		for (b2Fixture* f = m_body->GetFixtureList(); f; )
		{
			b2Fixture* fixtureToDestroy = f;
			f = f->GetNext();
			m_body->DestroyFixture( fixtureToDestroy );
		}

		m_body->GetWorld()->DestroyBody(m_body);
	}
	for (int i = 0; i < m_blockBits.size(); ++i)
	{
		delete m_blockBits.at(i);
	}
}

void DirtBlock::Render(b2Vec2 offset) 
{ 
	if (m_alive) 
	{
		SDL_Rect stretchRect;
		stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS) - (m_dimensions.x/2) - offset.x;
		stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (m_dimensions.y/2) + offset.y;
		stretchRect.w = m_dimensions.x;
		stretchRect.h = m_dimensions.y;

		if (0 == m_blockType || m_blockType == 60)
		{
			SDL_RenderCopyEx( m_renderer, TileBase::getBase()->m_textureBlock, NULL, &stretchRect, m_body->GetAngle()*RADTODEG , NULL, SDL_RendererFlip::SDL_FLIP_NONE );
		}
		/*else
		{
			SDL_RenderCopyEx( m_renderer, TileBase::getBase()->m_text, NULL, &stretchRect, m_body->GetAngle()*TORADIANS, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
		}*/
	}

	for (int i = 0; i < m_blockBits.size(); ++i)
	{
		m_blockBits.at(i)->Draw(offset);
	}
}

void DirtBlock::Destroy()
{
	m_isBodyDestroyed = true;
	if (m_alive)
	{
		for (int i = 0; i < m_numParticles; ++i)
		{
			m_blockBits.push_back(new BlockParticles(m_body->GetWorldCenter(), m_renderer,1));
		}
		for (b2Fixture* f = m_body->GetFixtureList(); f; )
		{
			b2Fixture* fixtureToDestroy = f;
			f = f->GetNext();
			m_body->DestroyFixture( fixtureToDestroy );
		}
		
		m_body->GetWorld()->DestroyBody(m_body);
		m_alive=false;
	}
}

bool DirtBlock::ShouldRemove()
{
	return !m_alive && 0 == m_blockBits.size();
}
b2Body* DirtBlock::GetBody()
{
	return m_body;
}
void DirtBlock::DestroyBody()
{
	m_isBodyDestroyed = true;
	for (b2Fixture* f = m_body->GetFixtureList(); f; )
	{
		b2Fixture* fixtureToDestroy = f;
		f = f->GetNext();
		m_body->DestroyFixture( fixtureToDestroy );
	}
		
	m_body->GetWorld()->DestroyBody(m_body);
}
void DirtBlock::Update(double deltatime)
{
	
	for (int i = 0; i < m_blockBits.size(); ++i)
	{
		m_blockBits.at(i)->Update(deltatime);
		if (!m_blockBits.at(i)->isAlive())
		{
			m_blockBits.at(i)->Destroy();
			m_blockBits.erase(m_blockBits.begin() + i);
		}
	}
}

