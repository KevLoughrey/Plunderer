#include <EnemyManager.h>


EnemyManager *EnemyManager::s_instance = NULL;

EnemyManager::EnemyManager()
{
	// FSMs for Snakes and Mummies are static 
	// and initialized here once.
	if(!Snake::GetInit())
	{
		Snake::PushFSMelement("Moving", "Nothing", 	"Turn", "Moving");
		Snake::PushFSMelement("Moving", "Floor Presents", "Move","Moving");
		Snake::PushFSMelement("Moving", "Player in Front", "Attack", "Moving");
		Snake::PushFSMelement("Moving", "Block in Front", "Turn", "Moving");
		Snake::SetInit(true);
	}

	if(!Mummy::GetInit())
	{
		Mummy::PushFSMelement("Moving", "1 Block in Front", "Jump", "Moving");
		Mummy::PushFSMelement("Moving", "Wall in Front", "Turn", "Moving");
		Mummy::PushFSMelement("Moving", "Pit", "Turn", "Moving");
		Mummy::PushFSMelement("Moving", "1 Block Step", "Move", "Moving");
		Mummy::PushFSMelement("Moving", "Floor Presents", "Move","Moving");
		Mummy::PushFSMelement("Moving", "Player in Front", "Attack", "Moving");
		Mummy::SetInit(true);
	}
}

EnemyManager::~EnemyManager(void)
{
}


void EnemyManager::CheckForDead(double deltatime)
{
	for (int i = 0; i < m_snakes.size(); ++i) 
	{
		if (m_snakes.at(i)->GetIsDead())
		{
			m_snakes.at(i)->Destroy();
		}
	}
	for (int i = 0; i < m_snakes.size(); ++i) 
	{
		m_snakes.at(i)->Update(deltatime);
	}

	for (int i = 0; i < m_snakes.size(); ++i) 
	{
		if(m_snakes.at(i)->ShouldRemove())
		{
			delete m_snakes.at(i);
			m_snakes.erase(m_snakes.begin()+i);
		}
	}

	for (int i = 0; i < m_mummies.size(); ++i) 
	{
		if (m_mummies.at(i)->GetIsDead())
		{
			m_mummies.at(i)->Destroy();
		}
	}
	for (int i = 0; i < m_mummies.size(); ++i) 
	{
		m_mummies.at(i)->Update(deltatime);
	}

	for (int i = 0; i < m_mummies.size(); ++i) 
	{
		if(m_mummies.at(i)->ShouldRemove())
		{
			delete m_mummies.at(i);
			m_mummies.erase(m_mummies.begin()+i);
			
		}
	}

	for (int i = 0; i < m_bats.size(); ++i) 
	{
		if (m_bats.at(i)->GetIsDead())
		{
			m_bats.at(i)->Destroy();
		}
	}
	for (int i = 0; i < m_bats.size(); ++i) 
	{
		m_bats.at(i)->Update(deltatime);
	}

	for (int i = 0; i < m_bats.size(); ++i) 
	{
		if(m_bats.at(i)->ShouldRemove())
		{
			delete m_bats.at(i);
			m_bats.erase(m_bats.begin()+i);
		}
	}

}


void EnemyManager::SnakeUpdate(int index, b2World* world)
{
	b2Body* l_body = m_snakes.at(index)->GetBody();

	// Check if snake alive.
	if (!m_snakes.at(index)->GetIsDead())
	{
		// Retrieve snake's Axis-Aligned Bounding Box. One will be used 
		// to check what is in front ans another will check what is in front
		// AND below.
		b2AABB l_AABBSnakeStraight = l_body->GetFixtureList()->GetAABB(0);
		b2AABB l_AABBSnakeDiagonal = l_body->GetFixtureList()->GetAABB(0);

		// Get Direction in which snake looks.
		std::string l_look = m_snakes.at(index)->GetLook();

		std::string l_event;

		// A custom made callback method, derived from "b2QueryCallback"
		SnakeQuery l_callback;

		// Increase AABBs
		#pragma region Extend AABBs
		l_AABBSnakeStraight.upperBound.x += Snake::GetSize().x/2;
		l_AABBSnakeStraight.upperBound.y -= Snake::GetSize().y/2;

		l_AABBSnakeDiagonal.upperBound.x += Snake::GetSize().x/2;	
		l_AABBSnakeDiagonal.upperBound.y -= Snake::GetSize().y/2;
		#pragma endregion

		// Below adjusted AABBs' dimensions and positions. 
		// Very messy and was a hardest part.
		if(l_look == "Right")
		{
			#pragma region Correct AABBs
			l_AABBSnakeStraight.lowerBound.x += Snake::GetSize().x / 4;
			l_AABBSnakeStraight.upperBound.x += Snake::GetSize().x / 4;
			l_AABBSnakeStraight.lowerBound.y += Snake::GetSize().y / 4;
			l_AABBSnakeStraight.upperBound.y += Snake::GetSize().y / 4;

			l_AABBSnakeDiagonal.lowerBound.x += Snake::GetSize().x / 4 + Snake::GetPitCheck();
			l_AABBSnakeDiagonal.upperBound.x += Snake::GetSize().x / 4;	
			l_AABBSnakeDiagonal.lowerBound.y -= Snake::GetSize().y / 4;
			l_AABBSnakeDiagonal.upperBound.y -= Snake::GetSize().y / 4;
			#pragma endregion
		}

		else
		{
			#pragma region Correct AABBs
			l_AABBSnakeStraight.lowerBound.x -= Snake::GetSize().x /2;
			l_AABBSnakeStraight.upperBound.x -= Snake::GetSize().x /2;
			l_AABBSnakeStraight.lowerBound.y += Snake::GetSize().y / 4;
			l_AABBSnakeStraight.upperBound.y += Snake::GetSize().y / 4;

			l_AABBSnakeDiagonal.lowerBound.x -= Snake::GetSize().x / 2;
			l_AABBSnakeDiagonal.upperBound.x -= (Snake::GetSize().x / 2) + Snake::GetPitCheck();
			l_AABBSnakeDiagonal.lowerBound.y -= Snake::GetSize().y / 4;
			l_AABBSnakeDiagonal.upperBound.y -= Snake::GetSize().y / 4;
			#pragma endregion
		}

		// Check is there something in front.  Result is output into "l_event"
		world->QueryAABB(&l_callback,l_AABBSnakeStraight);
		l_event = l_callback.m_event;

		// If Nothing, we check is floor presents.  Result is also stored in "l_event"
		if(l_event == "Nothing")
		{
			l_callback.m_diagonalCheck = true;
			world->QueryAABB(&l_callback,l_AABBSnakeDiagonal);
			l_event = l_callback.m_event;
		}

		// Then I pass "l_event" into snake update method.
		m_snakes.at(index)->FSMUpdate(l_event);
	}
}


