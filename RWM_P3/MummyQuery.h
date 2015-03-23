// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : USED TO CHECK COLLISIONS OF MUMMY AABBs WITH FIXTURES.  

#pragma once

#include <Box2d/Box2d.h>
#include <vector>

class MummyQuery : public b2QueryCallback
{

public:
	std::string m_type;
	std::string m_event;

	MummyQuery():
		m_type("In Front"),
		m_event("Nothing")
	{}
     
	bool ReportFixture(b2Fixture* fixture) override
	{
		// This value will be returned.
		bool l_continueSearch = true;
  
		// List of fixtures to ignore
		if(	fixture->GetUserData() == "bombSensor" ||
			fixture->GetUserData() == "batCeilingSensor" ||
			fixture->GetUserData() == "batPlayerSensor"  ||
			fixture->GetUserData() == "bat" ||
			fixture->GetUserData() == "snake"  ||
			fixture->GetUserData() == "scarab" ||
			fixture->GetUserData() == "life" ||
			fixture->GetUserData() == "gold")
		{
			l_continueSearch = true;
		}

		// For other fixtures, do check based on check type (4 in total)
		// Check will see what fixture was detected and will modify "m_event",
		// which will be retrieved in Enemy Manager.
		else
		{
			#pragma region In Front
			if(m_type == "In Front")
			{
				if(fixture->GetUserData() == "player")
				{
					m_event = "Player in Front";
					l_continueSearch = false;
				}

				else if(fixture->GetUserData() == "block" ||
						fixture->GetUserData() == "arrowTrap")
				{
					m_event = "Obstacle";
					l_continueSearch = false;
				}

				else if(fixture->GetUserData() == "solidBlock" || 
						fixture->GetUserData() == "spike" )
				{
					m_event = "Wall in Front";
					l_continueSearch = false;
				}

				else 
				{
					l_continueSearch = true;
				}
			}
			#pragma endregion

			#pragma region Wall Height
			if(m_type == "Wall Height")
			{
				if(fixture->GetUserData() == "block" ||
					fixture->GetUserData() == "arrowTrap"|| 
					fixture->GetUserData() == "spike")
				{
					m_event = "Wall in Front";
					l_continueSearch = false;
				}

				else
				{
					m_event = "1 Block in Front";
					l_continueSearch = false;
				}
			}
			#pragma endregion

			#pragma region Check Floor
			if(m_type == "Check Floor" && fixture->GetUserData() != "mummy")
			{
				if((fixture->GetUserData() != "block" &&
					fixture->GetUserData() != "arrowTrap" &&
					fixture->GetUserData() != "solidBlock") )
				{
					m_event = "Nothing";
					l_continueSearch = false;
				}

				else
				{
					m_event = "Floor Presents";
					l_continueSearch = false;
				}
			}
		#pragma endregion

			#pragma region Check Deepness
			if(m_type == "Check Deepness" && fixture->GetUserData() != "mummy")
			{
				if(	   (fixture->GetUserData() != "block" &&
						fixture->GetUserData() != "arrowTrap" &&
						fixture->GetUserData() != "solidBlock") || 
						(fixture->GetUserData() == "spike") )
				{
					m_event = "Pit";
					l_continueSearch = false;
				}

				else 
				{
					m_event = "1 Block Step";
					l_continueSearch = false;
				}
			}
		#pragma endregion
		}
		return l_continueSearch;
	}
};

