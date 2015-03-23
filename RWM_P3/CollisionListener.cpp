#include <CollisionListener.h>

CollisionListener* CollisionListener::m_instance;
b2World* CollisionListener::m_world;

CollisionListener::CollisionListener()
{
}

CollisionListener::~CollisionListener()
{
}

CollisionListener* CollisionListener::getListener() 
{
	if (m_instance == NULL) 
	{
		m_instance = new CollisionListener();
	}
	return m_instance;
}

void CollisionListener::SetWorld(b2World* world) 
{
	m_world = world;
}

void CollisionListener::BeginContact(b2Contact* contact) 
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();


	#pragma region Player Sensor and Blocks
	if (fixtureA->GetUserData() == "playerSensor" 
		&& fixtureB->GetUserData() == "block") 
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseJumpContacts();
	}
	else if (fixtureA->GetUserData() == "block" 
		&& fixtureB->GetUserData() == "playerSensor") 
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseJumpContacts();
	}

	if (fixtureA->GetUserData() == "scarab" 
		&& fixtureB->GetUserData() == "player"
		&& contact->IsTouching()) 
	{
		static_cast<Player*>(fixtureB->GetBody()->GetUserData())->DecreaseHealth(1);
	}
	else if (fixtureA->GetUserData() == "player" 
		&& fixtureB->GetUserData() == "scarab"
		&& contact->IsTouching()) 
	{
		static_cast<Player*>(fixtureA->GetBody()->GetUserData())->DecreaseHealth(1);
	}

	if (fixtureA->GetUserData() == "playerSensor" 
		&& fixtureB->GetUserData() == "solidBlock") 
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseJumpContacts();
	}
	else if (fixtureA->GetUserData() == "solidBlock" 
		&& fixtureB->GetUserData() == "playerSensor") 
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseJumpContacts();
	}

	if (fixtureA->GetUserData() == "playerSensor" 
		&& fixtureB->GetUserData() == "arrowTrap") 
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseJumpContacts();
	}
	else if (fixtureA->GetUserData() == "arrowTrap" 
		&& fixtureB->GetUserData() == "playerSensor") 
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseJumpContacts();
	}

	if (fixtureA->GetUserData() == "player" 
		&& fixtureB->GetUserData() == "switchSensor") 
	{
		void* s = fixtureB->GetBody()->GetUserData();
		static_cast<DoorSwitch*>(s)->setClose(true);
	}
	else if (fixtureA->GetUserData() == "switchSensor" 
		&& fixtureB->GetUserData() == "player") 
	{
		void* s = fixtureA->GetBody()->GetUserData();
		static_cast<DoorSwitch*>(s)->setClose(true);
	}

	#pragma endregion
	
	#pragma region Snake and Player

	if (fixtureA->GetUserData() == "playerSensor" 
		&& fixtureB->GetUserData() == "snake"
		&& contact->IsTouching()) 
	{
		void* player = fixtureA->GetBody()->GetUserData();
		void* snake = fixtureB->GetBody()->GetUserData();

		//static_cast<Player*>(player)->ModifyState(new PlayerStomp());
		static_cast<Player*>(player)->Bounce();
		static_cast<Snake*>(snake)->SetIsDead(true);
	}

	else if (fixtureA->GetUserData() == "snake" 
		&& fixtureB->GetUserData() == "playerSensor"
		&& contact->IsTouching()) 
	{
		void* snake = fixtureA->GetBody()->GetUserData();
		void* player = fixtureB->GetBody()->GetUserData();

		//static_cast<Player*>(player)->ModifyState(new PlayerStomp());
		static_cast<Player*>(player)->Bounce();
		static_cast<Snake*>(snake)->SetIsDead(true);
	}

	if (fixtureA->GetUserData() == "player" 
		&& fixtureB->GetUserData() == "snake"
		&& contact->IsTouching()) 
	{
		void* snake = fixtureB->GetBody()->GetUserData();
		void* player = fixtureA->GetBody()->GetUserData();
		Player* p = static_cast<Player*>(player);
		if(!static_cast<Snake*>(snake)->GetIsDead())
		{
			p->DecreaseHealth(1);
			p->SetInjured(true);
			p->Kickback(static_cast<Snake*>(snake)->GetBody()->GetPosition());
		}
	}
	else if (fixtureA->GetUserData() == "snake" 
		&& fixtureB->GetUserData() == "player"
		&& contact->IsTouching()) 
	{
		void* snake = fixtureA->GetBody()->GetUserData();
		void* player = fixtureB->GetBody()->GetUserData();
		Player* p = static_cast<Player*>(player);
		if(!static_cast<Snake*>(snake)->GetIsDead())
		{
			p->DecreaseHealth(1);
			p->SetInjured(true);
			p->Kickback(static_cast<Snake*>(snake)->GetBody()->GetPosition());
		}
	}
	#pragma endregion

	#pragma region Mummy and Player
	if (fixtureA->GetUserData() == "playerJumpSensor" 
		&& fixtureB->GetUserData() == "mummy"
		&& contact->IsTouching()) 
	{
		void* player = fixtureA->GetBody()->GetUserData();
		//static_cast<Player*>(player)->ModifyState(new PlayerStomp());
		static_cast<Player*>(player)->Bounce();

		void* mummy = fixtureB->GetBody()->GetUserData();
		static_cast<Mummy*>(mummy)->DecreaseHealth(6);
	}

	else if (fixtureA->GetUserData() == "mummy" 
		&& fixtureB->GetUserData() == "playerJumpSensor"
		&& contact->IsTouching()) 
	{
		void* mummy = fixtureA->GetBody()->GetUserData();
		static_cast<Mummy*>(mummy)->DecreaseHealth(6);
		
		void* player = fixtureB->GetBody()->GetUserData();
		//static_cast<Player*>(player)->ModifyState(new PlayerStomp());
		static_cast<Player*>(player)->Bounce();
	}

	
	if (fixtureA->GetUserData() == "player" 
		&& fixtureB->GetUserData() == "mummy"
		&& contact->IsTouching()) 
	{
		void* mummy = fixtureB->GetBody()->GetUserData();
		void* player = fixtureA->GetBody()->GetUserData();
		if(!static_cast<Mummy*>(mummy)->GetIsDead())
		{
			Player* p = static_cast<Player*>(player);
			p->DecreaseHealth(2);
		}
	}
	else if (fixtureA->GetUserData() == "mummy" 
		&& fixtureB->GetUserData() == "player"
		&& contact->IsTouching()) 
	{
		void* mummy = fixtureA->GetBody()->GetUserData();
		void* player = fixtureB->GetBody()->GetUserData();
		if(!static_cast<Mummy*>(mummy)->GetIsDead())
		{
			Player* p = static_cast<Player*>(player);
			p->DecreaseHealth(2);
		}
	}


	#pragma endregion

	#pragma region Bat and Player
	if (fixtureA->GetUserData() == "playerJumpSensor" 
		&& fixtureB->GetUserData() == "bat"
		&& contact->IsTouching()) 
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->Bounce();

		void* bat = fixtureB->GetBody()->GetUserData();
		static_cast<Bat*>(bat)->SetIsDead(true);
	}

	else if (fixtureA->GetUserData() == "bat" 
		&& fixtureB->GetUserData() == "playerJumpSensor"
		&& contact->IsTouching()) 
	{
		void* bat = fixtureA->GetBody()->GetUserData();
		static_cast<Bat*>(bat)->SetIsDead(true);

		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->Bounce();
	}

	
	if (fixtureA->GetUserData() == "player" 
		&& fixtureB->GetUserData() == "bat"
		&& contact->IsTouching()) 
	{
		void* bat = fixtureB->GetBody()->GetUserData();
		void* player = fixtureA->GetBody()->GetUserData();
		if(!static_cast<Bat*>(bat)->GetIsDead())
		{
			Player* p = static_cast<Player*>(player);
			p->DecreaseHealth(1);
			//p->SetInjured(true);
			//p->Kickback(static_cast<Bat*>(bat)->GetBody()->GetPosition());
		}
	}
	else if (fixtureA->GetUserData() == "bat" 
		&& fixtureB->GetUserData() == "player"
		&& contact->IsTouching()) 
	{
		void* bat = fixtureA->GetBody()->GetUserData();
		void* player = fixtureB->GetBody()->GetUserData();
		if(!static_cast<Bat*>(bat)->GetIsDead())
		{
			Player* p = static_cast<Player*>(player);
			p->DecreaseHealth(1);
			//p->SetInjured(true);
			//p->Kickback(static_cast<Bat*>(bat)->GetBody()->GetPosition());
		}
	}

		if (fixtureB->GetUserData() == "batCeilingSensor")
	{
		if ((	fixtureA->GetUserData() == "block" || 
				fixtureA->GetUserData() == "arrowTrap"|| 
				fixtureA->GetUserData() == "solidBlock") 
			&& contact->IsTouching())
		{
			void* bat = fixtureB->GetBody()->GetUserData();
			static_cast<Bat*>(bat)->SetOnCeiling(true);
		}
	}


	else if (fixtureA->GetUserData() == "batCeilingSensor")
	{
		if ((	fixtureB->GetUserData() == "block" || 
				fixtureB->GetUserData() == "arrowTrap"|| 
				fixtureA->GetUserData() == "solidBlock") 
			&& contact->IsTouching())
		{
			void* bat = fixtureA->GetBody()->GetUserData();
			static_cast<Bat*>(bat)->SetOnCeiling(true);
		}		
	}

	if (fixtureB->GetUserData() == "batPlayerSensor" && 
		fixtureA->GetUserData() == "player" && 
		contact->IsTouching())
	{
			void* bat = fixtureB->GetBody()->GetUserData();
			static_cast<Bat*>(bat)->SetPlayerIsClose(true);
			static_cast<Bat*>(bat)->SetPlayerBody(fixtureA->GetBody());
	}

	else if (fixtureA->GetUserData() == "batPlayerSensor" && 
			fixtureB->GetUserData() == "player" && 
			contact->IsTouching())
	{
			void* bat = fixtureA->GetBody()->GetUserData();
			static_cast<Bat*>(bat)->SetPlayerIsClose(true);
			static_cast<Bat*>(bat)->SetPlayerBody(fixtureB->GetBody());
	}


	#pragma endregion

	#pragma region Spike and Player

	if (fixtureA->GetUserData() == "player" 
		&& fixtureB->GetUserData() == "spike"
		&& contact->IsTouching()) 
	{
		void* spike = fixtureB->GetBody()->GetUserData();
		void* player = fixtureA->GetBody()->GetUserData();
		Player* p = static_cast<Player*>(player);
		p->Kickback(static_cast<Spikes*>(spike)->GetBody()->GetPosition());
		p->DecreaseHealth(1);
	}
	else if (fixtureA->GetUserData() == "spike" 
		&& fixtureB->GetUserData() == "player"
		&& contact->IsTouching()) 
	{
		void* spike = fixtureA->GetBody()->GetUserData();
		void* player = fixtureB->GetBody()->GetUserData();
		Player* p = static_cast<Player*>(player);
		p->Kickback(static_cast<Spikes*>(spike)->GetBody()->GetPosition());
		p->DecreaseHealth(1);
	}
	#pragma endregion

	#pragma region BombSensor and Blocks
	if (fixtureA->GetUserData() == "bombSensor" 
		&& fixtureB->GetUserData() == "block")
	{
		DirtBlock* block = (DirtBlock*)fixtureA->GetBody()->GetUserData();
		Bomb* bomb = (Bomb*)fixtureB->GetBody()->GetUserData();
		bomb->AddBlock(block);
	}
	else if (fixtureB->GetUserData() == "bombSensor" 
		&& fixtureA->GetUserData() == "block")
	{			
		DirtBlock* block = (DirtBlock*)fixtureA->GetBody()->GetUserData();
		Bomb* bomb = (Bomb*)fixtureB->GetBody()->GetUserData();
		bomb->AddBlock(block);
	}


	#pragma endregion 

	#pragma region Player and Door
	if (fixtureA->GetUserData() == "player" && fixtureB->GetUserData() == "doorMiddleSensorExit")
	{
		void* door = fixtureA->GetBody()->GetUserData();
		static_cast<Door*>(door)->setClose(true);
	}
	else if (fixtureB->GetUserData() == "player" && fixtureA->GetUserData() == "doorMiddleSensorExit")
	{
		void* door = fixtureA->GetBody()->GetUserData();
		static_cast<Door*>(door)->setClose(true);
	}
	#pragma endregion 

	#pragma region Player and Ladder

	if (fixtureA->GetUserData() == "player" && fixtureB->GetUserData() == "ladderLeftSensor")
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseRequiredLeftLadderContacts();
	}
	else if (fixtureB->GetUserData() == "player" && fixtureA->GetUserData() == "ladderLeftSensor")
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseRequiredLeftLadderContacts();
	}
	if (fixtureA->GetUserData() == "player" && fixtureB->GetUserData() == "ladderRightSensor")
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseRequiredRightLadderContacts();
	}
	else if (fixtureB->GetUserData() == "player" && fixtureA->GetUserData() == "ladderRightSensor")
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseRequiredRightLadderContacts();
	}

	if (fixtureA->GetUserData() == "topPlayerLadder" && fixtureB->GetUserData() == "ladder")
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseTopLadderContacts();
	}
	else if (fixtureB->GetUserData() == "topPlayerLadder" && fixtureA->GetUserData() == "ladder")
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->IncreaseTopLadderContacts();
	}
	
	#pragma endregion 

	#pragma region Player and Gold
	if (fixtureA->GetUserData() == "player" 
		&& fixtureB->GetUserData() == "gold") 
	{
		void* player = fixtureA->GetBody()->GetUserData();
		void* pickup = fixtureB->GetBody()->GetUserData();

		static_cast<Player*>(player)->IncreaseGold();
		static_cast<Pickup*>(pickup)->SetIsDead(true);
	}
	else if (fixtureA->GetUserData() == "gold" 
		&& fixtureB->GetUserData() == "player") 
	{
		void* player = fixtureB->GetBody()->GetUserData();
		void* pickup = fixtureA->GetBody()->GetUserData();
	
		static_cast<Player*>(player)->IncreaseGold();
		static_cast<Pickup*>(pickup)->SetIsDead(true);
	}


	if (fixtureA->GetUserData() == "player" 
		&& fixtureB->GetUserData() == "life") 
	{
		void* player = fixtureA->GetBody()->GetUserData();
		void* life = fixtureB->GetBody()->GetUserData();

		static_cast<Player*>(player)->IncreaseLives();
		static_cast<Life*>(life)->SetIsDead(true);
	}
	else if (fixtureA->GetUserData() == "life" 
		&& fixtureB->GetUserData() == "player") 
	{
		void* player = fixtureB->GetBody()->GetUserData();
		void* pickup = fixtureA->GetBody()->GetUserData();
		
		static_cast<Player*>(player)->IncreaseLives();
		static_cast<Pickup*>(pickup)->SetIsDead(true);
	}


	#pragma endregion

	#pragma region ArrowSensor and Player
	if (fixtureB->GetUserData() == "arrowSensor")
	{
		if (fixtureA->GetUserData() != "gold"
			&& fixtureA->GetUserData() != "ladder"
			&& fixtureA->GetUserData() != "arrowTrap"
			&& fixtureA->GetUserData() != "snake"	
			&& fixtureA->GetUserData() != "mummy"
			&& fixtureA->GetUserData() != "bat"
			&& fixtureA->GetUserData() != "batPlayerSensor"
			&& fixtureA->GetUserData() != "playerJumpSensor"
			&& fixtureA->GetUserData() != "playerSensor"
			&& fixtureA->GetUserData() != "topPlayerLadder" 
			&& fixtureA->GetUserData() != "scarab")
		{
			void* arrowTrap = fixtureB->GetBody()->GetUserData();
			static_cast<ArrowTrap*>(arrowTrap)->FireArrow();
		}
	}
	else if (fixtureA->GetUserData() == "arrowSensor")
	{
		if (fixtureB->GetUserData() != "gold"
			&& fixtureB->GetUserData() != "ladder"
			&& fixtureB->GetUserData() != "arrowTrap"
			&& fixtureB->GetUserData() != "snake"
			&& fixtureB->GetUserData() != "mummy"
			&& fixtureB->GetUserData() != "bat"
			&& fixtureB->GetUserData() != "batPlayerSensor"
			&& fixtureB->GetUserData() != "playerJumpSensor"
			&& fixtureB->GetUserData() != "playerSensor"
			&& fixtureB->GetUserData() != "topPlayerLadder"
			&& fixtureB->GetUserData() != "scarab")
		{
			void* arrowTrap = fixtureA->GetBody()->GetUserData();
			static_cast<ArrowTrap*>(arrowTrap)->FireArrow();
		}
	}
	#pragma endregion

}

