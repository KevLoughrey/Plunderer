#include <MultiplayerGame.h>
#include <EnemyManager.h>

MultiplayerGame::MultiplayerGame(SDL_Renderer* renderer,
								 b2World* bworld, 
								 std::string myName, 
								 std::string friendName,
								 Subject* subject,
								 MapManager* mapManager) 
	: m_renderer(renderer), 
	m_world(bworld),
	PORT(80),
	gameState(WAITING),
	m_myName(myName),
	m_friendsName(friendName),
	mySeed(0),
	m_subject(subject),
	m_restart(false),
	m_mapManager(mapManager),
	m_gameOver(false)
{
	playerInfo = std::vector<std::pair<int,std::string>>();
	m_serverHelper = new ServerHelper();
	ip = m_serverHelper->GetIPAddress();
	
  
	char cIPAddress[20];
	strcpy(cIPAddress,ip.c_str());

	//setup net using ip
	mNet = new Net();
	mNet->initialise();
	mNet->setupUDP(PORT, cIPAddress);

	
	std::string seedAsDouble = m_serverHelper->PostNameToServer(ip,PORT,m_myName,m_friendsName);
	mySeed = std::stod(seedAsDouble);

}
MultiplayerGame::MultiplayerGame(SDL_Renderer *renderer, b2World *bWorld, std::string myName, std::string friendName, Subject* subject, MapManager *mapManager,
					std::string myIP, ::string friendIP, int port)
					: m_renderer(renderer), 
	m_world(bWorld),
	PORT(port),
	gameState(PLAYING),
	m_myName(myName),
	m_friendsName(friendName),
	mySeed(0),
	m_subject(subject),
	m_restart(false),
	m_mapManager(mapManager),
	m_gameOver(false)
{
	playerInfo = std::vector<std::pair<int,std::string>>();
	playerInfo.push_back(std::pair<int, std::string>(port,friendIP));

	char cIPAddress[20];
	strcpy(cIPAddress,myIP.c_str());

	mNet = new Net();
	mNet->initialise();
	mNet->setupUDP(PORT, cIPAddress);

	Setup();
}
MultiplayerGame::~MultiplayerGame()
{
	EnemyManager::Instance()->DestroyAll();
	for (int i = 0; i < m_blocks.size(); ++i) 
	{
		if (m_blocks.at(i)->ShouldRemove())
		{
			m_blocks.at(i)->DestroyBody();
		}
	}

	//delete m_player;
	/*delete m_mapManager;*/
	/*delete m_rewindTexture1;
	delete m_rewindTexture2;
	delete m_rewindTexture3;
	delete m_rewindTexture4;*/
	delete m_endDoor;
	delete m_hud;
	
	for(int i = 0; i < m_blocks.size(); ++i)
	{
		delete m_blocks.at(i);
	}	
	for (int i = 0; i < m_bgBlocks.size(); ++i)
	{
		delete m_bgBlocks.at(i);	
	}
	delete m_startDoor;	

	for (int i = 0; i < m_bgBlocksOnes.size(); ++i)
	{
		delete m_bgBlocksOnes.at(i);	
	}
	for(int i = 0; i < m_ladders.size(); ++i)
	{
		delete m_ladders.at(i);
	}
	for(int i =0; i < m_pickUps.size(); ++i)
	{
		delete m_pickUps.at(i);
	}
	for(int i =0; i < m_spikes.size(); ++i)
	{
		delete m_spikes.at(i);
	}	
	for(int i =0; i < m_arrowTraps.size(); ++i)
	{
		delete m_arrowTraps.at(i);
	}
	for(int i =0; i < m_torches.size(); ++i)
	{
		delete m_torches.at(i);
	}	
	mNet->cleanup();
}
std::pair<bool,bool> MultiplayerGame::EndGame()
{
	return std::pair<bool,bool>(m_mapManager->GetLives() <= 0, m_gameOver);
}
std::pair<int,string> MultiplayerGame::GetFriendInfo()
{
	return std::pair<int,string>(playerInfo.at(0).first,playerInfo.at(0).second);
}
std::pair<int,string> MultiplayerGame::GetMyInfo()
{
	return std::pair<int,string>(playerInfo.at(0).first,ip);
}
void MultiplayerGame::CheckPickupDead()
{
	for (int i = 0; i < m_pickUps.size(); ++i) 
	{
		if (m_pickUps.at(i)->GetIsDead()) 
		{
			delete m_pickUps.at(i);
			m_pickUps.erase(m_pickUps.begin() + i);
		}
	}
}
bool MultiplayerGame::CheckRestart()
{
	return m_restart;
}
void MultiplayerGame::GoToNextLevel()
{
	m_restart = false;
	EnemyManager::Instance()->DestroyAll();
	for (int i = 0; i < m_blocks.size(); ++i) 
	{
		if (m_blocks.at(i)->ShouldRemove())
		{
			m_blocks.at(i)->DestroyBody();
		}
	}

	//delete m_player;
	/*delete m_mapManager;*/
	/*delete m_rewindTexture1;
	delete m_rewindTexture2;
	delete m_rewindTexture3;
	delete m_rewindTexture4;*/
	delete m_endDoor;
	delete m_hud;
	
	for(int i = 0; i < m_blocks.size(); ++i)
	{
		delete m_blocks.at(i);
	}	
	for (int i = 0; i < m_bgBlocks.size(); ++i)
	{
		delete m_bgBlocks.at(i);	
	}
	delete m_startDoor;	

	for (int i = 0; i < m_bgBlocksOnes.size(); ++i)
	{
		delete m_bgBlocksOnes.at(i);	
	}
	for(int i = 0; i < m_ladders.size(); ++i)
	{
		delete m_ladders.at(i);
	}
	for(int i =0; i < m_pickUps.size(); ++i)
	{
		delete m_pickUps.at(i);
	}
	for(int i =0; i < m_spikes.size(); ++i)
	{
		delete m_spikes.at(i);
	}	
	for(int i =0; i < m_arrowTraps.size(); ++i)
	{
		delete m_arrowTraps.at(i);
	}
	for(int i =0; i < m_torches.size(); ++i)
	{
		delete m_torches.at(i);
	}	
	
	
}
void MultiplayerGame::Setup()
{	
	m_endLevel = false;
	m_bgBlocks = std::vector<BgBlock*>();
	m_bgBlocksOnes= std::vector<BgBlock*>();
	m_blocks = std::vector<DirtBlock*>();
	m_ladders = std::vector<Ladder*>();
	m_torches = std::vector<Torch*>();
	m_pickUps = std::vector<Pickup*>();
	m_spikes = std::vector<Spikes*>();
	m_arrowTraps = std::vector<ArrowTrap*>();
	
	std::vector<b2Vec2> positions = m_mapManager->BuildLevel();
	std::vector<int> types = m_mapManager->getTypes();
	std::vector<b2Vec2> bgPositions = m_mapManager->getBgPositions();
	std::vector<int> bgTypes = m_mapManager->getBgTypes();
	std::vector<int> blockHeights = m_mapManager->getBlockHeights();
	m_doorSwitch = new DoorSwitch(m_world,m_renderer,m_mapManager->GetSwitchPos());
	m_startDoor = new Door(m_world,m_renderer,m_mapManager->GetStartPoint(),1,m_doorSwitch);
	m_endDoor = new Door(m_world,m_renderer,m_mapManager->GetEndPoint(),3,m_doorSwitch);
	m_player = new Player(m_world, b2Vec2(30, 45), m_mapManager->GetStartPoint(), m_renderer, m_subject,m_mapManager);
	m_networkPlayer = new Player(m_world, b2Vec2(30, 45), m_mapManager->GetStartPoint(), m_renderer, m_subject,m_mapManager);
	m_hud = new HUD(m_renderer, m_mapManager);
	m_enemyFactory = new EnemyFactory;
	
	std::vector<b2Vec2> pos = m_mapManager->getBgPosOnes();
	std::vector<int> bgTypesOnes = m_mapManager->getBgTypesOnes();

	for (int k = 0; k < pos.size(); ++k)
	{
		m_bgBlocksOnes.push_back(new BgBlock(m_renderer, pos.at(k), bgTypesOnes.at(k)));
	}
	for (int x = 0; x < bgPositions.size(); ++x)
	{
		m_bgBlocks.push_back(new BgBlock(m_renderer,bgPositions.at(x),bgTypes.at(x)));
	}
	for (int i = 0; i < positions.size(); ++i)
	{
		if(types.at(i) == 0)
		{
			m_blocks.push_back(new DirtBlock(m_world,b2Vec2(50,50), positions.at(i), m_renderer, 0));
		}
		else if(types.at(i) == 60)
		{
			m_blocks.push_back(new DirtBlock(m_world,b2Vec2(50,50), positions.at(i), m_renderer,types.at(i)));
		}
		else if (types.at(i) == 2)
		{	
			GenerateEnemy(positions.at(i),types.at(i));
		}
		else if (types.at(i) == 3)
		{	
			GenerateEnemy(positions.at(i),types.at(i));
		}
		else if (types.at(i) == 4)
		{	
			GenerateEnemy(positions.at(i),types.at(i));
		}
		else if (types.at(i) == 20)
		{
			m_ladders.push_back(new Ladder(m_world,b2Vec2(50,50),positions.at(i),m_renderer));
		}
		else if (types.at(i) == 21)
		{
			m_pickUps.push_back(new Pickup(m_world,b2Vec2(35,30),positions.at(i),m_renderer,m_subject));
		}
		else if (types.at(i) == 22)
		{
			m_spikes.push_back(new Spikes(m_world,b2Vec2(45,40),positions.at(i),m_renderer));
		}
		else if (types.at(i) == 23)
		{
			m_arrowTraps.push_back(new ArrowTrap(m_world,b2Vec2(50,50),positions.at(i),m_renderer,types.at(i)));
		}
		else if (types.at(i) == 24)
		{
			m_arrowTraps.push_back(new ArrowTrap(m_world,b2Vec2(50,50),positions.at(i),m_renderer,types.at(i)));
		}
		else if (types.at(i) == 17)
		{
			m_torches.push_back(new Torch(m_renderer,positions.at(i)));
		}
	}	

	m_rewindTexture1 = SDL_CreateTextureFromSurface(m_renderer, IMG_Load("images/Sepia1.png"));
	m_rewindTexture2 = SDL_CreateTextureFromSurface(m_renderer, IMG_Load("images/Sepia2.png"));
	m_rewindTexture3 = SDL_CreateTextureFromSurface(m_renderer, IMG_Load("images/Sepia3.png"));
	m_rewindTexture4 = SDL_CreateTextureFromSurface(m_renderer, IMG_Load("images/Sepia4.png"));
	m_border = SDL_CreateTextureFromSurface(m_renderer, IMG_Load("images/border.png"));
	gameState = PLAYING;
}

