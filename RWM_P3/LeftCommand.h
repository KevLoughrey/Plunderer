// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Command for the player to move left.

#pragma once

#include <Command.h>

class LeftCommand : public Command
{
public:
	LeftCommand();
	~LeftCommand();
	void moveRight(Player *p, 
				   bool modifier);
	virtual void execute(Player *p, 
						 bool modifier);
};