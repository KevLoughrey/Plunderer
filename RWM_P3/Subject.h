// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Subject which is used in observer pattern. Maintains a list of all observers.

#pragma once

#include <Observer.h>
#include <vector>
#include <iostream>

class Subject
{
public:
	/// Constructor
	/// Creates a Subject object
	Subject();

	/// Destructor
	/// Destroys the object
	~Subject() {}

	/// Add observer
	/// Add an observer to the list of observers
	/// \observerToAdd[in] reference to the observer to be added
	void AddObserver(Observer* observerToAdd);

	/// Remove observer
	/// Remove an observer from the list of observers
	/// \observerToRemove[in] reference to the observer to be removed
	void RemoveObserver(Observer* observerToRemove);

	/// Notify
	/// Notify all observers of an event
	/// \theEvent[in] the event that has occured
	void Notify(char* theEvent);

	/// Set active
	/// Is the subject active? Should it notify observers of incoming events?
	/// \toggle[in] set whether the subject is active or not
	void SetActive(bool toggle);

protected:
	///vector of observers that the subject will notify
	std::vector<Observer*> m_observers;

	///is this subject active?
	bool m_isActive;
};