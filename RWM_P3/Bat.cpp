#include <Bat.h>

b2Vec2 Bat::s_dimensions(30, 30);
float Bat::s_speed(3.0f);
float Bat::s_slowdownMultiplier(6);
float Bat::s_minVelXBeforeTurning(0.005f);

Bat::Bat(b2World* world, 
			 b2Vec2 position, 
			 SDL_Renderer* renderer,
			 Subject* subject) 
	:	m_renderer(renderer), 
		m_look("Left"),
		m_isDead(false),
		m_initStickToCeiling(false),
		m_isOnCeiling(false),
		m_alive(true),
		m_playerIsWithinRadius(false),
		m_state( new BatSleep()),
		m_subject(subject)
{
	m_texture = TileBase::getBase()->m_batVector.at(0);
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.userData = this;
	m_bodyDef.gravityScale = -.2;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((s_dimensions.x/2) * PIXELSTOMETRES, (s_dimensions.y/2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.userData = "bat";
	m_fixtureDef.density = 10;
	m_body->CreateFixture(&m_fixtureDef);


	m_ceilingSensorShape.SetAsBox( ((s_dimensions.x/2) - 6) * PIXELSTOMETRES, (s_dimensions.y/2)* PIXELSTOMETRES, b2Vec2(0,0.5),0);
	m_ceilingSensorDef.shape = &m_ceilingSensorShape;
	m_ceilingSensorDef.isSensor = true;
	m_ceilingSensorDef.userData = "batCeilingSensor";
	m_body->CreateFixture(&m_ceilingSensorDef);

	b2PolygonShape m_playerSensorShape;
	b2FixtureDef m_playerSensorDef;

	float radius = 8;
	b2Vec2 vertices[8];
	vertices[0].Set(0,0);
	for (int i = 0; i < 7; i++) 
	{
		
		float angle = i / 3.0 * 90 * DEGTORAD ;

		vertices[i+1].Set( radius * cosf(angle), radius * sinf(angle) );
	}


	m_playerSensorShape.Set(vertices, 8);
	m_playerSensorDef.shape = &m_playerSensorShape;
	m_playerSensorDef.isSensor = true;
	m_playerSensorDef.userData = "batPlayerSensor";
	m_body->CreateFixture(&m_playerSensorDef);
  

	m_body->SetLinearVelocity( b2Vec2 (0, 170) );
	m_numParticles = CONSTANTS::NUM_PARTICLES_DEATH;
}

Bat::~Bat() 
{
	m_subject->Notify("bat destroyed");
	if(m_body != NULL && m_isBodyDestroyed)
	{
		m_subject->Notify("bat destroyed");
	}
	for (int i = 0; i < m_blockBits.size(); ++i)
	{
		delete m_blockBits.at(i);
	}
}

void Bat::Destroy()
{
	m_isBodyDestroyed = true;
	if (m_alive)
	{
		for (int i = 0; i < m_numParticles; ++i)
		{
			m_blockBits.push_back(new BlockParticles(m_body->GetWorldCenter(), m_renderer,3));
		}
		m_body->GetWorld()->DestroyBody(m_body);
		m_alive=false;
	}
}

void Bat::Update(double deltatime)
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


void Bat::DestroyBody()
{
	m_isBodyDestroyed = true;
	m_body->GetWorld()->DestroyBody(m_body);
}

bool Bat::ShouldRemove()
{
	return !m_alive && 0 == m_blockBits.size();
}



void Bat::Render(b2Vec2 offset) 
{
	SDL_Rect stretchRect;
	stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (s_dimensions.x/2) - offset.x;
	stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (s_dimensions.y/2) + offset.y;
	stretchRect.w = s_dimensions.x;
	stretchRect.h = s_dimensions.y;


	if(m_look == "Left" && !m_isOnCeiling)
	{
		SDL_RenderCopyEx ( m_renderer, m_texture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}

	else if (!m_isOnCeiling)
	{
		SDL_RenderCopyEx ( m_renderer, m_texture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
	}

	else
	{
		SDL_RenderCopyEx ( m_renderer, m_texture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_VERTICAL );
	}

	for (int i = 0; i < m_blockBits.size(); ++i)
	{
		m_blockBits.at(i)->Draw(offset);
	}

}

void Bat::SetIsDead(bool toggle) 
{
	SoundManager::getSoundManager()->PlayPop();
	m_isDead = toggle;
}

void Bat::SetLook(std::string dir)
{
	m_look = dir;
}

bool Bat::GetIsDead()const {
	return m_isDead;
}

std::string Bat::GetLook() const
{
	return m_look;
}

b2Body* Bat::GetBody() const
{
	return m_body;
}


b2Vec2 Bat::GetSize() 
{
	b2Vec2 l_size(s_dimensions.x * PIXELSTOMETRES, s_dimensions.y * PIXELSTOMETRES);
	return l_size;
}




void Bat::Update(bool playerDetected)
{
	m_batSeesPlayer = playerDetected;


	BatState* state = m_state->Update(*this);
	if (state != NULL)
	{
		delete m_state;
		m_state = state;
	}
}

void Bat::FlyForward()
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

void Bat::Turn()
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


bool Bat::GetOnCeiling() const
{
	return m_isOnCeiling;
}

void Bat::SetOnCeiling(bool v)
{
	m_isOnCeiling = v;

	if(!m_initStickToCeiling &&
		m_isOnCeiling)
	{
		m_initStickToCeiling = true;
	}
}


bool Bat::GetPlayerIsClose() const
{
	return m_playerIsWithinRadius;
}

void Bat::SetPlayerIsClose(bool v)
{
	m_playerIsWithinRadius = v;
}

b2Body* Bat::GetPlayerBody() const
{
	return m_playerBody; 
}

void Bat::SetPlayerBody(b2Body* v)
{
	m_playerBody = v;
}

void Bat::SetTexture(SDL_Texture* t)
{
	m_texture = t;
}

bool Bat::GetSeesPlayer() const
{
	return m_batSeesPlayer;
}