void MultiplayerGame::GenerateEnemy(b2Vec2 position,int type)
{
	switch(type)
	{
	case 2:
		EnemyManager::Instance()->AddSnake( m_enemyFactory->CreateSnake(m_world, position, m_renderer, m_subject));
		break;
	case 3:
		EnemyManager::Instance()->AddMummy( m_enemyFactory->CreateMummy(m_world, position, m_renderer, m_subject));
		break;
	case 4:
		EnemyManager::Instance()->AddBat( m_enemyFactory->CreateBat(m_world, position, m_renderer, m_subject));
		break;

	break;
	}
}


void MultiplayerGame::Update(double deltaTime) 
{	
	if(gameState == WAITING)
	{
		listenForIP();
	}
	
	else if(gameState == PLAYING){
		if(m_shakeTimer > 0)
		{
			m_shakeTimer -= deltaTime;
		}
	/*	float32 timeStep = 1/60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
	
		m_world->Step(timeStep, velocityIterations, positionIterations);	*/

		CheckPickupDead();
		EnemyManager::Instance()->Update(m_world,deltaTime);

		for (int i = 0; i < m_blocks.size(); ++i) 
		{
			m_blocks.at(i)->Update(deltaTime);
		}
		for (int i = 0; i < m_blocks.size(); ++i) 
		{
			if(m_blocks.at(i)->ShouldRemove())
			{
				m_blocks.erase(m_blocks.begin()+i);
			}
		}
		if (KeyboardManager::getKeys()->Key_B)
		{
			m_mapManager->BuyBomb();
		}
		PacketStream* pStream = m_player->Serialize();
		if(m_doorSwitch->CheckCollision())
		{
			m_player->AppendDoorOpen();
		}
		if(m_player->Update(deltaTime))
		{
			m_shakeTimer = 0.5;
		}
		if(m_networkPlayer->UpdateNetworkPlayers(deltaTime))
		{
			m_shakeTimer = 0.5;
		}
		m_endDoor->CheckCollision();
		if(m_endDoor->GetMultiEnd())
		{
			m_player->AppendNextLevel();
			m_restart = true;
		}
		if(m_mapManager->GetLives() <= 0)
		{
			m_player->AppendGameOver();
		}
		for(int i =0; i < playerInfo.size(); ++i)
		{
			mNet->sendData(const_cast<char*>(playerInfo.at(i).second.c_str()),playerInfo.at(i).first,pStream->toCharArray());
		}
		Listen();
	}
}
bool MultiplayerGame::CheckEnd()
{
	return m_endDoor->GetAnimEnded();
}

