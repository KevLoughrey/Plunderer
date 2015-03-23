// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : PLAYER STATE WHEN PLAYER IS KILLED

#pragma once
#include "PlayerState.h"
class PlayerDying 
:	public PlayerState
{

public:
	PlayerDying();
	virtual ~PlayerDying();
	virtual PlayerState* HandleInput(Player &player);
	virtual void Update(Player &player);

private:	
	/// A conter used to delay frame advance.
	/// Used to adjust animation in game so that
	/// it would be in a pace with game.
	int m_counter;

	/// A frame index to show.
	int m_curFrame;
};

