// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Abstract command class for command pattern.

#pragma once

#include <iostream>
#include <Box2D\Box2D.h>
#include <Constants.h>

class Player;

class Command
{
public:
	/// Destructor
	/// Destorys the object
	virtual ~Command() {};

	/// Execute the command
	/// Affect the player depending on the command type
	/// \p[in] reference to the player
	/// \modifier[in] should the action be modified?
	virtual void execute(Player *p, 
						 bool modifier) = 0;

protected:
	/// Constructor
	/// Creates the object
	Command() {};
};

#include "Player.h"