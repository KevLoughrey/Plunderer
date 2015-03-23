// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : USED TO CHECK COLLISIONS OF BAT RAYCAST WITH FIXTURES.  

#pragma once

#include <Box2d/Dynamics/b2WorldCallbacks.h>
#include <vector>

class BatQuery 
:	public b2RayCastCallback
{

public:
	bool m_detectedPlayer;

	BatQuery():
		m_detectedPlayer(false)
	{}
     
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override
	{
		// If ray-cast hit solid object bat cant see 
		// through, stop ray-cast and set "m_detectedPlayer" to false.
		if(	fixture->GetUserData() == "block" ||
			fixture->GetUserData() == "solidblock"||
			fixture->GetUserData() == "arrowTrap")
		{
			m_detectedPlayer = false;

		}

		// If ray-cast hit player stop ray-cast and 
		// set "m_detectedPlayer" to true.
		else if(fixture->GetUserData() == "player")
		{
			m_detectedPlayer = true;
		}

		return fraction;
	}
};

