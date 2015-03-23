// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Class which holds a vector of all achievements in the game.

#pragma once

#include <Observer.h>
#include <Subject.h>
#include <Achievement.h>

class Achievements : public Observer
{
public:
	/// Constructor
	/// Creates an Achievements Observer object
	/// \subject[in] the subject for the project
	/// \renderer[in] the sdl renderer
	Achievements(Subject *subject, SDL_Renderer* renderer);

	/// Destructor
	/// Destroys an Achievements object
	~Achievements();

	/// On Notify
	/// Observer patten - what to do when this object is notified
	/// \theEvent[in] event which has occured
	virtual void OnNotify(char* theEvent);

	/// Render
	/// Renders the achievements
	void Render();

private:
	/// Unlock
	/// Unlock a specific achievement
	/// \achievementName[in] the achievement to be unlocked
	void Unlock(char* achievementName);

	///Reference to the game's subject
	Subject *m_subject;

	///Vector of all available achievements
	std::vector<Achievement*> m_achievements;
};