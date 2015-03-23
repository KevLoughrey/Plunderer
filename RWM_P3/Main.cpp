#include <iostream>
#include <SDL.h>
#include <Box2D\Box2D.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <ctime>
#include <SDL_mixer.h>
#include <Game.h>
#include <CollisionListener.h>
#include <KeyboardManager.h>
#include <SDL_thread.h>
#include <MainMenu.h>
#include <EndingMenu.h>
#include <stack>
#include <functional>
#include <vector>
#include <MultiplayerGame.h>
#include <OptionsMenu.h>
#include <MultiMenu.h>
#include <TileBase.h>
#include <Subject.h>
#include <Achievements.h>
#include <MapManager.h>
#include <ServerHelper.h>
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <time.h>


//Screen dimension constants 
const int SCREEN_WIDTH = CONSTANTS::SCREEN_WIDTH; 
const int SCREEN_HEIGHT = CONSTANTS::SCREEN_HEIGHT;

//The window we'll be rendering to 
SDL_Window *window = NULL; 
SDL_Renderer *renderer = NULL; 
SDL_Event eHandler;
b2World *world;

SDL_sem* gDataLock = NULL;

typedef std::function<void()> VoidFunc;
typedef std::vector<VoidFunc> FuncVector;
FuncVector functions;
Game *game;
MultiplayerGame *multiGame;
MainMenu *menu;
OptionsMenu *optionsMenu;
MultiMenu *multiMenu;
EndingMenu *endingMenu;
MapManager *mapManager;
ServerHelper *serverHelper;
void gameLoop();

Subject *m_subject;
Achievements *m_achievements;

bool gameOver = false;

double m_updateTicks;
double m_physicsTicks;
double m_inputTicks;

SDL_Thread *renderThread = NULL;
int i = 0;
const int FRAME_RATE=60;
enum GameState { MENU, PLAYING , LOADING , PLAYINGMULTI, OPTIONS, MULTIMENU, ENDINGMENU};
GameState gameState = MENU;

int RenderMenu(void* data);

SDL_Texture* m_loadingTexture;

int RenderEndMenu(void* data) 
{
	while (gameState == ENDINGMENU) 
	{
		SDL_Delay( 15 );
		if (!endingMenu->CheckQuitButton())
		{
			endingMenu->Render();
		}
		else
		{
			gameState = MENU;
			menu->SetButtons();
			KeyboardManager::getKeys()->Key_Space = false;
			renderThread = SDL_CreateThread(RenderMenu,"Renderer",NULL);
		}
	}
	return 0;
}

int RenderMultiGame(void* data) 
{
	while (gameState == PLAYINGMULTI) 
	{
		SDL_Delay( 15 );
		SDL_SemWait(gDataLock);
		multiGame->Render();
		if(multiGame->CheckRestart())
		{
			
			std::pair<int, std::string> friendInfo = multiGame->GetFriendInfo();
			std::pair<int, std::string> myInfo = multiGame->GetMyInfo();
			int seed = multiGame->getSeed();
			
			delete multiGame;
			if (mapManager->GetBombs() <= 0)
			{
				mapManager->AddBomb();
			}
			++seed;
			srand(seed);
			mapManager->AddLevel();
			mapManager->AddToVectors();
			mapManager->LoadWorldBorder();
			delete world;
			b2Vec2 gravity =  b2Vec2(0.0f, (-9.81f*GRAVITYSCALE));
			world = new b2World(gravity);
			world->SetContactListener(CollisionListener::getListener());
			CollisionListener::getListener()->SetWorld(world);
			multiGame = new MultiplayerGame(renderer,world,multiMenu->getMyName(),multiMenu->getFriendsName(),m_subject,mapManager,myInfo.second,friendInfo.second,++friendInfo.first);
			multiGame->setSeed(seed);
		}
		std::pair<bool,bool> endGames = multiGame->EndGame();

		if(endGames.first)
		{
			serverHelper->PostCoopHighScore(mapManager->GetCompletedLevels(), multiMenu->getMyName(), multiMenu->getFriendsName());
			gameState = ENDINGMENU;	
			endingMenu = new EndingMenu(renderer,world,mapManager->GetCompletedLevels(),2);
			endingMenu->SetButtons();
			delete multiGame;
			mapManager->ResetHud();
			renderThread = SDL_CreateThread(RenderEndMenu,"Renderer",NULL);
		}
		else if(endGames.second)
		{
			gameState = ENDINGMENU;	
			endingMenu = new EndingMenu(renderer,world,mapManager->GetCompletedLevels(),2);
			endingMenu->SetButtons();
			delete multiGame;
			mapManager->ResetHud();
			renderThread = SDL_CreateThread(RenderEndMenu,"Renderer",NULL);
		}
		SDL_SemPost(gDataLock);
	}
	return 0;
}

