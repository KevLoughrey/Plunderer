// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Arrow trap object, which fires arrow objects when their sensor is triggered.

#pragma once

#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <SoundManager.h>
#include <Arrow.h>
#include <TileBase.h>

class ArrowTrap : BaseObject
{
public:
	/// Constructor
	/// Creates an Arrow Trap object
	/// \world[in] the world the arrow trap will be created in
	/// \dimensions[in] pixel dimensions of the arrow trap
	/// \position[in] pixel position of the arrow trap
	/// \renderer[in] the sdl renderer
	/// \type[in] will the trap fire to the left or right? 
	ArrowTrap(b2World *world, 
		  b2Vec2 dimensions, 
		  b2Vec2 position, 
		  SDL_Renderer *renderer,
		  int type);

	/// Destructor
	/// Destroys an Arrow trap object
	~ArrowTrap();

	/// Get Body
	/// Returns the arrow trap's body
	/// \return b2Body* of the arrow trap
	b2Body* GetBody();

	/// Render
	/// Renders the arrow trap
	/// \offset[in] player offset - offset the arrow trap so the camera appears to follow the player
	void Render(b2Vec2 offset);

	/// Fire arrow
	/// Initialises and fires the trap's associated arrow
	void FireArrow();

protected:
	///Basic box2D setup
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;

	///Pixel dimensions of the trap
	b2Vec2 m_dimensions;

	///Reference to the SDL renderer
	SDL_Renderer *m_renderer;

	///Left or right facing trap
	int m_type;

	///The sensor which will detect the player and fire the trap
	b2PolygonShape m_sensorShape;
	b2FixtureDef m_sensorDef;

	///The arrow that will be fired
	Arrow *m_arrow;

	///Can the trap fire?
	bool canFire;

	///Has the trap fired?
	bool hasFired;

	///Delay from initia; triggering to firing
	int m_count;

	///Only play arrow firing sound once
	bool doOnce;
	
	///Draw the arrow head in unfired traps
	SDL_Texture *m_textureArrowHead;

	///Renderer fliptype
	SDL_RendererFlip flipType;
};

