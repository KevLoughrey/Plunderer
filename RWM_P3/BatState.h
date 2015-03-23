// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : A BASE CLASS FOR ALL BAT STATES.  

#pragma once
#include <stdlib.h>   
#include <time.h>       

class Bat;

/// Base Class for bat state handling.
/// This class manages when to trigger an action
/// as well as frame update.  Within it has a way to
/// transit to another state.
/// List of child Classes
/// -# BatFlyToCeiling - When bat flies to the ceiling
/// -# BatFlyTowardPlayer - When bat flies toward player
/// -# BatSleep - When bat is sleeping
class BatState
{

public:
	
	/// Destructor.
	virtual ~BatState(){}

	/// Updates State.
	/// This method is often used to update frame counter and to trigger
	/// actions.
	/// \param[in] a reference of a bat.
	/// \return NULL if state shall remain same or a new BatState child
	/// object.
	virtual BatState* Update(Bat &bat){return NULL;}
};

#include <Bat.h>