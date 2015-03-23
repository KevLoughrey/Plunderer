#include <Mummy.h>


b2Vec2 Mummy::s_dimensions(30,45);
float Mummy::s_speed(4);
float Mummy::s_attackMultiplier(2);
float Mummy::s_slowdownMultiplier(6);
float Mummy::s_minVelXBeforeTurning(0.005f);
float Mummy::s_pitCheckValue(1);
bool Mummy::s_initializedFSM(false);

std::map<std::string, std::function<void(Mummy&)>> Mummy::m_actionMap;
FSM Mummy::m_fsm;

Mummy::Mummy(b2World* world, 
			 b2Vec2 position, 
			 SDL_Renderer* renderer,
			 Subject* subject) 
	:	m_renderer(renderer), 
		m_state("Moving"),
		m_look("Left"),
		m_isDead(false),
		m_alive(true),
		m_health(6),
		m_subject(subject)
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.userData = this;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((s_dimensions.x/2) * PIXELSTOMETRES, (s_dimensions.y/2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.userData = "mummy";
	m_fixtureDef.density = 10;
	m_body->CreateFixture(&m_fixtureDef);

	m_actionMap["Turn"] = std::mem_fn(&Mummy::Turn);
	m_actionMap["Move"] = std::mem_fn(&Mummy::Move);
	m_actionMap["Attack"] = std::mem_fn(&Mummy::Attack);
	m_actionMap["Jump"] = std::mem_fn(&Mummy::Jump);

	m_numParticles = CONSTANTS::NUM_PARTICLES_DEATH;
}

Mummy::~Mummy() 
{
	m_subject->Notify("mummy destroyed");
	if(m_body != NULL && m_isBodyDestroyed)
	{
		m_subject->Notify("mummy destroyed");
	}
	for (int i = 0; i < m_blockBits.size(); ++i)
	{
		delete m_blockBits.at(i);
	}
}

void Mummy::Destroy()
{
	m_isBodyDestroyed = true;
	if (m_alive)
	{
		for (int i = 0; i < m_numParticles; ++i)
		{
			m_blockBits.push_back(new BlockParticles(m_body->GetWorldCenter(), m_renderer,4));
		}
		m_body->GetWorld()->DestroyBody(m_body);
		m_alive=false;
	}
}

void Mummy::Update(double deltatime)
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
void Mummy::DestroyBody()
{
	m_isBodyDestroyed = true;
	m_body->GetWorld()->DestroyBody(m_body);
}

bool Mummy::ShouldRemove()
{
	return !m_alive && 0 == m_blockBits.size();
}

void Mummy::Render(b2Vec2 offset) 
{
	SDL_Rect stretchRect;
	stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (s_dimensions.x/2) - offset.x;
	stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (s_dimensions.y/2) + offset.y;
	stretchRect.w = s_dimensions.x;
	stretchRect.h = s_dimensions.y;

	if(m_look == "Left")
	{
		SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_textureMummy, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}

	else
	{
		SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_textureMummy, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
	}

	for (int i = 0; i < m_blockBits.size(); ++i)
	{
		m_blockBits.at(i)->Draw(offset);
	}
}

void Mummy::SetIsDead(bool toggle) 
{
	SoundManager::getSoundManager()->PlayPop();
	m_isDead = toggle;
}

void Mummy::SetLook(std::string dir)
{
	m_look = dir;
}

bool Mummy::GetIsDead()const {
	return m_isDead;
}

std::string Mummy::GetLook() const
{
	return m_look;
}

b2Body* Mummy::GetBody() const
{
	return m_body;
}

b2Vec2 Mummy::GetSize() 
{
	b2Vec2 l_size(s_dimensions.x * PIXELSTOMETRES, s_dimensions.y * PIXELSTOMETRES);
	return l_size;
}


float Mummy::GetPitCheck()
{
	return s_pitCheckValue;
}

void Mummy::PushFSMelement(	std::string state1,
							std::string evnt,
							std::string action,
							std::string state2)
{
	m_fsm.PushFSMelement(state1, evnt, action, state2);
}

void  Mummy::FSMUpdate(std::string evnt)
{
	std::string l_action = m_fsm.Update(m_state, evnt);
	if (l_action != "No Action")
	{
		m_actionMap[l_action]((*this));
	}

}

void Mummy::Move()
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

void Mummy::Turn()
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

void Mummy::Attack()
{
	if(m_look == "Right")
	{
		m_body->SetLinearVelocity(	b2Vec2 (s_speed * s_attackMultiplier, m_body->GetLinearVelocity().y));
	}
	else 
	{
		m_body->SetLinearVelocity(	b2Vec2 (-s_speed * s_attackMultiplier, m_body->GetLinearVelocity().y));
	}
}

void Mummy::Jump()
{
	m_body->SetLinearVelocity(	b2Vec2 (m_body->GetLinearVelocity().x, 18) );
}

void Mummy::DecreaseHealth(int v)
{
	m_health -= v;

	if(m_health <=0)
	{
		m_isDead = true;
	}
}

bool Mummy::GetInit()
{
	return s_initializedFSM;
}

void Mummy::SetInit(bool v)
{
	s_initializedFSM = v;
}