void DrawLoading()
{
	
	int random = rand() %TileBase::getBase()->m_interTileTextures.size();
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = CONSTANTS::SCREEN_WIDTH;
	stretchRect.h = CONSTANTS::SCREEN_HEIGHT;
	SDL_RenderClear(renderer);
	SDL_RenderSetScale(renderer,1,1);
	SDL_RenderCopy( renderer, TileBase::getBase()->m_interTileTextures.at(random), NULL, &stretchRect);
	SDL_RenderPresent( renderer );
}

void doFunc()
{
	SDL_SemWait( gDataLock );
	m_subject->SetActive(false);
	gameState = LOADING;
	SoundManager::getSoundManager()->StopGameAudio();
	SoundManager::getSoundManager()->PlayGameplayTheme();
	DrawLoading();
	SDL_Delay(3000);
	if (game->CheckRestart())
	{
		mapManager->ResetHud();
		mapManager->ResetLevel();
	}
	delete game;
	if (mapManager->GetBombs() <= 0)
	{
		mapManager->AddBomb();
	}
	mapManager->AddLevel();
	mapManager->AddToVectors();
	mapManager->LoadWorldBorder();
	delete world;
	b2Vec2 gravity =  b2Vec2(0.0f, (-9.81f*GRAVITYSCALE));
	world = new b2World(gravity);
	world->SetContactListener(CollisionListener::getListener());
	CollisionListener::getListener()->SetWorld(world);
	game = new Game(renderer,world, mapManager, m_subject);
	gameState = PLAYING;
	gameOver = false;
	//_CrtDumpMemoryLeaks();
	m_subject->SetActive(true);
	SDL_SemPost(gDataLock);
}



int RenderGame(void* data) 
{
	while (gameState == PLAYING) 
	{
		SDL_Delay( 15 );
		if (game->CheckBackToMain())
		{
			SDL_SemWait( gDataLock );
			gameState = MENU;	
			delete game;
			menu->SetButtons();
			renderThread = SDL_CreateThread(RenderMenu, "Renderer", NULL);
			menu->doOnce = false;
			SoundManager::getSoundManager()->StopGameAudio();
			SDL_SemPost(gDataLock);
		}
		else if (!game->CheckRestart() && !game->CheckEnd() && game->CheckPlayerAlive())
		{
				SDL_SemWait(gDataLock);
				SDL_RenderClear( renderer );
				game->Render();
				m_achievements->Render();
				SDL_RenderPresent(renderer);
				SDL_SemPost(gDataLock);
		}
		else
		{
			if (!game->CheckPlayerAlive())
			{
				SDL_SemWait( gDataLock );
				gameState = ENDINGMENU;	
				endingMenu = new EndingMenu(renderer,world,mapManager->GetCompletedLevels(),1);
				endingMenu->SetButtons();
				delete game;
				mapManager->ResetHud();
				renderThread = SDL_CreateThread(RenderEndMenu,"Renderer",NULL);
				
				SDL_SemPost(gDataLock);
			}
			else 
			{
				doFunc();
			}
		}
	}
	return 0;
}



int RenderOptions(void* data) 
{
	while (gameState == OPTIONS) 
	{
		SDL_Delay( 15 );
		if (!optionsMenu->checkGuyPressed() && !optionsMenu->checkGirlPressed())
		{
			optionsMenu->Render();
		}
		else
		{
			gameState = MENU;
			menu->SetButtons();
			KeyboardManager::getKeys()->Key_Space = false;
			renderThread = SDL_CreateThread(RenderMenu,"Renderer",NULL);
		}
	}
	return 0;
}
int RenderMultiMenu(void* data)
{
	while (gameState == MULTIMENU) 
	{
		SDL_Delay( 15 );
		multiMenu->Render();
		if(multiMenu->checkStartButton()
			&& multiMenu->getMyName().length()>1 
			&& multiMenu->getFriendsName().length()>1)
		{
			DrawLoading();
			SDL_Delay(3000);
			delete world;
			b2Vec2 gravity =  b2Vec2(0.0f, (-9.81f * GRAVITYSCALE));
			world = new b2World(gravity);
			world->SetContactListener(CollisionListener::getListener());
			mapManager = new MapManager(0,renderer);
			CollisionListener::getListener()->SetWorld(world);
			multiGame = new MultiplayerGame(renderer,world,multiMenu->getMyName(),multiMenu->getFriendsName(), m_subject, mapManager);//menu->getMultiGame();
			gameState = PLAYINGMULTI;
			renderThread = SDL_CreateThread(RenderMultiGame,"Renderer",NULL);
		}
		else if (multiMenu->checkQuitBtn())
		{
			gameState = MENU;
			menu->SetButtons();
			KeyboardManager::getKeys()->Key_Space = false;
			renderThread = SDL_CreateThread(RenderMenu,"Renderer",NULL);
		}

	}
	return 0;
}

