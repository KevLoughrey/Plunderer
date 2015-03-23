// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : Used to procedurally generate the game levels
#pragma once

#include <iostream>
#include <vector>
#include <SDL_image.h>
#include <Box2D\Box2D.h>
#include <Tmx.h>
#include <TileBase.h>
#include <Room.h>
#include <string>
#include <SoundManager.h>

class MapManager
{
public:
	///Creates a map manager
	/// \param[level] starting floor of level generation
	/// \param[renderer] pointer to renderer for rendering
	MapManager(int level, 
			   SDL_Renderer *renderer);

	~MapManager();
	/// Load block positions from .tmx files
	/// \param[paths] vector of strings to the .tmx files
	/// \param[rooms] pointer to room list that  stores block positions from each tmx file
	void LoadObjects(std::vector<std::string> paths, 
					 std::vector<Room*> *rooms);
	
	void Render(b2Vec2 offset);
	///call to create level
	/// \return a vector of block positions
	std::vector<b2Vec2> BuildLevel();
	
	///Create a floor of rooms
	/// \param[sp] starting room
	/// \param[counter] the floor to create
	/// \param[rooms] vector of block positions
	void BuildWorld(int sp, int counter, std::vector<b2Vec2> *rooms);
	///Get types of blocks
	/// \return a vector of ints containing block types
	std::vector<int> getTypes();
	///Get background block positions
	/// \return a vector of block positions
	std::vector<b2Vec2> getBgPos();
	///Get background block types
	/// \return a vector of block types
	std::vector<int> getBgTypes();
	///Get background type one blocks
	/// \return a vector of type one blocks
	std::vector<int> getBgTypesOnes();
	///Get background position one blocks
	/// \return a vector of positions for one blocks
	std::vector<b2Vec2> getBgPosOnes();
	///Get background block positions
	/// \return a vector of background block positions
	std::vector<b2Vec2> getBgPositions();
	///Get heights of blocks
	/// \return block heights
	std::vector<int> getBlockHeights();
	///Get starting door position
	/// \return starting door position
	b2Vec2 GetStartPoint();
	///Get ending door position
	/// \return ending door position
	b2Vec2 GetEndPoint();
	///Get position of hourglass pickup
	/// \return position
	b2Vec2 GetHourglassPos();
	///Get position of door switch
	/// \return position
	b2Vec2 GetSwitchPos();
	///Get position of health pickup
	/// \return position

	b2Vec2 GetHealthPickupPos();
	///Add offsets back into the vector
	void AddToVectors();
	///Load world blocks
	void LoadWorldBorder();
	///Decrease number of bombs player has
	void DecreaseNumBombs();
	///Increase amount of gold player has
	void IncreaseGold();
	///Go to next level
	void AddLevel();
	///Reduce health
	void DecreseHealth(int decrease);
	///Reduce diamonds by 5, add a bomb
	void BuyBomb();
	///Add bomb to players inventory
	void AddBomb();
	///Reset hud values to default
	void ResetHud();
	///Resets the level
	void ResetLevel();
	///Increase life amount
	void AddLife();
	///Get current level counter
	int GetLevel();
	///Get amounts of completed levels
	int GetCompletedLevels();
	///Get curr lives
	int GetLives();
	///Get curr bombs
	int GetBombs();
	///Get curr diamonds
	int GetJewels();
	///Check if player is dead
	bool CheckPlayerDead();
	///Set the player to dead
	void SetDead();

protected:
	bool m_alive;
	int m_completedLevels;
	SDL_Renderer *m_renderer;
	Tmx::Map *m_map;
	int m_level;
	SDL_Rect m_pos;
	const Tmx::Layer *m_currLayer;
	SDL_Texture *m_texture;
	std::vector<Room*> m_type0Rooms;
	std::vector<Room*> m_type1Rooms;
	std::vector<Room*> m_type2Rooms;
	std::vector<Room*> m_type3Rooms;
	std::vector<std::string> m_type0Paths;
	std::vector<std::string> m_type1Paths;
	std::vector<std::string> m_type2Paths;
	std::vector<std::string> m_type3Paths;
	std::vector<b2Vec2> m_row0Offsets;
	std::vector<b2Vec2> m_row1Offsets;
	std::vector<b2Vec2> m_row2Offsets;
	std::vector<b2Vec2> m_row3Offsets;
	std::vector<b2Vec2> m_levelBlockPositions;
	std::vector<b2Vec2> m_backPositionsOnes;
	std::vector<b2Vec2> m_backPositions;
	std::vector<int> m_backTypes;
	std::vector<int> m_blockTypes;
	std::vector<int> m_blockTypesOnes;
	std::vector<b2Vec2> m_bgPositions;
	std::vector<int> m_blockHeights;
	std::vector<b2Vec2> vec;
	std::vector<b2Vec2> vecBack;
	std::vector<int> heights;
	std::vector<int> vecType;
	std::vector<int> vecBackType;

	b2Vec2 m_hourGlassPos;
	b2Vec2 m_startPoint;
	b2Vec2 m_endPoint;
	b2Vec2 m_switchPos;
	b2Vec2 m_healthPos;

	int m_goldAmount;
	int m_numBombs;
	int m_health;

	bool healthPosAssinged;
};