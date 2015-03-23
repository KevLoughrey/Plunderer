// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Arrow object, which are fired from arrow traps.

#pragma once

#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <SoundManager.h>
#include <TileBase.h>

class Arrow : BaseObject
{
public:
	/// Constructor
	/// Creates an Arrow object
	/// \world[in] the world the arrow will be created in
	/// \dimensions[in] pixel dimensions of the arrow
	/// \position[in] pixel position of the arrow
	/// \renderer[in] the sdl renderer
	/// \velocity[in] initial velocity of the arrow (metres per second)
	Arrow(b2World *world, 
		  b2Vec2 dimensions, 
		  b2Vec2 position, 
		  SDL_Renderer *renderer,
		  b2Vec2 velocity);

	/// Destructor
	/// Destroys an Arrow object
	~Arrow();
	
	/// Get Body
	/// Returns the arrow's body
	/// \return b2Body* of the arrow
	b2Body* GetBody();

	/// Render
	/// Renders the arrow
	/// \offset[in] player offset - offset the arrow so the camera appears to follow the player
	void Render(b2Vec2 offset);


	bool GetIsBroken() const;
	void SetBroken();

protected:
	///Basic box2D setup
	b2Body *m_body;
	b2World *m_world;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	b2Fixture *m_fixture;

	///Pixel dimensions
	b2Vec2 m_dimensions;

	///Reference to the SDL renderer
	SDL_Renderer *m_renderer;
	
	///Is the arrow facing left or right
	int m_type;

	b2PolygonShape m_sensorShape;
	b2FixtureDef m_sensorDef;
	bool m_broken;
};

