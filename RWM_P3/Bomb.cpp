#include "Bomb.h"

Bomb::Bomb(b2World *world, 
			SDL_Renderer *renderer,
			b2Vec2 dimensions,
			b2Vec2 position,
			b2Vec2 force)
		: m_renderer(renderer),
		m_world(world),
		m_dimensions(dimensions),
		m_fuseTime(2),
		alive(true)
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, position.y * PIXELSTOMETRES);
	m_bodyDef.fixedRotation = false;
	m_bodyDef.userData = this;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((m_dimensions.x/2) * PIXELSTOMETRES, (m_dimensions.y/2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.friction = 0.125f;
	m_fixtureDef.restitution = 0.5;
	m_fixtureDef.userData = "bomb";
	m_fixtureDef.filter.groupIndex = -100;

	m_body->CreateFixture(&m_fixtureDef);

	b2CircleShape circleShape;	
	circleShape.m_radius = 100*PIXELSTOMETRES; 
	m_sensorDef.shape = &circleShape;	
	m_sensorDef.isSensor = true;
	m_sensorDef.filter.groupIndex = -100;
	m_sensorDef.userData = "bombSensor";
	
	m_body->CreateFixture(&m_sensorDef);

	m_body->SetLinearVelocity(force);
	SoundManager::getSoundManager()->PlayFuseSound();
}

Bomb::~Bomb(void)
{
}

b2Body *Bomb::getBody()
{
	return m_body;
}

void Bomb::AddBlock(DirtBlock* b)
{
	collidingWithBlocks.push_back(b);
}

void Bomb::RemoveBlock(DirtBlock* b)
{
	for (int i = 0; i < collidingWithBlocks.size(); ++i)
	{
		if (b == collidingWithBlocks.at(i))
		{
			collidingWithBlocks.erase(collidingWithBlocks.begin()+i);
			break;
		}
	}
	
}
bool Bomb::Update(double deltatime)
{
	bool exploded = false;
	m_fuseTime -= deltatime;

	if (m_fuseTime < 0)
	{
		exploded = true;
		Explode();
		for (b2Fixture* f = m_body->GetFixtureList(); f; )
		{
			b2Fixture* fixtureToDestroy = f;
			f = f->GetNext();
			m_body->DestroyFixture( fixtureToDestroy );
		}
		
		
	}
	return exploded;
}

void Bomb::DeleteBody()
{
	m_body->GetWorld()->DestroyBody(m_body);
}


void Bomb::Explode()
{
	SoundManager::getSoundManager()->PlayExplosion();
	SDL_Haptic *haptic;
	haptic = SDL_HapticOpen( 0 );
	if (SDL_HapticRumbleInit( haptic ) != 0){}
	if (SDL_HapticRumblePlay( haptic, 1, 500 ) != 0){}
	for (int i = 0; i < collidingWithBlocks.size(); ++i)
	{
		collidingWithBlocks.at(i)->Destroy();
	}
	alive = false;
}

void Bomb::Render(b2Vec2 offset)
{
	int percentage = m_fuseTime / 2 * 9;
	
	stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (m_dimensions.x/2) - offset.x;
	stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (m_dimensions.y/2) + offset.y;
	stretchRect.w = m_dimensions.x;
	stretchRect.h = m_dimensions.y;
	SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_bombVector.at(percentage), NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}