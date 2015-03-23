// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : HANDLES ENEMY AI, UPDATE AND RENDER  

#pragma once
#include <Snake.h>
#include <Mummy.h>
#include <Bat.h>

#include <SnakeQuery.h>
#include <MummyQuery.h>
#include <BatQuery.h>


/// This class handles enemy update, AI and drawing.
/// This singleton class initializes all in-game enemies,
/// which are:
/// -# Snakes
/// -# Mummies
/// -# Bats
/// Snakes and Mummies use string operated FSM, while Bats 
/// have State handling same as of a player.
class EnemyManager
{
private:	
	/// These vectors store enemies.
	std::vector<Mummy*> m_mummies;
	std::vector<Snake*> m_snakes;
	std::vector<Bat*> m_bats;

protected:
	static EnemyManager *s_instance;
	EnemyManager();
	
	/// Deletes enemies which are dead.
	void CheckForDead(double deltatime);

	/// AI Logic is handled in these methods per each enemy type.

	/// Snake AI Handling.
	/// Features:
	/// -# Turns if close to wall (Doesn't collide physically)
	/// -# Turns if near a hole (Will not fall on it's own)
	/// -# Responds to changes in the world (if block was re-
	/// moved, snake will respond to it)
	void SnakeUpdate(int index, b2World* world);

	/// Mummy AI Handling.
	/// Features:
	/// -# Turns if close to a tall wall (Doesn't collide physically)
	/// -# Turns if near a deep hole (Will not fall on it's own)
	/// -# Can jump up on one block up (or two, but it is a bug...)
	/// -# Can jump down one block
	/// -# Attacks player if close
	/// -# Responds to changes in the world (if block was re-
	/// moved, mummy will respond to it)
	void MummyUpdate(int index, b2World* world);

	/// Bat AI Handling.
	/// Features:
	/// -# Uses half-circle sensor to detect is player close
	/// -# Once player inside, ray-cast is used to check is player
	/// can be seen physically
	/// -# Bat simulates flapping
	/// -# Sleeps on the ceiling if no player present
	void BatUpdate(int index, b2World* world);

public:	
	static EnemyManager* Instance();
	~EnemyManager(void);

	void AddMummy(Mummy *mummy);
	void AddSnake(Snake *snake);
	void AddBat(Bat *bat);

	void Update(b2World* world, double deltatime);
	void Render( b2Vec2 offset);
	void DestroyAll();
};

