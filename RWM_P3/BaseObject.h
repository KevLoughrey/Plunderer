// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Simple base object for others to inherit from.

#pragma once

#include <Box2D\Box2D.h>
#include <SDL_image.h>
#include <Constants.h>
#include <Observer.h>

class BaseObject
{
public:
	/// Constructor
	/// Abstract base object - default constructor
	BaseObject() {}

	/// Destructor
	/// Destroys the object
	~BaseObject() {}

protected:
	///The object's texture
	SDL_Texture *m_texture;
};