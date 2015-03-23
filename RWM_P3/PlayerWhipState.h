// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : PLAYER STATE WHEN PLAYER USES HIS WHIP

#pragma once
#include <PlayerState.h>

class PlayerWhipState
:	public PlayerState
{

public:
	PlayerWhipState();
	~PlayerWhipState();
	virtual PlayerState* HandleInput(Player &player);

	///A counter determines how quickly frames will update.
	///When the frame reaches 16 the whip code actually takes effect.
	///Player SetWhipping telles the player about the whip so it will be animated during the scene.
	///Once the frames reach the end, SetWhipping becomes false again so the player stops drawing the whip.
	/// \param[player] passes the player into the method so they can begint the whip method.
	virtual void Update(Player &player);
	
private:
	/// A conter used to delay frame advance.
	/// Used to adjust animation in game so that
	/// it would be in a pace with game.
	int m_counter;

	/// A frame index to show.
	int m_curFrame;
};

