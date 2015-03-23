#include <Scarab.h>

Scarab::Scarab(b2World *world, 
			   b2Vec2 dimensions, 
			   b2Vec2 position, 
			   SDL_Renderer *renderer) 
			   : m_renderer(renderer), 
			   m_dimensions(dimensions),
			   m_maxSteeringForce(150),
			   m_maxSpeed(20),
			   m_desiredSeparation(5),
			   m_distanceToNeighbour(0.15f)
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -(position.y * PIXELSTOMETRES));
	m_bodyDef.userData = this;
	m_bodyDef.gravityScale = 0;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((m_dimensions.x/2) * PIXELSTOMETRES, (m_dimensions.y/2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.userData = "scarab";
	m_fixtureDef.isSensor = true;
	m_fixtureDef.filter.groupIndex = -2000;
	m_body->CreateFixture(&m_fixtureDef);

	currFrame = 0;
}

Scarab::~Scarab() 
{
}

b2Body* Scarab::GetBody()
{
	return m_body;
}

void Scarab::Render(b2Vec2 offset) 
{
	if(currFrame == 0)
	{
		m_texture = TileBase::getBase()->m_scarabVector.at(0);
		currFrame = 1;
	}
	else
	{
		m_texture = TileBase::getBase()->m_scarabVector.at(1);
		currFrame = 0;
	}

	SDL_Rect stretchRect;
	stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (m_dimensions.x/2) - offset.x;
	stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (m_dimensions.y/2) + offset.y;
	stretchRect.w = m_dimensions.x;
	stretchRect.h = m_dimensions.y;

	if(m_body->GetLinearVelocity().x < 0)
	{
		SDL_RenderCopyEx ( m_renderer, m_texture, NULL, &stretchRect, m_body->GetAngle() * RADTODEG , NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
	}
	else
	{
		SDL_RenderCopyEx ( m_renderer, m_texture, NULL, &stretchRect, m_body->GetAngle() * RADTODEG , NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}
}

b2Vec2 Scarab::Separate(std::vector<Scarab*> scarabs)
{
	b2Vec2 steering = b2Vec2(0, 0);
	int numNeighbours = 0;
	b2Vec2 myPosition = m_body->GetPosition();

	//Get positions of other scarabs and modify steering vector accordingly
	for (int i = 0; i < scarabs.size(); ++i)
	{
		if (scarabs.at(i) != this)
		{
			b2Vec2 otherPosition = scarabs.at(i)->GetBody()->GetPosition();
			float distance = b2Distance(myPosition, otherPosition);

			if (distance > 0
				&& distance < m_desiredSeparation)
			{
				b2Vec2 difference = myPosition - otherPosition;
				difference.Normalize();
				difference *= (1 / distance);			
				steering += difference;
				++numNeighbours;
			}
		}
	}

	//Get average
	if (numNeighbours > 0)
	{
		steering *= (1 / numNeighbours);
	}

	//Check if steering vector is greater than the max steering force, and if it is, shorten it accordingly
	if (steering.Length() > 0) 
	{
		steering.Normalize();
		steering *= m_maxSpeed;
		steering -= m_body->GetLinearVelocity();
		if (steering.Length() > m_maxSteeringForce) 
		{
			steering.Normalize();
			steering *= m_maxSteeringForce;
		}
	}
	return -steering;
}

b2Vec2 Scarab::Align(std::vector<Scarab*> scarabs)
{
	b2Vec2 alignment = b2Vec2(0, 0);
	int numNeighbours = 0;
	b2Vec2 myPosition = m_body->GetPosition();

	//Get velocties of other scarabs and modify alignment vector accordingly
	for (int i = 0; i < scarabs.size(); ++i)
	{
		static b2Body* b = static_cast<b2Body*>(scarabs.at(i)->GetBody());
		if (scarabs.at(i) != this)
		{
			b2Vec2 otherPosition = b->GetPosition();
			float distance = b2Distance(myPosition, otherPosition);

			if (distance > 0 
				&& distance < m_distanceToNeighbour) 
			{
				alignment += b->GetLinearVelocity();
				++numNeighbours;
			}
		}
	}

	//Calculate steering vector from the alignment
	if (numNeighbours > 0) 
	{
		alignment *= (1 / numNeighbours);
		alignment.Normalize();
		alignment *= m_maxSpeed;
		b2Vec2 steering = alignment - m_body->GetLinearVelocity();

		//Check if steering vector is greater than the max steering force, and if it is, shorten it accordingly
		if (steering.Length() > m_maxSteeringForce) 
		{
			steering.Normalize();
			steering *= m_maxSteeringForce;
		}
		return -steering;
	}
	else 
	{
		return b2Vec2(0, 0);
	}
}

b2Vec2 Scarab::Cohesion(std::vector<Scarab*> scarabs)
{
	b2Vec2 totalCohesion = b2Vec2(0, 0);
	int numNeighbours = 0;
	b2Vec2 myPosition = m_body->GetPosition();

	//Get the distance to other scarabs and adjust cohesion accordingly
	for (int i = 0; i < scarabs.size(); ++i)
	{
		if (scarabs.at(i) != this)
		{
			b2Vec2 otherPosition = scarabs.at(i)->GetBody()->GetPosition();
			float distance = b2Distance(myPosition, otherPosition);

			if (distance > 0 
				&& distance < m_distanceToNeighbour) 
			{
				totalCohesion += otherPosition;
				++numNeighbours;
			}
		}
	}

	//Get average cohesion vector and seek towards it
	if (numNeighbours > 0) 
	{
		totalCohesion *= (1.0 / numNeighbours);
		return Seek(totalCohesion);
	}
	return b2Vec2(0, 0);
}

b2Vec2 Scarab::Seek(b2Vec2 target)
{
	//Seek towards a target
	b2Vec2 targetVector = target - m_body->GetPosition();
	targetVector.Normalize();
	targetVector *= m_maxSpeed;

	b2Vec2 seekVector = targetVector - m_body->GetLinearVelocity();
	if (seekVector.Length() > m_maxSteeringForce)
	{
		seekVector.Normalize();
		seekVector *= m_maxSteeringForce;
	}
	return -seekVector;
}

void Scarab::Flock(std::vector<Scarab*> scarabs, b2Vec2 playerPos)
{
	//Get vectors
	b2Vec2 separation = Separate(scarabs);
	b2Vec2 alignment= Align(scarabs);
	b2Vec2 cohesion = Cohesion(scarabs);

	//Apply forces
	m_body->ApplyForceToCenter(separation, true);
	m_body->ApplyForceToCenter(alignment, true);
	m_body->ApplyForceToCenter(cohesion, true);
	//Also move towards player
	m_body->ApplyForceToCenter(3 * (playerPos - m_body->GetPosition()), true);

	//Limit total velocity
	if (m_body->GetLinearVelocity().x > 20)
		m_body->SetLinearVelocity(b2Vec2(20, m_body->GetLinearVelocity().y));
	if (m_body->GetLinearVelocity().x < -20)
		m_body->SetLinearVelocity(b2Vec2(-20, m_body->GetLinearVelocity().y));
	if (m_body->GetLinearVelocity().y > 20)
		m_body->SetLinearVelocity(b2Vec2(m_body->GetLinearVelocity().x, 20));
	if (m_body->GetLinearVelocity().y < -20)
		m_body->SetLinearVelocity(b2Vec2(m_body->GetLinearVelocity().x, -20));
}