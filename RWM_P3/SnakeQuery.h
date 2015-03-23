// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : USED TO CHECK COLLISIONS OF SNAKE AABBs WITH FIXTURES.  

#pragma once

#include <Box2d/Dynamics/b2WorldCallbacks.h>
#include <vector>

class SnakeQuery 
:	public b2QueryCallback
{

public:
	std::string m_event;
	bool m_diagonalCheck;

	SnakeQuery():
		m_event("Nothing"),
		m_diagonalCheck(false)
	{
		
	}
     
	bool ReportFixture(b2Fixture* fixture) override
	{
		// This value will be returned.
		bool l_continueSearch = true;

		// For Snake, there are 2 types of check (explained in Enemy manager)
		// Check will see what fixture was detected and will modify "m_event",
		// which will be retrieved in Enemy Manager.
		if (!m_diagonalCheck)
		{		
		    if(fixture->GetUserData() == "player")
			{
				m_event = "Player in Front";
				l_continueSearch = false;
			}

			else if(fixture->GetUserData() == "block"||
					fixture->GetUserData() == "arrowTrap")
			{
				m_event = "Block in Front";
				l_continueSearch = false;
			}
		}

		else if (m_diagonalCheck)
		{
			if(fixture->GetUserData() == "block")
			{
				m_event = "Floor Presents";
				l_continueSearch = false;
			}
		}

		return l_continueSearch;
	}
};

