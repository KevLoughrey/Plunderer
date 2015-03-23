// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : PLAYER STATE WHEN PLAYER DROPS A BOMB

#pragma once
#include <PlayerState.h>

class PlayerThrowBomb 
:	public PlayerState
{

public:
	PlayerThrowBomb();
	~PlayerThrowBomb();
	virtual PlayerState* HandleInput(Player &player);
	virtual void Update(Player &player);
	
private:
	/// A conter used to delay frame advance.
	/// Used to adjust animation in game so that
	/// it would be in a pace with game.
	int m_counter;

	/// A frame index to show.
	int m_curFrame;

	/// Used to plant bomb only once.
	bool m_bombPlanted;
};

