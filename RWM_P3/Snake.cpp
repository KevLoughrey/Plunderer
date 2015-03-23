#include <Snake.h>
#include <iostream>

b2Vec2 Snake::s_dimensions(30, 30);
float Snake::s_speed(3.0f);
float Snake::s_attackMultiplier(2.5f);
float Snake::s_slowdownMultiplier(6);
float Snake::s_minVelXBeforeTurning(0.005f);
float Snake::s_pitCheckValue(1);

bool Snake::s_initializedFSM(false);
		static bool GetInit();
	static void SetInit(bool);



std::map<std::string, std::function<void(Snake&)>> Snake::m_actionMap;
FSM Snake::m_fsm;

Snake::Snake(b2World* world, 
			 b2Vec2 position, 
			 SDL_Renderer* renderer,
			 Subject* subject) 
	:	m_renderer(renderer), 
		m_state("Moving"),
		m_look("Left"),
		m_isDead(false),
		m_alive(true),
		m_subject(subject)
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.userData = this;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((s_dimensions.x/2) * PIXELSTOMETRES, (s_dimensions.y/2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.userData = "snake";
	m_fixtureDef.density = 10;
	m_body->CreateFixture(&m_fixtureDef);

	m_actionMap["Turn"] = std::mem_fn(&Snake::Turn);
	m_actionMap["Move"] = std::mem_fn(&Snake::Move);
	m_actionMap["Attack"] = std::mem_fn(&Snake::Attack);

	m_numParticles = 30;
}

Snake::~Snake() 
{
	m_subject->Notify("snake destroyed");
	if(m_body != NULL && m_isBodyDestroyed)
	{
		m_subject->Notify("snake destroyed");
	}
	for (int i = 0; i < m_blockBits.size(); ++i)
	{
		delete m_blockBits.at(i);
	}
}

void Snake::Render(b2Vec2 offset) 
{
	if (m_alive == true)
	{
	SDL_Rect stretchRect;
	stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (s_dimensions.x/2) - offset.x;
	stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (s_dimensions.y/2) + offset.y;
	stretchRect.w = s_dimensions.x;
	stretchRect.h = s_dimensions.y;

	if(m_look == "Left")
	{
		SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_textureSnake, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}

	else
	{
		SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_textureSnake, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
	}
	}

	for (int i = 0; i < m_blockBits.size(); ++i)
	{
		m_blockBits.at(i)->Draw(offset);
	}
}

void Snake::Destroy()
{
	m_isBodyDestroyed = true;
	if (m_alive)
	{
		for (int i = 0; i < m_numParticles; ++i)
		{
			m_blockBits.push_back(new BlockParticles(m_body->GetWorldCenter(), m_renderer,2));
		}
		m_body->GetWorld()->DestroyBody(m_body);
		m_alive=false;
	}
}

void Snake::Update(double deltatime)
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

void Snake::DestroyBody()
{
	m_isBodyDestroyed = true;
	m_body->GetWorld()->DestroyBody(m_body);
}

bool Snake::ShouldRemove()
{
	return !m_alive && 0 == m_blockBits.size();
}

void Snake::SetIsDead(bool toggle) 
{
	SoundManager::getSoundManager()->PlayPop();
	m_isDead = toggle;
}

void Snake::SetLook(std::string dir)
{
	m_look = dir;
}

bool Snake::GetIsDead()const {
	return m_isDead;
}

std::string Snake::GetLook() const
{
	return m_look;
}

b2Body* Snake::GetBody() const
{
	return m_body;
}


b2Vec2 Snake::GetSize() 
{
	b2Vec2 l_size(s_dimensions.x * PIXELSTOMETRES, s_dimensions.y * PIXELSTOMETRES);
	return l_size;
}


float Snake::GetPitCheck()
{
	return s_pitCheckValue;
}

void Snake::PushFSMelement(	std::string state1,
							std::string evnt,
							std::string action,
							std::string state2)
{
	m_fsm.PushFSMelement(state1, evnt, action, state2);
}

void  Snake::FSMUpdate(std::string evnt)
{
	std::string l_action = m_fsm.Update(m_state, evnt);
	if (l_action != "No Action")
	{
		m_actionMap[l_action]((*this));
	}

}

void Snake::Move()
{
	if(m_look == "Left")
	{
		m_body->SetLinearVelocity( b2Vec2 (-s_speed, m_body->GetLinearVelocity().y) );
	}
	else
	{
		m_body->SetLinearVelocity( b2Vec2 (s_speed, m_body->GetLinearVelocity().y) );
	}
}

void Snake::Turn()
{
	float l_absCurrentXVel = std::abs(m_body->GetLinearVelocity().x);
	
	if(m_look == "Left")
	{
		if(l_absCurrentXVel < s_minVelXBeforeTurning)
		{
			m_look = "Right";
			m_body->SetLinearVelocity( b2Vec2(0, m_body->GetLinearVelocity().y));
		}
		else
		{
			m_body->ApplyForceToCenter(	b2Vec2 (-s_speed * s_slowdownMultiplier, m_body->GetLinearVelocity().y ), true);
		}
	}

	else
	{
		if(l_absCurrentXVel < s_minVelXBeforeTurning)
		{
			m_look = "Left";
			m_body->SetLinearVelocity( b2Vec2(0, m_body->GetLinearVelocity().y));
		}
		else
		{
			m_body->ApplyForceToCenter(	b2Vec2 (s_speed * s_slowdownMultiplier, m_body->GetLinearVelocity().y ), true);
		}
	}
}

void Snake::Attack()
{
	Move();
}

bool Snake::GetInit()
{
	return s_initializedFSM;
}

void Snake::SetInit(bool v)
{
	s_initializedFSM = v;
}