// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : PLAYER STATE WHEN PLAYER SPRINTS

#pragma once
#include <PlayerState.h>

class PlayerSprinting 
:	public PlayerState
{

public:
	PlayerSprinting();
	~PlayerSprinting();
	virtual PlayerState* HandleInput(Player &player);
	virtual void Update(Player &player);
	
private:
	/// A conter used to delay frame advance.
	/// Used to adjust animation in game so that
	/// it would be in a pace with game.
	int m_counter;

	/// A frame index to show.
	int m_curFrame;

	/// Used to simulate press and release.
	bool m_buttonSPrevPressed;
};