void MultiplayerGame::AnimEnd()
{
	if (m_endDoor->CheckCollision())
	{
		m_endDoor->PlayClose();
	}
}
vector<string> MultiplayerGame::splitString(std::string s){
	string buf; // Have a buffer string
	stringstream ss(s); // Insert the string into a stream
	vector<string> tokens; // Create vector to hold our words
	while (ss >> buf)
		tokens.push_back(buf);
	return tokens;
}
void MultiplayerGame::listenForIP(){
	std::string names = m_serverHelper->GetNamesFromServer(m_myName,m_friendsName);

	vector<std::string> ips = splitString(names);
	PacketStream* pStream = new PacketStream();
	// 0 = port
	// 1 = ip
	// 2 = port 
	// 3 = ip
	if(ips.size() > 2)
	{	
		playerInfo.push_back(std::pair<int,std::string>(pStream->readInt(ips.at(0)),pStream->readString(ips.at(1))));		
		double d = stod(ips.at(2));
		if(d > mySeed)
		{
			mySeed = d;
		}
		mySeed *= RAND_MAX;
		srand(mySeed * RAND_MAX);
		Setup();
	}
	
	
}
int MultiplayerGame::getSeed()
{
	return static_cast<int>(mySeed);
}

void MultiplayerGame::setSeed(int seed)
{
	mySeed = seed;
}
void MultiplayerGame::Listen(){
	char message[600]="";
	mNet->receiveData(message);

	if(message[0] != '\0'){
		PacketStream* pStream = new PacketStream();
		pStream->setMessage(std::string(message));
		vector<string> messages = splitString(message);
		if(pStream->readString(messages.at(0)) == "update")
		{
			std::tuple<bool,bool,bool> restart_Lever = m_networkPlayer->Deserialize(pStream);
			
			if(std::get<0>(restart_Lever))
			{
				m_restart = true;
			}
			if(std::get<1>(restart_Lever))
			{
				m_doorSwitch->setClose(true);
				m_doorSwitch->PlayClose();
			}			
			if(std::get<2>(restart_Lever))
			{
				m_gameOver = true;
			}
		}		
	}
}