void CollisionListener::EndContact(b2Contact* contact) 
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (fixtureA->GetUserData() == "playerSensor" && fixtureB->GetUserData() == "block") 
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseJumpContacts();
	}
	else if (fixtureA->GetUserData() == "block" && fixtureB->GetUserData() == "playerSensor") 
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseJumpContacts();
	}

	if (fixtureA->GetUserData() == "playerSensor" && fixtureB->GetUserData() == "solidBlock") 
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseJumpContacts();
	}
	else if (fixtureA->GetUserData() == "solidBlock" && fixtureB->GetUserData() == "playerSensor") 
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseJumpContacts();
	}

	if (fixtureA->GetUserData() == "playerSensor" 
		&& fixtureB->GetUserData() == "arrowTrap") 
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseJumpContacts();
	}

	else if (fixtureA->GetUserData() == "arrowTrap" 
		&& fixtureB->GetUserData() == "playerSensor") 
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseJumpContacts();
	}

	if (fixtureA->GetUserData() == "player" 
		&& fixtureB->GetUserData() == "switchSensor") 
	{
		void* s = fixtureB->GetBody()->GetUserData();
		static_cast<DoorSwitch*>(s)->setClose(false);
	}
	else if (fixtureA->GetUserData() == "switchSensor" 
		&& fixtureB->GetUserData() == "player") 
	{
		void* s = fixtureA->GetBody()->GetUserData();
		static_cast<DoorSwitch*>(s)->setClose(false);
	}


	if (fixtureA->GetUserData() == "bombSensor" 
		&& fixtureB->GetUserData() == "block")
	{
		DirtBlock* block = (DirtBlock*)fixtureA->GetBody()->GetUserData();
		Bomb* bomb = (Bomb*)fixtureB->GetBody()->GetUserData();
		bomb->RemoveBlock(block);
	}
	else if (fixtureB->GetUserData() == "bombSensor" 
		&& fixtureA->GetUserData() == "block")
	{			
		DirtBlock* block = (DirtBlock*)fixtureA->GetBody()->GetUserData();
		Bomb* bomb = (Bomb*)fixtureB->GetBody()->GetUserData();
		bomb->RemoveBlock(block);
	}

	if (fixtureA->GetUserData() == "player" && fixtureB->GetUserData() == "doorMiddleSensor")
	{
		void* door = fixtureA->GetBody()->GetUserData();
		static_cast<Door*>(door)->PlayClose();
	}
	else if (fixtureB->GetUserData() == "player" && fixtureA->GetUserData() == "doorMiddleSensor")
	{
		void* door = fixtureA->GetBody()->GetUserData();
		static_cast<Door*>(door)->PlayClose();
	}

	if (fixtureA->GetUserData() == "player" && fixtureB->GetUserData() == "doorMiddleSensorExit")
	{
		void* door = fixtureA->GetBody()->GetUserData();
		static_cast<Door*>(door)->setClose(false);
	}
	else if (fixtureB->GetUserData() == "player" && fixtureA->GetUserData() == "doorMiddleSensorExit")
	{
		void* door = fixtureA->GetBody()->GetUserData();
		static_cast<Door*>(door)->setClose(false);
	}

	if (fixtureA->GetUserData() == "player" && fixtureB->GetUserData() == "ladderLeftSensor")
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseRequiredLeftLadderContacts();
	}
	else if (fixtureB->GetUserData() == "player" && fixtureA->GetUserData() == "ladderLeftSensor")
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseRequiredLeftLadderContacts();
	}
	if (fixtureA->GetUserData() == "player" && fixtureB->GetUserData() == "ladderRightSensor")
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseRequiredRightLadderContacts();
	}
	else if (fixtureB->GetUserData() == "player" && fixtureA->GetUserData() == "ladderRightSensor")
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseRequiredRightLadderContacts();
	}

	if (fixtureA->GetUserData() == "topPlayerLadder" && fixtureB->GetUserData() == "ladder")
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseTopLadderContacts();
	}
	else if (fixtureB->GetUserData() == "topPlayerLadder" && fixtureA->GetUserData() == "ladder")
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseTopLadderContacts();
	}

	if (fixtureB->GetUserData() == "batCeilingSensor")
	{
		if ((	fixtureA->GetUserData() == "block" || 
				fixtureA->GetUserData() == "arrowTrap" || 
				fixtureA->GetUserData() == "solidBlock") )
		{
			void* bat = fixtureB->GetBody()->GetUserData();
			static_cast<Bat*>(bat)->SetOnCeiling(false);
		}
	}


	else if (fixtureA->GetUserData() == "batCeilingSensor")
	{
		if ((	fixtureB->GetUserData() == "block" || 
				fixtureB->GetUserData() == "arrowTrap"|| 
				fixtureA->GetUserData() == "solidBlock"))
		{
			void* bat = fixtureA->GetBody()->GetUserData();
			static_cast<Bat*>(bat)->SetOnCeiling(false);
		}		
	}


	if (fixtureB->GetUserData() == "batPlayerSensor" && 
		fixtureA->GetUserData() == "player" )
	{
			void* bat = fixtureB->GetBody()->GetUserData();
			static_cast<Bat*>(bat)->SetPlayerIsClose(false);
			static_cast<Bat*>(bat)->SetPlayerBody(NULL);
	}

	else if (fixtureA->GetUserData() == "batPlayerSensor" && 
			fixtureB->GetUserData() == "player")
	{
			void* bat = fixtureA->GetBody()->GetUserData();
			static_cast<Bat*>(bat)->SetPlayerIsClose(false);
			static_cast<Bat*>(bat)->SetPlayerBody(NULL);
	}



	/*
	if (fixtureA->GetUserData() == "topPlayerLadder" && fixtureB->GetUserData() == "ladder")
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseTopLadderContacts();
	}
	else if (fixtureB->GetUserData() == "topPlayerLadder" && fixtureA->GetUserData() == "ladder")
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseTopLadderContacts();
	}

	if (fixtureA->GetUserData() == "bottomPlayerLadder" && fixtureB->GetUserData() == "ladder")
	{
		void* player = fixtureA->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseBottomLadderContacts();
	}
	else if (fixtureB->GetUserData() == "bottomPlayerLadder" && fixtureA->GetUserData() == "ladder")
	{
		void* player = fixtureB->GetBody()->GetUserData();
		static_cast<Player*>(player)->DecreaseBottomLadderContacts();
	}
	*/
}

