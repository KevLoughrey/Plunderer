// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Observer which will be used to unlock achievements.

#pragma once

class Observer
{
public:
	/// Destructor
	/// Destorys the observer
	virtual ~Observer() {}

	/// On notify
	/// What to do when notified
	/// \theEvent[in] the event that has occured
	virtual void OnNotify(char* theEvent) = 0;
	
	///type of observer
	char* m_type;
};