int RenderMenu(void* data)
{
	srand (time(NULL));
	while (gameState == MENU) 
	{
		SDL_Delay( 15 );
		menu->Render();
		if (menu->CheckPlayButton())
		{
			DrawLoading();
			SDL_Delay(3000);
			delete world;
			b2Vec2 gravity =  b2Vec2(0.0f, (-9.81f*GRAVITYSCALE));
			world = new b2World(gravity);
			world->SetContactListener(CollisionListener::getListener());
			mapManager = new MapManager(0,renderer);
			CollisionListener::getListener()->SetWorld(world);
			game = new Game(renderer,world,mapManager, m_subject);
			gameState = PLAYING;
			renderThread = SDL_CreateThread(RenderGame,"Renderer",NULL);
			SoundManager::getSoundManager()->StopMenuAudio();
			SoundManager::getSoundManager()->PlayGameplayTheme();
		}
		if (menu->CheckMultiButton())
		{
			multiMenu = new MultiMenu(renderer,world);
			gameState = MULTIMENU;
			KeyboardManager::Key_Space = false;
			renderThread = SDL_CreateThread(RenderMultiMenu,"Renderer",NULL);
		}
		if (menu->CheckOptionButton())
		{
			optionsMenu = new OptionsMenu(renderer,world);
			gameState = OPTIONS;
			KeyboardManager::Key_Space = false;
			renderThread = SDL_CreateThread(RenderOptions,"Renderer",NULL);
		}
	}
	return 0;
}

void StepWorld()
{
	float32 timeStep = PHYSICS_TICKS;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(timeStep, velocityIterations, positionIterations);
}

int main(int argc, char **argv) 
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	bool QUIT = true;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Initialize SDL
	if( SDL_Init(SDL_INIT_JOYSTICK ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}

	//Initialize SDL
	if( SDL_Init( SDL_INIT_AUDIO ) < 0 )
	{
		std::cout <<( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	//Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		std::cout <<( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	}

	//window = SDL_CreateWindow( "Plunderer!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP  ); 
	window = SDL_CreateWindow( "Plunderer!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN  ); 
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ); 
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 

	//Initialize PNG loading 
	if(!( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ))
	{ 		
		std::cout <<( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	} 
	TTF_Init();
	SDL_ShowCursor(SDL_DISABLE);

	m_loadingTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/loading.png"));
	SDL_RenderClear( renderer );
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = CONSTANTS::SCREEN_WIDTH;
	stretchRect.h = CONSTANTS::SCREEN_HEIGHT;
	SDL_RenderCopyEx( renderer, m_loadingTexture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	SDL_RenderPresent( renderer );

	gDataLock = SDL_CreateSemaphore( 1 );
	
	TileBase::getTileBase(renderer);

	

	menu = new MainMenu(renderer,world);

	//SoundManager::getSoundManager()->PlayMenuTheme();
	m_subject = new Subject();
	m_achievements = new Achievements(m_subject, renderer);

	renderThread = SDL_CreateThread(RenderMenu,"Renderer",NULL);

	m_physicsTicks = SDL_GetTicks();
	m_updateTicks = m_physicsTicks;
	m_inputTicks = m_physicsTicks;

	serverHelper = new ServerHelper();
	while (QUIT)
	{
		Uint32 currentTicks = SDL_GetTicks();
		double updateDelta = currentTicks - m_updateTicks;
		double physicsDelta = currentTicks - m_physicsTicks;

		if (physicsDelta / 1000 > PHYSICS_TICKS)
		{
			m_physicsTicks += physicsDelta;
			if (gameState == PLAYING || gameState == PLAYINGMULTI)
			{
				SDL_SemWait( gDataLock );
				StepWorld();
				SDL_SemPost( gDataLock);
			}
		}

		if (updateDelta * 0.001f > UPDATE_TICKS)
		{
			m_updateTicks += updateDelta;
		
			KeyboardManager::getKeys()->Update(eHandler);
			if (KeyboardManager::getKeys()->QUIT)
			{
				SDL_Quit();
			}
			if (gameState == PLAYING)
			{
				SDL_SemWait( gDataLock );
				game->Update(updateDelta/1000.0f);
				SDL_SemPost( gDataLock);
			}
			if (gameState == PLAYINGMULTI)
			{
				SDL_SemWait( gDataLock );
				multiGame->Update(updateDelta/1000.0f);
				
				SDL_SemPost( gDataLock);
			}
			if (gameState == MULTIMENU)
			{
				SDL_SemWait( gDataLock );
				multiMenu->update();
				SDL_SemPost( gDataLock);
			}
		}
	
	}
	if (multiGame != NULL)
	{
		delete multiGame;
	}
	SDL_Quit();

	return 0;
}