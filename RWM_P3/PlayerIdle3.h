// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : PLAYER STATE WHEN PLAYER DOING NOTHING

#pragma once
#include "playerstate.h"
class PlayerIdle3 
:	public PlayerState
{

public:
	PlayerIdle3();
	~PlayerIdle3();
	virtual PlayerState* HandleInput(Player &player);
	virtual void Update(Player &player);

private:
	/// A conter used to delay frame advance.
	/// Used to adjust animation in game so that
	/// it would be in a pace with game.
	int m_counter;

	/// A frame index to show.
	int m_curFrame;

	/// Used to switch another Idle State.
	bool m_switchIdle;
};

