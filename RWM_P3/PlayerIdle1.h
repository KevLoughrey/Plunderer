// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : PLAYER STATE WHEN PLAYER DOING NOTHING

#pragma once
#include <PlayerState.h>

class PlayerIdle1 
:	public PlayerState
{

public:
	PlayerIdle1();
	~PlayerIdle1();

	///Stops the animation and plays another one depending on player input.
	///If no player input play the default animation.
	///If the idle counter (increased in the update) gets above a certain amount, alternate idle animations are activated.
	/// \param[player] passes the player into the method so it can tell what the player is doing.
	virtual PlayerState* HandleInput(Player &player);
	
	///Causes the animation frames to pass and increases/loops the counter for playing other animations.
	/// \param[player] passes the player into the method so they can begint the whip method.
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

	/// Used to simulate press and release.
	bool m_buttonSPrevPressed;
};