void CollisionListener::PreSolve(b2Contact* contact, 
								 const b2Manifold* oldManifold) 
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if ((fixtureA->GetUserData() && fixtureB->GetUserData()) &&
		fixtureA->GetUserData() == "mummy" ||
		fixtureA->GetUserData() == "snake" ||
		fixtureA->GetUserData() == "bat")
	{
		contact->SetEnabled(false);
	}



	#pragma region Arrow and Objects 
	if (fixtureB->GetUserData() == "arrow"  && fixtureA->GetUserData() != "arrowSensor" )
	{	

		if(fixtureA->GetUserData() == "player")
		{
			void* arrow = fixtureB->GetBody()->GetUserData();

			void* player = fixtureA->GetBody()->GetUserData();
			Player* p = static_cast<Player*>(player);


			if(!static_cast<Arrow*>(arrow)->GetIsBroken() && !p->GetBehindDoor())
			{
				static_cast<Arrow*>(arrow)->SetBroken();
				p->DecreaseHealth(2, "arrow");
				p->SetInjured(true);
				p->Kickback(static_cast<Arrow*>(arrow)->GetBody()->GetPosition());

				static_cast<Arrow*>(arrow)->GetBody()->SetLinearVelocity(b2Vec2(static_cast<Arrow*>(arrow)->GetBody()->GetLinearVelocity().x/5, 
																				static_cast<Arrow*>(arrow)->GetBody()->GetLinearVelocity().y));
			}

			else
			{
				contact->SetEnabled(false);
			}

		}

		else if(fixtureA->GetUserData() == "block" ||  fixtureA->GetUserData() == "solidBlock")
		{
			void* arrow = fixtureB->GetBody()->GetUserData();
			if(!static_cast<Arrow*>(arrow)->GetIsBroken())
			{
				static_cast<Arrow*>(arrow)->SetBroken();
			}

		}

		else if(fixtureA->GetUserData() == "mummy")
		{
			void* arrow = fixtureB->GetBody()->GetUserData();
			if(!static_cast<Arrow*>(arrow)->GetIsBroken())
			{
				static_cast<Arrow*>(arrow)->SetBroken();
				void* mummy = fixtureA->GetBody()->GetUserData();
				Mummy* m = static_cast<Mummy*>(mummy);
				m->DecreaseHealth(2);
			}

			else
			{
				contact->SetEnabled(false);
			}
		}
		else if(fixtureA->GetUserData() == "bat")
		{
			void* arrow = fixtureA->GetBody()->GetUserData();
				
			if(!static_cast<Arrow*>(arrow)->GetIsBroken())
			{
				static_cast<Arrow*>(arrow)->SetBroken();
				void* bat = fixtureB->GetBody()->GetUserData();
				Bat* b = static_cast<Bat*>(bat);
				b->SetIsDead(true);
			}
			else
			{
				contact->SetEnabled(false);
			}

		}



		else if(fixtureA->GetUserData() == "snake")
		{
			void* arrow = fixtureA->GetBody()->GetUserData();

			if(!static_cast<Arrow*>(arrow)->GetIsBroken())
			{
				static_cast<Arrow*>(arrow)->SetBroken();
				void* snake = fixtureB->GetBody()->GetUserData();
				Snake* s = static_cast<Snake*>(snake);
				s->SetIsDead(true);
			}
			else
			{
				contact->SetEnabled(false);
			}

		}

		else if (	fixtureA->GetUserData() == "ladder" ||

					fixtureA->GetUserData() == "gold" ||
					fixtureA->GetUserData() == "life" ||
					fixtureA->GetUserData() == "door" ||	
					fixtureA->GetUserData() == "switch"||
					fixtureA->GetUserData() ==  "switchSensor"||
					fixtureA->GetUserData() =="ladderLeftSensor"||
					fixtureA->GetUserData() == "ladderRightSensor")
		{
			contact->SetEnabled(false);
		}



	}



	else if (fixtureA->GetUserData() == "arrow" && fixtureB->GetUserData() != "arrowSensor")
	{
		if(fixtureB->GetUserData() == "player")
		{
			void* arrow = fixtureA->GetBody()->GetUserData();

			void* player = fixtureB->GetBody()->GetUserData();
			Player* p = static_cast<Player*>(player);

			if(!static_cast<Arrow*>(arrow)->GetIsBroken() && !p->GetBehindDoor())
			{
				static_cast<Arrow*>(arrow)->SetBroken();
				p->DecreaseHealth(2);
				p->SetInjured(true);
				p->Kickback(static_cast<Arrow*>(arrow)->GetBody()->GetPosition());
			}
			else
			{
				contact->SetEnabled(false);
			}


		}

		else if(fixtureB->GetUserData() == "block" ||  fixtureB->GetUserData() == "solidBlock")
		{
			void* arrow = fixtureA->GetBody()->GetUserData();
			if(!static_cast<Arrow*>(arrow)->GetIsBroken())
			{
				static_cast<Arrow*>(arrow)->SetBroken();
			}
		}


		else if(fixtureB->GetUserData() == "mummy")
		{
			void* arrow = fixtureA->GetBody()->GetUserData();
			if(!static_cast<Arrow*>(arrow)->GetIsBroken())
			{
				static_cast<Arrow*>(arrow)->SetBroken();
				void* mummy = fixtureB->GetBody()->GetUserData();
				Mummy* m = static_cast<Mummy*>(mummy);
				m->DecreaseHealth(2);
			}

			else
			{
				contact->SetEnabled(false);
			}

		}

		else if(fixtureB->GetUserData() == "bat")
		{
			void* arrow = fixtureA->GetBody()->GetUserData();

			if(!static_cast<Arrow*>(arrow)->GetIsBroken())
			{
				static_cast<Arrow*>(arrow)->SetBroken();
				void* bat = fixtureB->GetBody()->GetUserData();
				Bat* b = static_cast<Bat*>(bat);
				b->SetIsDead(true);
			}

			else
			{
				contact->SetEnabled(false);
			}


		}

		else if(fixtureB->GetUserData() == "snake")
		{
			void* arrow = fixtureA->GetBody()->GetUserData();
			
			if(!static_cast<Arrow*>(arrow)->GetIsBroken())
			{
				static_cast<Arrow*>(arrow)->SetBroken();
				void* snake = fixtureB->GetBody()->GetUserData();
				Snake* s = static_cast<Snake*>(snake);
				s->SetIsDead(true);
			}

			else
			{
				contact->SetEnabled(false);
			}

		}

		else if (	fixtureB->GetUserData() == "ladder" ||
					fixtureB->GetUserData() == "gold" ||
					fixtureB->GetUserData() == "door" )
		{
			contact->SetEnabled(false);
		}

	}
	#pragma endregion	

	#pragma region Enemies and Passable Objects
	if (fixtureB->GetUserData() == "bat"  || 
		fixtureB->GetUserData() == "snake" ||
		fixtureB->GetUserData() == "mummy")
	{	
		if (fixtureA->GetUserData() == "ladder" || 
			fixtureA->GetUserData() == "gold" || 
			fixtureA->GetUserData() == "door")
		{
			contact->SetEnabled(false);
		}
	}

	else if (	fixtureA->GetUserData() == "bat"  || 
				fixtureA->GetUserData() == "snake" ||
				fixtureA->GetUserData() == "mummy")
	{	
		if (fixtureB->GetUserData() == "ladder" || 
			fixtureB->GetUserData() == "gold" || 
			fixtureB->GetUserData() == "door")
		{
			contact->SetEnabled(false);
		}
	}
	#pragma endregion	

}

void CollisionListener::PostSolve(b2Contact* contact, 
								  const b2ContactImpulse* impulse) 
{
}