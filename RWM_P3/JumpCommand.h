// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Command for the player to jump.

#pragma once

#include <Command.h>

class JumpCommand : public Command
{
public:
	/// Constructor
	/// Creates the command
	JumpCommand();

	/// Destructor
	/// Destorys the object
	~JumpCommand();

	/// Jump
	/// make the player jump
	/// \p[in] reference to the player
	/// \modifier[in] should the action be modified?
	void jump(Player *p, 
			  bool modifier);
	
	/// Execute the command
	/// Affect the player bu calling Jump()
	/// \p[in] reference to the player
	/// \modifier[in] should the action be modified?
	virtual void execute(Player *p, 
						 bool modifier);
};