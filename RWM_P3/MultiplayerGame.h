// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : The class that controls a multiplayer game
#pragma once
#include <fstream>
#include <SDL_image.h>
#include <ctime>
#include <Box2D\Box2D.h>
#include <Player.h>
#include <DirtBlock.h>
#include <Constants.h>
#include <MapManager.h>
#include <EnemyManager.h>
#include <BgBlock.h>
#include <Ladder.h>
#include <Door.h>
#include <Torch.h>
#include <Pickup.h>
#include <Spikes.h>
#include <ArrowTrap.h>
#include <HUD.h>
#include <Net.h>
#include <PacketStream.h>
#include <Factory.h>
#include <EnemyFactory.h>
#include <DoorSwitch.h>
#include <ServerHelper.h>
class MultiplayerGame
{
public:
	///Create multiplayer game
	/// \param[renderer] renderer for drawing world
	/// \param[world] box2d world
	/// \param[myName] string containing my name from previous menu
	/// \param[friendName] string containing friends name from previous menu
	/// \param[subject] observer used to update objects
	/// \param[mapManager] pointer to map manager
	MultiplayerGame(SDL_Renderer *renderer, 
		 b2World *bworld,
		 std::string myName, std::string friendName, Subject*, MapManager *mapManager);

	///Create multiplayer game
	/// \param[renderer] renderer for drawing world
	/// \param[world] box2d world
	/// \param[myName] string containing my name from previous menu
	/// \param[friendName] string containing friends name from previous menu
	/// \param[subject] observer used to update objects
	/// \param[mapManager] pointer to map manager
	/// \param[myIP] my ip address
	/// \param[friendIP] friends ip address
	/// \param[port] port used to setup connection
	MultiplayerGame(SDL_Renderer *renderer, b2World *bWorld, std::string myName, std::string friendName, Subject*, MapManager *mapManager,
					std::string myIP, std::string friendIP, int port);
	~MultiplayerGame();
	/// update all objects in the multiplayer game
	/// \param[deltatime] time since last frame
	void Update(double deltaTime);
	/// Draw the game world
	void Render();
	/// Setup the game world
	void Setup();
	/// Listen for game messages
	void Listen();
	/// Check if game has ended
	/// \return wether the player has died
	bool CheckEnd();
	/// Ends animation
	void AnimEnd();
	/// Checks if a pickup is dead
	void CheckPickupDead();
	/// Check if were zooming in
	void CheckZoom();
	///Create an enemy
	/// \param[position] position of enemy
	/// \param[type] type of enemy
	void GenerateEnemy(b2Vec2 position,int type);
	/// Check if going to next level
	/// \return if the next level is starting
	bool CheckRestart();
	/// Sets up game to allow next level to be loaded
	void GoToNextLevel();
	///Check if game is over
	/// \return first bool is if player died, second if received message saying game is over
	std::pair<bool,bool> EndGame();
	///Get friends ip and port
	/// \return pair containing port and ip
	std::pair<int,string> GetFriendInfo();
	///Get my ip and port
	/// \return pair containing port and ip
	std::pair<int,string> GetMyInfo();
	///Get seed used for level generation
	/// \return seed
	int getSeed();
	///Set seed used for level generation
	
	void setSeed(int seed);
protected:
	
	SDL_Renderer *m_renderer;
	b2World *m_world;
	Player *m_player;
	std::vector<DirtBlock*> m_blocks;
	std::vector<BgBlock*> m_bgBlocks;
	std::vector<BgBlock*> m_bgBlocksOnes;
	std::vector<Pickup*> m_pickUps;
	std::vector<Ladder*> m_ladders;
	std::vector<Torch*> m_torches;
	std::vector<Spikes*> m_spikes;
	std::vector<ArrowTrap*> m_arrowTraps;
	MapManager *m_mapManager;
	double m_shakeTimer;
	SDL_Texture* m_rewindTexture1;
	SDL_Texture* m_rewindTexture2;
	SDL_Texture* m_rewindTexture3;
	SDL_Texture* m_rewindTexture4;
	int m_rewindTime;
	Door *m_startDoor;
	Door *m_endDoor;
	HUD *m_hud;
	bool m_endLevel;
	SDL_Texture* m_border;

	std::string m_myName;
	std::string m_friendsName;
	std::string ip;

	std::string ipAddress;
	Net* mNet;
	int PORT;
	double mySeed;
	enum GameState { WAITING,CONNECTING,PLAYING};
	GameState gameState;
	void listenForIP();
	vector<string> splitString(std::string s);
	DoorSwitch *m_doorSwitch;
	EnemyFactory *m_enemyFactory;
	Player *m_networkPlayer;
	std::vector<std::pair<int,std::string>> playerInfo;
	Subject* m_subject;
	ServerHelper *m_serverHelper;
	bool m_restart;
	bool m_gameOver;
};