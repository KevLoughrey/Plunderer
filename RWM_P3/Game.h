// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: An instance of the game, which contains all other game entities.

#pragma once

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
#include <Scarab.h>
#include <Subject.h>
#include <Factory.h>
#include <Life.h>
#include <EnemyFactory.h>

class Game
{
public:
	/// Constructor
	/// Creates a new game
	/// \renderer[in] the sdl renderer
	/// \world[in] the box2d world
	/// \mapManager[in] the map manager
	/// \subject[in] the subject for observers
	Game(SDL_Renderer *renderer, 
     	 b2World *bworld, 
		 MapManager *mapManager,
		 Subject* subject);

	/// Destructor
	/// Destroys the game
	~Game();

	/// Update
	/// Updates all entities
	/// \deltaTime[in] time since the last update
	void Update(double deltaTime);

	/// Render
	/// Render all entities
	void Render();

	/// Check end
	/// Has the game ended
	/// \return bool m_hasEnded
	bool CheckEnd();

	/// Check restart
	/// Can the game be restarted?
	/// \return bool m_canRestart
	bool CheckRestart();

	/// Check back to main menu
	/// Should we return to the main menu?
	/// \return bool representing wheter should return
	bool CheckBackToMain();

	/// Check is player alive
	/// Is the player alive
	/// \return bool is player alive
	bool CheckPlayerAlive();

	/// End of animation
	/// An animation has ended
	void AnimEnd();

	/// Check is a pickup dead
	/// Has the pickup been picked up?
	void CheckPickupDead();

	/// Check is a life pickup dead
	/// Has the life pickup been picked up?
	void CheckLifePickup();

	/// Check the zoom
	/// Zoom/scale of the game/camera
	void CheckZoom();

	/// Create the scarabs
	/// Creates a flock of scarabs
	void CreateScarabs();

	/// Generate an enemy
	/// Generate a specific enemy at a position
	/// \position[in] pixel position the enemy will be created at
	/// \type[in] type of enemy to be created
	void GenerateEnemy(b2Vec2 position, int type);

protected:
	///the SDL renderer
	SDL_Renderer *m_renderer;
	
	///the box2d world
	b2World *m_world;

	///the player
	Player *m_player;

	///vector of blocks
	std::vector<DirtBlock*> m_blocks;

	///vector of background blocks
	std::vector<BgBlock*> m_bgBlocks;

	///vector of background blocks
	std::vector<BgBlock*> m_bgBlocksOnes;

	///vector of pickups (gems)
	std::vector<Pickup*> m_pickUps;

	///vector of ladders
	std::vector<Ladder*> m_ladders;

	///vector of torches
	std::vector<Torch*> m_torches;

	///vector of spikes
	std::vector<Spikes*> m_spikes;

	///vector of arrow traps
	std::vector<ArrowTrap*> m_arrowTraps;

	///vector of life pickups
	std::vector<Life*> m_lifePickup;

	///the map manager for generating levels
	MapManager *m_mapManager;

	///timer for shaking the camera when a bomb explodes
	double m_shakeTimer;

	///time for rewinding time
	int m_rewindTime;

	///entrance to the level
	Door *m_startDoor;

	///exit from the level
	Door *m_endDoor;

	///the hud for player stats
	HUD *m_hud;

	///has the player finished the level
	bool m_endLevel;

	///has the player picked something up
	bool pickedUp;

	///should the level be restarted
	bool m_restart;

	///should return to main menu?
	bool m_mainMenu;

	///should the scarabs be spawned
	bool m_scarabsActive;

	///vector of flocking scarabs
	std::vector<Scarab*> scarabs;

	///animation counter
	int m_count;

	///number of enemies
	int m_enemyCount;

	///number of scarabs
	int m_scarabCount;

	///the subject for observer pattern
	Subject* m_subject;

	//the enemy factory
	EnemyFactory *m_enemyFactory;

};