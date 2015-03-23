// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : BAT STATE WHEN BAT FLIES TO CEILING.  

#pragma once
#include <BatState.h>

class BatFlyToCeiling 
:	public BatState
{

public:
	BatFlyToCeiling();
	virtual ~BatFlyToCeiling();
	virtual BatState* Update(Bat &bat);

private:
	/// Used as indicator when to flap.
	int m_flapAt;

	/// A conter used to delay frame advance.
	/// Used to adjust animation in game so that
	/// it would be in a pace with game.
	int m_counter;

	/// A frame index to show.
	int m_frame;
};