void MultiplayerGame::CheckZoom()
{
	if (KeyboardManager::getKeys()->Key_P)
	{
		TileBase::getBase()->AddZoom();
	}
	if (KeyboardManager::getKeys()->Key_O)
	{
		TileBase::getBase()->MinusZoom();
	}
}
void MultiplayerGame::Render() 
{
	if(gameState != PLAYING)
	{
		return;
	}
	
	float theZoomScale = TileBase::getBase()->m_zoomScale;

	int leftEdge = -CONSTANTS::MAP_LEFT_BORDER;
	int rightEdge = CONSTANTS::MAP_RIGHT_BORDER - 

		(CONSTANTS::SCREEN_WIDTH / theZoomScale);
	int topEdge = CONSTANTS::MAP_LEFT_BORDER;
	int bottomEdge = -CONSTANTS::MAP_BOTTOM_BORDER + 

		(CONSTANTS::SCREEN_HEIGHT / theZoomScale);
	SDL_RenderSetScale(m_renderer,theZoomScale,theZoomScale);
	b2Vec2 offset = b2Vec2((m_player->GetPosition().x * METRESTOPIXELS) - CONSTANTS::SCREEN_WIDTH / (2 * theZoomScale), 
		(m_player->GetPosition().y * METRESTOPIXELS) + CONSTANTS::SCREEN_HEIGHT / (2 * theZoomScale));

	if (offset.x < leftEdge)
	{
		offset.x = leftEdge;
	}
	else if (offset.x > rightEdge)
	{
		offset.x = rightEdge;
	}
	if (offset.y > topEdge)
	{
		offset.y = topEdge;
	}
	else if (offset.y < bottomEdge)
	{
		offset.y = bottomEdge;
	}

	CheckZoom();
	if(m_shakeTimer > 0)
	{
		offset.x += rand()%10;
		offset.y += rand()%10;
	}
	SDL_RenderClear( m_renderer );

	m_mapManager->Render(offset);

	for (int i = 0; i < m_bgBlocks.size(); ++i)
	{
		m_bgBlocks.at(i)->Render(offset);
	}

	for (int i = 0; i < m_spikes.size(); ++i)
	{
		m_spikes.at(i)->Render(offset);
	}

	for (int i = 0; i < m_torches.size(); ++i)
	{
		m_torches.at(i)->Render(offset);
	}

	m_startDoor->Render(offset);
	
	m_endDoor->Render(offset);
	m_doorSwitch->Render(offset);

	for (int i = 0; i < m_arrowTraps.size(); ++i)
	{
		m_arrowTraps.at(i)->Render(offset);
	}

	for (int i = 0; i < m_ladders.size(); ++i)
	{
		m_ladders.at(i)->Render(offset);
	}

	for (int i = 0; i < m_pickUps.size(); ++i)
	{
		m_pickUps.at(i)->Render(offset);
	}

	m_player->Render(offset);
	m_networkPlayer->Render(offset);
	EnemyManager::Instance()->Render(offset);

	for (int i = 0; i < m_blocks.size(); ++i) 
	{
		m_blocks.at(i)->Render(offset);
	}

	for (int i = 0; i < m_bgBlocksOnes.size(); ++i)
	{
		m_bgBlocksOnes.at(i)->Render(offset);
	}

	m_player->RenderExplosion(offset);

	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = CONSTANTS::SCREEN_WIDTH;
	stretchRect.h = CONSTANTS::SCREEN_HEIGHT;

	if (KeyboardManager::getKeys()->Key_R) 
	{
		++m_rewindTime;
		if (m_rewindTime == 11)
		{
			m_rewindTime = 0;
		}
		if (m_rewindTime < 3)
		{
			SDL_RenderCopyEx( m_renderer, m_rewindTexture1, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
		}
		else if (m_rewindTime < 6)
		{
			SDL_RenderCopyEx( m_renderer, m_rewindTexture2, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
		}
		else if (m_rewindTime < 9)
		{
			SDL_RenderCopyEx( m_renderer, m_rewindTexture3, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
		}
		else if (m_rewindTime < 12)
		{
			SDL_RenderCopyEx( m_renderer, m_rewindTexture4, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
		}
	}
	else
	{
		SDL_RenderCopyEx( m_renderer, m_border, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}

	m_hud->Render();

	SDL_RenderPresent( m_renderer );
}
