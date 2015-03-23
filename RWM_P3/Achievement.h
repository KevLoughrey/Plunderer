// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Class for each individual achievement, which controls lock/unlock state, and rendering.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <TileBase.h>
#include <iostream>
#include <SoundManager.h>

class Achievement
{
public:
	/// Constructor
	/// Creates an Achievement object
	/// \name[in] name of the achievement
	/// \renderer[in] the sdl renderer
	Achievement(char* name,
				SDL_Renderer* renderer);

	/// Destructor
	/// Destroys an Achievement object
	~Achievement();

	/// Render
	/// Renders the achievement
	void Render();

	/// Get Name
	/// Returns the name of the achievement
	/// \return name of the achievemt as a char array
	char* GetName();

	/// Unlock
	/// Unlocks the achievement, makes it so that it can not be unlocked again
	void Unlock();
	
	/// Get Is Unlocked
	/// Returns whether the achievement has been unlocked
	/// \return bool m_isUnlocked
	bool GetIsUnlocked();

	/// Get Is Alive
	/// Returns whether the achievement is alive - ie whether it should be rendered
	/// \return bool m_isAlive
	bool GetIsAlive();

protected:
	///Name of the achievement
	char *m_name;

	///Texture for the achievement
	SDL_Texture *m_texture;

	///Reference to the SDL renderer
	SDL_Renderer *m_renderer;

	///Draw position for the achievement
	SDL_Rect m_position;

	///Has the achievement been unlocked?
	bool m_isUnlocked;

	///Is the achievement alive... ie. Should it be drawn?
	bool m_alive;

	///Count for how long the achievement should be drawn for
	int m_count;
};

