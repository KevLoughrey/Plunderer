// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: A Box2D ladder tile, which can be climbed by player objects.

#pragma once

#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <Block.h>
#include <TileBase.h>

class Ladder : public Block
{
public:
	/// Constructor
	/// Creates a new ladder
	/// \world[in] the box2d world the ladder will be created in
	/// \dimensions[in] pixel dimensions of the ladder
	/// \position[in] pixel position of the ladder
	/// \renderer[in] the sdl renderer
	Ladder(b2World *world, 
		   b2Vec2 dimensions, 
		   b2Vec2 position, 
		   SDL_Renderer *renderer);

	/// Destructor
	/// Destorys the ladder
	~Ladder();

	/// Render
	/// Renders the laddrt
	/// \offset[in] player offset - offset the ladder so the camera appears to follow the player
	void Render(b2Vec2 offset);

protected:
	///Basic box2d setup
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	b2Vec2 m_dimensions;

	///Left hand side sensor for collision with the player
	b2PolygonShape m_leftSensorShape;
	b2FixtureDef m_leftSensorDef;

	///Right hand side sensor for collision with the player
	b2PolygonShape m_rightSensorShape;
	b2FixtureDef m_rightSensorDef;

	///The SDL renderer
	SDL_Renderer *m_renderer;
};