void EnemyManager::MummyUpdate(int index, b2World* world)
{
	// Check if mummy is alive.  Most of the method is same,
	// so I will leave comments in event handling.
	if (!m_mummies.at(index)->GetIsDead())
	{ 
		b2Body* l_body = m_mummies.at(index)->GetBody();

		std::string l_look = m_mummies.at(index)->GetLook();
		std::string l_event;

		MummyQuery l_callback;

		b2AABB l_AABBMummyStraight = l_body->GetFixtureList()->GetAABB(0);
		b2AABB l_AABBMummyDiagonalUp = l_body->GetFixtureList()->GetAABB(0);
		b2AABB l_AABBMummyDiagonalDown = l_body->GetFixtureList()->GetAABB(0);

		#pragma region Extend AABBs
		l_AABBMummyStraight.upperBound.x += Mummy::GetSize().x/2;
		l_AABBMummyStraight.upperBound.y -= Mummy::GetSize().y/2;

		l_AABBMummyDiagonalDown.upperBound.x += Mummy::GetSize().x/2;	
		l_AABBMummyDiagonalDown.upperBound.y -= Mummy::GetSize().y/2;

		l_AABBMummyDiagonalUp.upperBound.x += Mummy::GetSize().x/2;	
		l_AABBMummyDiagonalUp.upperBound.y -= Mummy::GetSize().y/2;
		#pragma endregion

		if(l_look == "Right")
		{
			#pragma region Correct AABBs
			l_AABBMummyStraight.lowerBound.x += Mummy::GetSize().x / 4;
			l_AABBMummyStraight.upperBound.x += Mummy::GetSize().x / 4;
			l_AABBMummyStraight.lowerBound.y += Mummy::GetSize().y / 4;
			l_AABBMummyStraight.upperBound.y += Mummy::GetSize().y / 4;

			l_AABBMummyDiagonalDown.lowerBound.x += Mummy::GetSize().x / 4 + Mummy::GetPitCheck();
			l_AABBMummyDiagonalDown.upperBound.x += Mummy::GetSize().x / 4;	
			l_AABBMummyDiagonalDown.lowerBound.y -= Mummy::GetSize().y / 4;
			l_AABBMummyDiagonalDown.upperBound.y -= Mummy::GetSize().y / 4;

			l_AABBMummyDiagonalUp.lowerBound.x += Mummy::GetSize().x / 4;
			l_AABBMummyDiagonalUp.upperBound.x += Mummy::GetSize().x / 2;	
			l_AABBMummyDiagonalUp.lowerBound.y += (Mummy::GetSize().y / 2);
			l_AABBMummyDiagonalUp.upperBound.y += (Mummy::GetSize().y );
			#pragma endregion
		}

		else
		{
			#pragma region Correct AABBs
			l_AABBMummyStraight.lowerBound.x -= Mummy::GetSize().x / 2;
			l_AABBMummyStraight.upperBound.x -= Mummy::GetSize().x / 2;
			l_AABBMummyStraight.lowerBound.y += Mummy::GetSize().y / 4;
			l_AABBMummyStraight.upperBound.y += Mummy::GetSize().y / 4;

			l_AABBMummyDiagonalDown.lowerBound.x -= (Mummy::GetSize().x / 2);
			l_AABBMummyDiagonalDown.upperBound.x -= (Mummy::GetSize().x / 2) + Mummy::GetPitCheck();
			l_AABBMummyDiagonalDown.lowerBound.y -= Mummy::GetSize().y / 4;
			l_AABBMummyDiagonalDown.upperBound.y -= Mummy::GetSize().y / 4;

			l_AABBMummyDiagonalUp.lowerBound.x -= Mummy::GetSize().x / 2;
			l_AABBMummyDiagonalUp.upperBound.x -= Mummy::GetSize().x ;	
			l_AABBMummyDiagonalUp.lowerBound.y += (Mummy::GetSize().y / 2);
			l_AABBMummyDiagonalUp.upperBound.y += (Mummy::GetSize().y );
			#pragma endregion
		}

		// There I set a type for Query.  For now, I check what is in front. 
		l_callback.m_type = "In Front";
		world->QueryAABB(&l_callback,l_AABBMummyStraight);
		l_event = l_callback.m_event;

		// If mummy spotted an obstacle, mummy will check how high it is.
		if(l_event == "Obstacle")
		{
			l_callback.m_type = "Wall Height";
			world->QueryAABB(&l_callback,l_AABBMummyDiagonalUp);
			l_event = l_callback.m_event;

		}


		// I mummy sees nothing in front, check the floor.
		if(l_event  == "Nothing") 
		{
			l_callback.m_type = "Check Floor";
			world->QueryAABB(&l_callback,l_AABBMummyDiagonalDown);
			l_event = l_callback.m_event;

			// If nothing, mummy will check how deep it is.
			if (l_event  == "Nothing")
			{
				// Lower AABB's position. 
				l_AABBMummyDiagonalDown.lowerBound.y -= Mummy::GetSize().y / 1;
				l_AABBMummyDiagonalDown.upperBound.y -= Mummy::GetSize().y / 1;

				l_callback.m_type = "Check Deepness";
				world->QueryAABB(&l_callback,l_AABBMummyDiagonalDown);
				l_event = l_callback.m_event;
				
				// Fixer, in case of a bug.  On normal occasion event
				// is either "Pit" (Mummy will turn) or "1 Block Step" (Mummy will jump down).  
				if(l_event  == "Nothing") 
				{
					l_event = "Pit";
				}
			}
		}

		// Feed in "l_event".
		m_mummies.at(index)->FSMUpdate(l_event);
	}
}

