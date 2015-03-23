#include <Player.h>

FSM Player::s_fsm;

Player::Player(b2World* world, 
			   b2Vec2 dimensions, 
			   b2Vec2 position, 
			   SDL_Renderer* renderer,
			   Subject* subject,
			   MapManager *mapManager) 
			   : m_renderer(renderer), 
			   m_dimensions(dimensions), 
			   m_buttonXPrevPressed(false), 
			   m_buttonSPrevPressed(false),
			   m_numJumpContacts(0), 
			   m_isSprinting(false),
			   m_health(CONSTANTS::PLAYER_STARTING_HEALTH),
			   m_injured(false),
			   m_world(world),
			   m_numRequiredRightLadderContacts(0),
			   m_numRequiredLeftLadderContacts(0),
			   m_numTopLadderContacts(0),
			   m_numLadderAboveContacts(0),
			   m_onLadder(false),
			   m_shouldDraw(true),
			   m_direction("right"),
			   m_state(new PlayerIdle1()),
			   m_numHourglasses(0),
			   m_idleCounter(0),
			   m_subject(subject),
			   m_behindDoor(false),
			   m_mapManager(mapManager),
			   m_whipPrevUsed(false),
			   m_dying(false)
{

	 m_rewindPressed = false;
	 m_texture = SDL_CreateTextureFromSurface(m_renderer, IMG_Load("images/IdleAnimation/_0.png"));

	count = 0;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.userData = this;

	m_alive = true;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox((m_dimensions.x/2) * PIXELSTOMETRES, (m_dimensions.y / 2) * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.friction = 0;
	m_fixtureDef.userData = "player";
	m_fixtureDef.filter.groupIndex = -100;

	m_body->CreateFixture(&m_fixtureDef);

	m_sensorShape.SetAsBox( ( (m_dimensions.x/2) - 1) * PIXELSTOMETRES, 1 * PIXELSTOMETRES, b2Vec2(0, -(m_dimensions.y / 2)*PIXELSTOMETRES), 0);
	m_sensorDef.shape = &m_sensorShape;
	m_sensorDef.isSensor = true;
	m_sensorDef.userData = "playerSensor";
	m_body->CreateFixture(&m_sensorDef);

	m_frictionShape.SetAsBox(((m_dimensions.x/2) - 1) * PIXELSTOMETRES, 0, b2Vec2(0, -(m_dimensions.y / 2)*PIXELSTOMETRES), 0);
	m_frictionDef.shape = &m_frictionShape;
	m_frictionDef.friction = 0.5f;
	m_frictionDef.filter.groupIndex= -100;
	m_body->CreateFixture(&m_frictionDef);

	m_topLadderSensorShape.SetAsBox(1 * PIXELSTOMETRES, 1 * PIXELSTOMETRES, b2Vec2(0, ((m_dimensions.y / 2) + 1) * PIXELSTOMETRES), 0);
	m_topLadderSensorDef.isSensor = true;
	m_topLadderSensorDef.shape = &m_topLadderSensorShape;
	m_topLadderSensorDef.userData = "topPlayerLadder";
	m_body->CreateFixture(&m_topLadderSensorDef);

	m_jumpSensorShape.SetAsBox(((m_dimensions.x/2) - 4) * PIXELSTOMETRES, 10 * PIXELSTOMETRES, b2Vec2(0, -(m_dimensions.y / 2)*PIXELSTOMETRES), 0);
	m_jumpLadderSensorDef.isSensor = true;
	m_jumpLadderSensorDef.shape = &m_jumpSensorShape;
	m_jumpLadderSensorDef.userData = "playerJumpSensor";
	m_body->CreateFixture(&m_jumpLadderSensorDef);

	m_buttonLeft	= new LeftCommand();
	m_buttonRight	= new RightCommand();
	m_buttonX		= new JumpCommand();

	m_memento = new Memento();

	m_packetStream = new PacketStream();
	m_subject->AddObserver(this);
	m_type = "Player";

	whipping = false;
}

Player::~Player() 
{
	delete m_memento;
	delete m_packetStream;
	delete m_buttonLeft;
	delete m_buttonRight;
	delete m_buttonX;
}

bool Player::Update(double deltatime) 
{
	m_event = "None";
	count = 0;
	bool bombExploded=false;
	
	if (m_injured && 0 == m_body->GetLinearVelocity().Length())
	{
		m_injured = false;
	}
	for (std::vector<Bomb*>::iterator iter = bombs.begin(); iter != bombs.end();)
	{
		if ((*iter)->alive) 
		{
			if((*iter)->Update(deltatime))
			{
				bombExploded = true;
				explosions.push_back(new Explosion(m_renderer,b2Vec2((*iter)->getBody()->GetPosition().x,(*iter)->getBody()->GetPosition().y)));
				explosions.at(count)->setAlive(true);
				(*iter)->DeleteBody();
				m_subject->Notify("player bomb exploded");
			}
			++iter;
		}
		else
		{
			iter = bombs.erase(iter);
		}
		count++;
	}


	for (std::vector<Explosion*>::iterator iter2 = explosions.begin(); iter2 != explosions.end();)
	{
		if ((*iter2)->getFinished())
		{
			iter2 = explosions.erase(iter2);
		}
		else
		{
			++iter2;
		}
	}



	for (std::vector<Explosion*>::iterator iter2 = explosions.begin(); iter2 != explosions.end();)
	{
		if ((*iter2)->getFinished())
		{
			iter2 = explosions.erase(iter2);
		}
		else
		{
			++iter2;
		}
	}

	if (!KeyboardManager::getKeys()->Key_R)
	{
		m_memento->PushToPositionsList(m_body->GetPosition());
	}
	m_state->Update(*this);

	if(m_mapManager->GetLives() <= 0 && !m_dying)
	{
		m_state = new PlayerDying();
		m_dying = true;
	}


	HandleInput();
	return bombExploded;
}

bool Player::CheckDead()
{
	return m_mapManager->CheckPlayerDead();
}

void Player::HandleInput() 
{
	PlayerState* state = m_state->HandleInput(*this);
	if(!m_dying)
	{
		if (state != NULL)
		{
			delete m_state;
			m_state = state;
		}
	}


	if (!KeyboardManager::getKeys()->Key_Space) 
	{
		m_buttonXPrevPressed = false;
	}
	

	m_isSprinting = KeyboardManager::getKeys()->Key_Shift ? true : false;

	if ((m_numRequiredRightLadderContacts >= 1 
		&& m_numRequiredLeftLadderContacts >= 1)  
		&& KeyboardManager::getKeys()->Key_Up
		&& !m_onLadder)
	{
		m_onLadder = true;
		m_body->SetLinearVelocity(b2Vec2(0, 0));
	}

	if (KeyboardManager::getKeys()->Key_Up && m_onLadder && m_numTopLadderContacts > 0)
	{
		m_body->SetLinearVelocity(b2Vec2(m_body->GetLinearVelocity().x, 100 * PIXELSTOMETRES));
	}
	else if (KeyboardManager::getKeys()->Key_Down && m_onLadder)
	{
		m_body->SetLinearVelocity(b2Vec2(m_body->GetLinearVelocity().x, -100 * PIXELSTOMETRES));
	}
	else if (m_onLadder)
	{
		m_body->SetLinearVelocity(b2Vec2(m_body->GetLinearVelocity().x, 0));
	}
	if (m_onLadder 
		&& (m_numRequiredRightLadderContacts < 1 
		|| m_numRequiredLeftLadderContacts < 1))
	{
		m_onLadder = false;
	}
}
bool Player::UpdateNetworkPlayers(double deltatime)
{
	bool bombExploded=false;
	for (std::vector<Bomb*>::iterator iter = bombs.begin(); iter != bombs.end();)
	{
		if ((*iter)->alive) 
		{
			if((*iter)->Update(deltatime))
			{
				bombExploded = true;
			}
			++iter;
		}
		else
		{
			iter = bombs.erase(iter);
		}
	}
	return bombExploded;
}
PacketStream* Player::Serialize()
{
	m_packetStream->clearString();
	m_packetStream->writeString("update");
	m_packetStream->writeFloat(m_body->GetPosition().x);
	m_packetStream->writeFloat(m_body->GetPosition().y);
	m_packetStream->writeFloat(m_body->GetLinearVelocity().x);
	m_packetStream->writeFloat(m_body->GetLinearVelocity().y);
	
	return m_packetStream;
}
void Player:: AppendNextLevel()
{
	m_packetStream->writeString("nextlevel");
}
void Player::AppendBombToPStream(b2Vec2 pos, b2Vec2 dir)
{
	m_packetStream->writeString("bomb");
	m_packetStream->writeFloat(pos.x);
	m_packetStream->writeFloat(pos.y);
	m_packetStream->writeFloat(dir.x);
	m_packetStream->writeFloat(dir.y);	
}
void Player::AppendDoorOpen()
{
	m_packetStream->writeString("dooropen");
}
void Player::AppendGameOver()
{
	m_packetStream->writeString("restart");
}
vector<string> Player::splitString(std::string s){
	string buf; // Have a buffer string
	stringstream ss(s); // Insert the string into a stream

	vector<string> tokens; // Create vector to hold our words

	while (ss >> buf)
		tokens.push_back(buf);

	return tokens;
}
std::tuple<bool,bool,bool> Player::Deserialize(PacketStream* pStream){
	std::tuple<bool,bool,bool> tup = make_tuple(true,true,true);
	bool nextLevel = false;
	bool doorOpen = false;
	bool gameOver = false;
	vector<string> listOfStrings = splitString(pStream->m_string);

	b2Vec2 pos(pStream->readFloat(listOfStrings.at(1)),pStream->readFloat(listOfStrings.at(2)));
	b2Vec2 vel(pStream->readFloat(listOfStrings.at(3)),pStream->readFloat(listOfStrings.at(4)));

	m_body->SetTransform(pos,m_body->GetAngle());
	m_body->SetLinearVelocity(vel);
	for(int i = 4; i < listOfStrings.size(); ++i)
	{
		if(listOfStrings.at(i) == "texture")
		{
			SetCurrentImage(listOfStrings.at(i+1),pStream->readInt(listOfStrings.at(i+2)));
		}
		else if(listOfStrings.at(i) == "bomb")
		{
			b2Vec2 bombPos(pStream->readFloat(listOfStrings.at(i+1)),pStream->readFloat(listOfStrings.at(i+2)));
			b2Vec2 bombDir(pStream->readFloat(listOfStrings.at(i+3)),pStream->readFloat(listOfStrings.at(i+4)));
			bombs.push_back(new Bomb(m_world,m_renderer,b2Vec2(25,40),bombPos,bombDir));
		}
		else if(listOfStrings.at(i) == "nextlevel")
		{
			nextLevel = true;
		}
		else if(listOfStrings.at(i) == "dooropen")
		{
			doorOpen = true;
		}
		else if(listOfStrings.at(i) == "restart")
		{
			gameOver = true;
		}
	}
	
	return make_tuple(nextLevel,doorOpen,gameOver);
	
}
void Player::Render(b2Vec2 offset) 
{
	SDL_Rect stretchRect;
	stretchRect.x = (m_body->GetPosition().x * METRESTOPIXELS)  - (m_dimensions.x/2) - offset.x;
	stretchRect.y = (-m_body->GetPosition().y * METRESTOPIXELS)  - (m_dimensions.y/2) + offset.y;
	stretchRect.w = m_dimensions.x;
	stretchRect.h = m_dimensions.y;
	SDL_RendererFlip flip;

	if(m_shouldDraw)
	{
		if(m_behindDoor)
		{
			m_behindDoor = false;
		}

		if(m_direction == "right")
		{
			flip = SDL_RendererFlip::SDL_FLIP_NONE;
		}
		else if(m_direction == "left")
		{
			flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		}
		
		SDL_RenderCopyEx ( m_renderer, m_texture, NULL, &stretchRect, 0, NULL, flip);

		if(whipping == true)
		{
			int whipOffsetX = 0;
			int whipOffsetY = 4;
			if(m_direction == "right")
			{
				whipOffsetX = 0;
			}
			else if(m_direction == "left")
			{
				whipOffsetX = 90;
			}
			SDL_Rect stretchRectWhip;
			stretchRectWhip.x = ((m_body->GetPosition().x * METRESTOPIXELS)  - (m_dimensions.x/2) - offset.x) - whipOffsetX;
			stretchRectWhip.y = ((-m_body->GetPosition().y * METRESTOPIXELS)  - (m_dimensions.y/2) + offset.y) - whipOffsetY;
			stretchRectWhip.w = m_dimensions.x * 4;
			stretchRectWhip.h = m_dimensions.y;
			SDL_RenderCopyEx ( m_renderer, m_whipTexture, NULL, &stretchRectWhip, 0, NULL, flip);
		}
	}

	else
	{
		if(!m_behindDoor)
		{
			m_behindDoor = true;
			for (b2Fixture* f = m_body->GetFixtureList(); f; )
			{
				b2Fixture* fixtureToModify = f;
				f = f->GetNext();
				b2Filter fil;
				fil.groupIndex = 0;
				fixtureToModify->SetFilterData(fil);
			}
		}
	}
	
	for(std::vector<Bomb*>::iterator iter = bombs.begin(); iter != bombs.end(); ++iter)
	{
		(*iter)->Render(offset);
	}
}


void Player::RenderExplosion(b2Vec2 offset)
{
	for (std::vector<Explosion*>::iterator iter2 = explosions.begin(); iter2 != explosions.end(); ++iter2)
	{
		(*iter2)->Render(offset);
	}
}

void Player::IncreaseLives()
{
	m_mapManager->AddLife();
}

void Player::setDraw(bool set)
{
	m_shouldDraw = set;
}

void Player::SetAlive(bool alive)
{
	m_alive = alive;
	if (!m_alive)
	{
		m_mapManager->SetDead();
	}
}

void Player::SetLinearVelocity(b2Vec2 vel) 
{
	m_body->SetLinearVelocity(b2Vec2(vel.x, m_body->GetLinearVelocity().y));
}

void Player::ApplyForceToCenter(b2Vec2 vel) 
{
	m_body->SetLinearVelocity(vel);
}

b2Vec2 Player::GetPosition() 
{
	return m_body->GetPosition();
}

int Player::GetIdleCounter() 
{
	return m_idleCounter;
}

void Player::SetIdleCounter(int theIdleCounter) 
{
	m_idleCounter = theIdleCounter;
}

int Player::GetHourglasses()
{
	return m_numHourglasses;
}

void Player::SetWhipping(bool theWhipping)
{
	whipping = theWhipping;
}

void Player::DecreaseHealth(int difference)
{
	//m_health -= difference;
	m_mapManager->DecreseHealth(difference);
}

void Player::DecreaseHealth(int difference, char* cause)
{
	//m_health -= difference;
	m_mapManager->DecreseHealth(difference);
	if (cause == "arrow")
	{
		m_subject->Notify("player shot with arrow");
	}
}

void Player::IncreaseJumpContacts() 
{
	++m_numJumpContacts;
}

void Player::DecreaseJumpContacts() 
{
	--m_numJumpContacts;
}

void Player::Bounce()
{
	m_body->SetLinearVelocity(b2Vec2(m_body->GetLinearVelocity().x, 600 * PIXELSTOMETRES));
}

void Player::Kickback(b2Vec2 position)
{
	if(m_mapManager->GetLives() > 0)
	{
		int i;
		i = position.x > m_body->GetPosition().x ? -250 : 250;
		m_body->SetLinearVelocity(b2Vec2(i * PIXELSTOMETRES, 800 * PIXELSTOMETRES));
	}
}

void Player::SetInjured(bool toggle)
{
	m_injured = toggle;
}

void Player::IncreaseRequiredRightLadderContacts() 
{
	++m_numRequiredRightLadderContacts;
}

void Player::DecreaseRequiredRightLadderContacts() 
{
	--m_numRequiredRightLadderContacts;
}

void Player::IncreaseRequiredLeftLadderContacts() 
{
	++m_numRequiredLeftLadderContacts;
}

void Player::DecreaseRequiredLeftLadderContacts() 
{
	--m_numRequiredLeftLadderContacts;
}

void Player::IncreaseTopLadderContacts() 
{
	++m_numTopLadderContacts;
}

void Player::DecreaseTopLadderContacts() 
{
	--m_numTopLadderContacts;
}

void Player::IncreaseLadderAboveContacts() 
{
	++m_numLadderAboveContacts;
}

void Player::DecreaseLadderAboveContacts() 
{
	--m_numLadderAboveContacts;
}

void Player::DecreaseNumBombs()
{
	m_mapManager->DecreaseNumBombs();
}

void Player::IncreaseGold() 
{
	if(m_alive)
	{
		m_mapManager->IncreaseGold();
		m_state = new PlayerGrab();
	}
}

void Player::Rewind()
{
	m_subject->Notify("rewinding");
	m_body->SetTransform(m_memento->PopFromPositionsList(), 0);
}


void Player::SetLook(std::string look)
{
	m_direction = look;
}
std::string Player::GetLook()
{
	return m_direction;
}

void Player::InceraseNumHourglasses()
{
	m_rewindPressed = false;
	++m_numHourglasses;
}

void Player::SetCurrentImage(std::string type, int index)
{
	m_packetStream->writeString("texture");
	m_packetStream->writeString(type);
	m_packetStream->writeInt(index);

if(TileBase::getBase()->GetPlayer() == "Guy")
	{
		if(type == "running")
		{
			m_texture = TileBase::m_runningTexturesM.at(index);
		}	
		else if(type == "idle1")
		{
			m_texture = TileBase::m_idle1TexturesM.at(index);
		}
		else if(type == "idle2")
		{
			m_texture = TileBase::m_idle2TexturesM.at(index);
		}
		else if(type == "idle3")
		{
			m_texture = TileBase::m_idle3TexturesM.at(index);
		}
		else if(type == "death")
		{
			m_texture = TileBase::m_deathTexturesM.at(index);
		}
		else if(type == "climbladder")
		{
			m_texture = TileBase::m_climbTexturesM.at(index);
		}			
		else if(type == "whip")
		{
			m_texture = TileBase::m_whipTexturesPlayerM.at(index);
			m_whipTexture = TileBase::m_whipTexturesWhip.at(index);
		}		
		else if(type == "jumping")
		{
			m_texture = TileBase::m_jumpTexturesM.at(index);
		}
		else if(type == "throwbomb")
		{
			m_texture = TileBase::m_bombThrowTexturesM.at(index);
		}
		else if(type == "sprinting")
		{
			m_texture = TileBase::m_sprintTexturesM.at(index);
		}
		else if(type == "dying")
		{
			m_texture = TileBase::m_deathTexturesM.at(index);
		}
		else if(type == "sprintjumping")
		{
			m_texture = TileBase::m_sprintJumpTexturesM.at(index);
		}
		else if(type == "loot")
		{
			m_texture = TileBase::m_lootGrabTexturesM.at(index);
		}

		else if(type == "bite")
		{
			m_texture = TileBase::m_snakeBiteTexturesM.at(index);
		}
		else if(type == "bat scare")
		{
			m_texture = TileBase::m_batFearTexturesM.at(index);
		}
		else if(type == "landing")
		{
			m_texture = TileBase::m_landingTexturesM.at(index);
		}
	}


	if(TileBase::getBase()->GetPlayer() == "Girl")
	{
		if(type == "running")
		{
			m_texture = TileBase::m_runningTexturesF.at(index);
		}	
		else if(type == "idle1")
		{
			m_texture = TileBase::m_idle1TexturesF.at(index);
		}
		else if(type == "idle2")
		{
			m_texture = TileBase::m_idle2TexturesF.at(index);
		}
		else if(type == "idle3")
		{
			m_texture = TileBase::m_idle3TexturesF.at(index);
		}
		else if(type == "death")
		{
			m_texture = TileBase::m_deathTexturesF.at(index);
		}
		else if(type == "climbladder")
		{
			m_texture = TileBase::m_climbTexturesF.at(index);
		}			
		else if(type == "whip")
		{
			m_texture = TileBase::m_whipTexturesPlayerF.at(index);
			m_whipTexture = TileBase::m_whipTexturesWhip.at(index);
		}		
		else if(type == "jumping")
		{
			m_texture = TileBase::m_jumpTexturesF.at(index);
		}
		else if(type == "throwbomb")
		{
			m_texture = TileBase::m_bombThrowTexturesF.at(index);
		}
		else if(type == "sprinting")
		{
			m_texture = TileBase::m_sprintTexturesF.at(index);
		}
		else if(type == "dying")
		{
			m_texture = TileBase::m_deathTexturesF.at(index);
		}
		else if(type == "sprintjumping")
		{
			m_texture = TileBase::m_sprintJumpTexturesF.at(index);
		}
		else if(type == "loot")
		{
			m_texture = TileBase::m_lootGrabTexturesF.at(index);
		}

		else if(type == "bite")
		{
			m_texture = TileBase::m_snakeBiteTexturesF.at(index);
		}
		else if(type == "bat scare")
		{
			m_texture = TileBase::m_batFearTexturesF.at(index);
		}
		else if(type == "landing")
		{
			m_texture = TileBase::m_landingTexturesF.at(index);
		}

	}
}

int Player::GetBombs()
{
	return m_mapManager->GetBombs();
}

bool Player::GetOnGround() const
{
	bool l_onGround;

	m_numJumpContacts > 0 ? l_onGround = true : l_onGround = false;

	return l_onGround;
}

bool Player::GetOnLadder() const
{
	return m_onLadder;
}

bool Player::GetMovesUpLadder() const
{
	if(m_body->GetLinearVelocity().y > 0  &&
		m_onLadder)
	{
		return true;
	}

	return false;
}

bool Player::GetMovesDownLadder() const
{
	if(m_body->GetLinearVelocity().y < 0  &&
		m_onLadder)
	{
		return true;
	}

	return false;
}

void Player::DropBomb()
{
	int xForce = m_direction == string("right") ? 10 : -10;
	bombs.push_back(new Bomb(	m_world,
								m_renderer,b2Vec2(25,40),
								b2Vec2(	m_body->GetPosition().x * METRESTOPIXELS,
										m_body->GetPosition().y * METRESTOPIXELS), 
								b2Vec2(xForce,10)));
	AppendBombToPStream(b2Vec2(	m_body->GetPosition().x * METRESTOPIXELS,
										m_body->GetPosition().y * METRESTOPIXELS), 
								b2Vec2(xForce,10));
}

b2Vec2 Player::GetVelocity()const 
{
	return m_body->GetLinearVelocity();
}

bool Player::GetCanJump() const
{
	return !m_buttonSPrevPressed;
}

bool Player::CanThrowBomb()
{
	return !m_buttonSPrevPressed;
}

void Player::UseWhip()
{
	SoundManager::getSoundManager()->PlayWhipCrack();
	m_subject->Notify("player whipped");
	RayCastListener* m_raycast = new RayCastListener();
	if (m_direction == "right")
	{
		m_world->RayCast(m_raycast, m_body->GetPosition(), b2Vec2(m_body->GetPosition().x + (75 * PIXELSTOMETRES), m_body->GetPosition().y + ((m_dimensions.y / 2) * PIXELSTOMETRES)));
		m_world->RayCast(m_raycast, m_body->GetPosition(), b2Vec2(m_body->GetPosition().x + (75 * PIXELSTOMETRES), m_body->GetPosition().y));
		m_world->RayCast(m_raycast, m_body->GetPosition(), b2Vec2(m_body->GetPosition().x + (75 * PIXELSTOMETRES), m_body->GetPosition().y - ((m_dimensions.y / 2) * PIXELSTOMETRES)));
	}
	else
	{
		m_world->RayCast(m_raycast, m_body->GetPosition(), b2Vec2(m_body->GetPosition().x - (75 * PIXELSTOMETRES), m_body->GetPosition().y + ((m_dimensions.y / 2) * PIXELSTOMETRES)));
		m_world->RayCast(m_raycast, m_body->GetPosition(), b2Vec2(m_body->GetPosition().x - (75 * PIXELSTOMETRES), m_body->GetPosition().y));
		m_world->RayCast(m_raycast, m_body->GetPosition(), b2Vec2(m_body->GetPosition().x - (75 * PIXELSTOMETRES), m_body->GetPosition().y - ((m_dimensions.y / 2) * PIXELSTOMETRES)));
	}
	delete m_raycast;
}

void Player::SetBehindDoor(bool toggle)
{
	m_behindDoor = toggle;
}

bool  Player::GetBehindDoor() const
{
	return m_behindDoor;
}

void Player::ExecuteLeftCommand()
{
	if (!m_injured)
	{
		m_buttonLeft->execute(this, m_isSprinting); //KEVIN - TODO - Implement command here properly.
	}

	else
	{
		SetLinearVelocity(b2Vec2(0, m_body->GetLinearVelocity().y));
	}
}

void Player::ExecuteRightCommand()
{
	if (!m_injured)
	{
		m_buttonRight->execute(this, m_isSprinting);
	}
	else
	{
		SetLinearVelocity(b2Vec2(0, m_body->GetLinearVelocity().y));
	}

}
void Player::ExecuteXCommand()
{
	if ((m_numJumpContacts > 0 && !m_buttonXPrevPressed && !m_injured)
		|| (m_onLadder && !m_buttonXPrevPressed)) 
	{
		m_buttonX->execute(this, m_isSprinting);
		m_buttonXPrevPressed = true;
		m_onLadder = false;
	}

}

void Player::ModifyState(PlayerState *newState)
{
	if(!m_dying)
	{
		delete m_state;
		m_state = newState;	
	}	
}

void Player::SetGravityScale(float f)
{
	m_body->SetGravityScale(f);
}