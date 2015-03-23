// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Command for moving the player right.

#pragma once

#include <Command.h>

class RightCommand : public Command
{
public:
	/// Constructor
	/// Creates the command
	RightCommand();

	/// Destructor
	/// Destorys the object
	~RightCommand();

	/// Move right
	/// make the player move right
	/// \p[in] reference to the player
	/// \modifier[in] should the action be modified?
	void moveRight(Player *p, 
				   bool modifier);

	/// Execute the command
	/// Affect the player bu calling moveRight()
	/// \p[in] reference to the player
	/// \modifier[in] should the action be modified?
	virtual void execute(Player *p, 
						 bool modifier);
};