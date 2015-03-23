// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : BAT STATE WHEN BAT IS SLEEPING. 

#pragma once
#include <BatState.h>
class BatSleep 
: public BatState
{
public:
	virtual ~BatSleep();
	virtual BatState* Update(Bat &bat);
};

