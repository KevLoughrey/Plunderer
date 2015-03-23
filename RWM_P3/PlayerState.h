// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : A BASE CLASS FOR ALL PLAYER STATES.  

#pragma once
#include <KeyboardManager.h>
#include <stdlib.h>   
#include <time.h>       

class Player;

/// Base Class for player state handling.
/// This class manages when to trigger an action
/// as well as frame update.  Within it has a way to
/// transit to another state.
/// List of child Classes
/// -# PlayerClimb - When player on a ladder
/// -# PlayerDying - When player is killed
/// -# PlayerGrab - When player collects item
/// -# PlayerIdle1 - When player doing nothing
/// -# PlayerIdle2 - When player doing nothing
/// -# PlayerIdle3 - When player doing nothing
/// -# PlayerJump - When player jumps from
/// idle or walk state
/// -# PlayerSprinting - When player sprints
/// -# PlayerSprintJump - When player jumps
/// from sprinting.
/// -# PlayerThrowBomb - When player drops 
/// a bomb
/// -# PlayerWalk - When player moves
/// -# PlayerWhipState - When player uses
/// his whip  
class PlayerState
{
public:

	/// Destructor.
	virtual ~PlayerState(){}

	/// Handles Input.
	/// This method returns player state based on a key press or 
	/// a certain event, like landing on ground.
	/// \param[in] a reference of a player.
	/// \return NULL if state shall remain same or a new PlayerState child
	/// object.
	virtual PlayerState* HandleInput(Player &player){return NULL;}

	/// Updates State.
	/// This method is often used to update frame counter and to trigger
	/// actions like a bomb throw.
	/// \param[in] a reference of a player.
	virtual void Update(Player &player){}
};

#include <Player.h>