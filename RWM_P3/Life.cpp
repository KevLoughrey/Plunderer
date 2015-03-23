#include "Life.h"


Life::Life(b2World* world, 
		   b2Vec2 dimensions, 
		   b2Vec2 position, 
		   SDL_Renderer* renderer,
		   Subject *subject) :
	m_renderer(renderer), 
	m_dimensions(dimensions),
	m_isDead(false),
	m_subject(subject)
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.userData = this;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((m_dimensions.x/2) * PIXELSTOMETRES, (m_dimensions.y/2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.userData = "life";
	m_fixtureDef.filter.groupIndex = -500;
	m_body->CreateFixture(&m_fixtureDef);
}

Life::~Life(void)
{
	m_body->GetWorld()->DestroyBody(m_body);
	m_subject->Notify("life destroyed");
}

void Life::SetIsDead(bool toggle) 
{
	SoundManager::getSoundManager()->PlayPickup();
	m_isDead = toggle;
}

bool Life::GetIsDead() 
{
	return m_isDead;
}

b2Body* Life::GetBody() 
{
	return m_body;
}

void Life::Render(b2Vec2 offset) 
{
	SDL_Rect stretchRect;
	stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (m_dimensions.x/2) - offset.x;
	stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (m_dimensions.y/2) + offset.y;
	stretchRect.w = m_dimensions.x;
	stretchRect.h = m_dimensions.y;
	SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_textureHudHeart, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}

