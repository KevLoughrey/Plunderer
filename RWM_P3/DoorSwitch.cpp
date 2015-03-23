#include "DoorSwitch.h"


DoorSwitch::DoorSwitch(b2World *world,
					   SDL_Renderer *renderer,
					   b2Vec2 position)
{
	m_position = position;
	m_renderer = renderer;
	pos.w = 60;
	pos.h = 40;
	m_frame = 0;
	m_resetCount = 1;

	startAnim = false;
	m_frame = 0;
	m_count = 0;
	animEnded = false;
	hasCollided = false;
	once = false;

	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.userData = this;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((pos.w/2) * PIXELSTOMETRES, (pos.h/2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.friction = 0;
	m_fixtureDef.filter.groupIndex = -100;
	m_fixtureDef.userData = "switch";
	m_body->CreateFixture(&m_fixtureDef);
	
	m_leftSensorShape.SetAsBox(20 * PIXELSTOMETRES, (pos.h/2) * PIXELSTOMETRES, b2Vec2(-10 * PIXELSTOMETRES, 0), 0);
	m_leftSensorDef.shape = &m_leftSensorShape;
	m_leftSensorDef.isSensor = true;
	m_leftSensorDef.userData = "switchSensor";
	m_body->CreateFixture(&m_leftSensorDef);
}

DoorSwitch::~DoorSwitch(void)
{
	for (b2Fixture* f = m_body->GetFixtureList(); f; )
	{
		b2Fixture* fixtureToDestroy = f;
		f = f->GetNext();
		m_body->DestroyFixture( fixtureToDestroy );
	}
	m_world->DestroyBody(m_body);
}

bool DoorSwitch::GetAnimEnded()
{
 	return animEnded;
}

bool DoorSwitch::CheckCollision()
{
	if (hasCollided && KeyboardManager::getKeys()->Key_Up)
	{
		PlayClose();
		return true;
	}
	return false;
}

void DoorSwitch::PlayClose()
{
	if (!once)
	{
		SoundManager::getSoundManager()->PlayDoorSound();
	}
	once = true;
	startAnim = true;
}

void DoorSwitch::setClose(bool close)
{
	hasCollided = close;
}

void DoorSwitch::Render(b2Vec2 offset)
{
	CheckCollision();

	if (startAnim && m_frame != 4 && m_count % 7 == 0)
	{
		m_frame++;
	}

	if (m_frame == 4)
	{
		animEnded = true;
	}

	if (animEnded)
	{
		m_resetCount++;
	}

	if (m_resetCount % 1000 == 0)
	{
		m_frame = 0;
		once = false;
		animEnded = false;
		startAnim = false;
		hasCollided = false;
		m_resetCount = 1;
	}

	m_count++;
	SDL_Rect stretchRect;
	stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (pos.w/2) - offset.x;
	stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (pos.h/2) + offset.y;
	stretchRect.w = pos.w;
	stretchRect.h = pos.h;
	SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_switchTextures.at(m_frame), NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}
