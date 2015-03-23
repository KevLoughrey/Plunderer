#include <Arrow.h>

Arrow::Arrow(b2World* world, 
			 b2Vec2 dimensions, 
			 b2Vec2 position, 
			 SDL_Renderer* renderer,
			 b2Vec2 velocity) 
	: m_renderer(renderer), 
	m_dimensions(dimensions),
	m_world(world),
	m_broken(false)
{
	(velocity.x < 0) ?
		m_texture = TileBase::getBase()->m_textureArrowLeft
	: m_texture = TileBase::getBase()->m_textureArrowRight;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(position.x, position.y);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.userData = this;
	m_bodyDef.linearVelocity = b2Vec2(velocity.x, velocity.y);
	m_bodyDef.bullet = true;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((m_dimensions.x/2) * PIXELSTOMETRES, (m_dimensions.y/2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.filter.groupIndex = -500;
	m_fixtureDef.userData = "arrow";
	m_fixture = m_body->CreateFixture(&m_fixtureDef);
}


Arrow::~Arrow(void)
{
	m_body->DestroyFixture(m_fixture);
	m_world->DestroyBody(m_body);
	//m_body->GetWorld()->DestroyBody(m_body);
}

void Arrow::Render(b2Vec2 offset) 
{
	SDL_Rect stretchRect;
	stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (m_dimensions.x/2) - offset.x;
	stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (m_dimensions.y/2) + offset.y;
	stretchRect.w = m_dimensions.x;
	stretchRect.h = m_dimensions.y;
	SDL_RenderCopyEx ( m_renderer, m_texture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}

b2Body* Arrow::GetBody() 
{
	return m_body;
}

void Arrow::SetBroken() 
{
	if(m_body != NULL)
	{
		b2Filter filter= m_body->GetFixtureList()->GetFilterData();
		filter.groupIndex = -100;
		m_body->GetFixtureList()->SetFilterData(filter);
		m_body->SetGravityScale(1);
		m_broken = true;
	}
}
bool Arrow::GetIsBroken() const
{
	return m_broken;
}