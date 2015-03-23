#include "Door.h"


Door::Door(b2World *world,
		   SDL_Renderer *renderer,
		   b2Vec2 position,
		   int type,
		   DoorSwitch *doorSwitch):
	m_world(world)
{
	m_position = position;
	m_renderer = renderer;
	pos.w = 60;
	pos.h = 74;
	m_type = type;
	startAnim = false;
	m_doorSwitch = doorSwitch;
	if (m_type == 3)
	{
		m_frame = 5;
	}
	else 
	{
		m_frame = 0;
	}
	m_count = 0;
	hasCollided = false;
	animEnded = false;
	once = false;
	multiEnd = false;
	if (m_type == 1)
	{
		m_textureVector = TileBase::getBase()->m_doorStartVector;
	}
	else
	{
		m_textureVector = TileBase::getBase()->m_doorExitVector;
	}

	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.userData = this;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((pos.w/2) * PIXELSTOMETRES, (pos.h/2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.friction = 0;
	m_fixtureDef.filter.groupIndex = -100;
	m_fixtureDef.userData = "door";
	m_body->CreateFixture(&m_fixtureDef);
	
	m_leftSensorShape.SetAsBox(20 * PIXELSTOMETRES, (pos.h/2) * PIXELSTOMETRES, b2Vec2(-10 * PIXELSTOMETRES, 0), 0);
	m_leftSensorDef.shape = &m_leftSensorShape;
	m_leftSensorDef.isSensor = true;
	if (m_type == 1)
	{
		m_leftSensorDef.userData = "doorMiddleSensor";
	}
	else if (m_type == 2 || m_type == 3)
	{
		m_leftSensorDef.userData = "doorMiddleSensorExit";
	}
	
	m_body->CreateFixture(&m_leftSensorDef);
}

Door::~Door(void)
{
	for (b2Fixture* f = m_body->GetFixtureList(); f; )
	{
		b2Fixture* fixtureToDestroy = f;
		f = f->GetNext();
		m_body->DestroyFixture( fixtureToDestroy );
	}
	m_world->DestroyBody(m_body);
}

bool Door::GetAnimEnded()
{
	return animEnded;
}

void Door::setClose(bool close)
{
	hasCollided = close;
}

void Door::PlayClose()
{
	if (!once)
	{
		SoundManager::getSoundManager()->PlayDoorSound();
	}
	once = true;
	startAnim = true;
}
bool Door::GetMultiEnd()
{
	return multiEnd;
}
bool Door::CheckCollision()
{
	if (hasCollided && KeyboardManager::getKeys()->Key_Up && m_type != 3)
	{
		PlayClose();
		return true;
	}
	else if (hasCollided && KeyboardManager::getKeys()->Key_Up && m_type == 3 && animEnded)
	{
		multiEnd = true;
		return true;
	}
	else if ( m_doorSwitch != NULL)
	{
		if (m_type == 3 && m_doorSwitch->GetAnimEnded() && !animEnded) 
		{
				PlayClose();
				return true;
		}
		else if (!m_doorSwitch->GetAnimEnded())
		{
			m_frame = 5;
			animEnded = false;
			startAnim = false;
		}
	}
	return false;
}

void Door::Render(b2Vec2 offset)
{
	if (startAnim && m_frame != 5 && m_count % 10 == 0 && m_type != 3)
	{
		m_frame++;
	}
	else if (startAnim && m_frame != 0 && m_count % 10 == 0 && m_type == 3 && !animEnded)
	{
		m_frame--;
	}

	if (m_frame == 5 && m_type != 3)
	{
		animEnded = true;
	}
	else if ( m_frame == 0 && m_type == 3)
	{
		animEnded = true;
	}

	m_count++;
	SDL_Rect stretchRect;
	stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (pos.w/2) - offset.x;
	stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (pos.h/2) + offset.y;
	stretchRect.w = pos.w;
	stretchRect.h = pos.h;
	SDL_RenderCopyEx ( m_renderer, m_textureVector.at(m_frame), NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}