void EnemyManager::BatUpdate(int index, b2World* world)
{
	bool playerSeen = false;

	if (!m_bats.at(index)->GetIsDead())
	{
		// Used to check is player within bat's sensor radius.
		if(m_bats.at(index)->GetPlayerIsClose())
		{
			b2Body* l_body = m_bats.at(index)->GetBody();

			std::string l_look = m_bats.at(index)->GetLook();
			std::string l_event;

			// Raycast method
			BatQuery l_callback;
			

			world->RayCast(&l_callback,l_body->GetPosition(), m_bats.at(index)->GetPlayerBody()->GetPosition());

			// store result
			playerSeen = l_callback.m_detectedPlayer;
		}
		// Pass the result.
		m_bats.at(index)->Update(playerSeen);
	}
}




EnemyManager* EnemyManager::Instance()
{
	if (s_instance == NULL)
	{
		s_instance = new EnemyManager();
	}
	return s_instance;
}


void EnemyManager::AddMummy(Mummy *mummy)
{
	m_mummies.push_back(mummy);
}

void EnemyManager::AddSnake(Snake *snake)
{
	m_snakes.push_back(snake);
}


void EnemyManager::AddBat(Bat * bat)
{
	m_bats.push_back(bat);
}


void EnemyManager::DestroyAll()
{
	for (int i = 0; i < m_snakes.size(); ++i) 
	{
		delete m_snakes.at(i);
		m_snakes.erase(m_snakes.begin() + i);
	}

	for (int i = 0; i < m_mummies.size(); ++i) 
	{
		delete m_mummies.at(i);
		m_mummies.erase(m_mummies.begin() + i);
	}

	m_mummies.clear();
	for(int i =0; i < m_mummies.size(); ++i)
	{
		delete m_mummies.at(i);
	}

	m_bats.clear();
	for(int i =0; i < m_bats.size(); ++i)
	{
		delete m_bats.at(i);
	}


	delete s_instance;
	s_instance = NULL;
}

void EnemyManager::Update(b2World* world , double deltatime)
{
	CheckForDead(deltatime);
	for(int i = 0; i <m_snakes.size(); i++)
	{
		SnakeUpdate(i, world);
	}

	for(int i = 0; i <m_mummies.size(); i++)
	{
		MummyUpdate(i, world);
	}

	for(int i = 0; i <m_bats.size(); i++)
	{
		BatUpdate(i, world);
	}
}

void EnemyManager::Render( b2Vec2 offset)
{
	for (int i = 0; i < m_snakes.size(); ++i) 
	{
		m_snakes.at(i)->Render(offset);
	}

	for (int i = 0; i < m_mummies.size(); ++i) 
	{
		m_mummies.at(i)->Render(offset);
	}

	for (int i = 0; i < m_bats.size(); ++i) 
	{
		m_bats.at(i)->Render(offset);
	}
}