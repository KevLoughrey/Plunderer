#include <Ladder.h>

Ladder::Ladder(b2World* world, 
			   b2Vec2 dimensions, 
			   b2Vec2 position, 
			   SDL_Renderer* renderer) 
	: m_renderer(renderer), 
	m_dimensions(dimensions)
{
	position.y = position.y + 50;

	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.userData = this;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((m_dimensions.x/2) * PIXELSTOMETRES, (m_dimensions.y/2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.friction = 0;
	m_fixtureDef.filter.groupIndex = -100;
	m_fixtureDef.userData = "ladder";
	m_body->CreateFixture(&m_fixtureDef);
	
	m_leftSensorShape.SetAsBox(5 * PIXELSTOMETRES, (m_dimensions.y/2) * PIXELSTOMETRES, b2Vec2(-10 * PIXELSTOMETRES, 0), 0);
	m_leftSensorDef.shape = &m_leftSensorShape;
	m_leftSensorDef.isSensor = true;
	m_leftSensorDef.userData = "ladderLeftSensor";
	m_body->CreateFixture(&m_leftSensorDef);

	m_rightSensorShape.SetAsBox(5 * PIXELSTOMETRES, (m_dimensions.y/2) * PIXELSTOMETRES, b2Vec2(10 * PIXELSTOMETRES, 0), 0);
	m_rightSensorDef.shape = &m_rightSensorShape;
	m_rightSensorDef.isSensor = true;
	m_rightSensorDef.userData = "ladderRightSensor";
	m_body->CreateFixture(&m_rightSensorDef);
}

Ladder::~Ladder() 
{
	for (b2Fixture* f = m_body->GetFixtureList(); f; )
	{
		b2Fixture* fixtureToDestroy = f;
		f = f->GetNext();
		m_body->DestroyFixture( fixtureToDestroy );
	}
	m_body->GetWorld()->DestroyBody(m_body);
}

void Ladder::Render(b2Vec2 offset) 
{
	SDL_Rect stretchRect;
	stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (m_dimensions.x/2) - offset.x;
	stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (m_dimensions.y/2) + offset.y;
	stretchRect.w = m_dimensions.x;
	stretchRect.h = m_dimensions.y;
	SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_textureLadder, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}