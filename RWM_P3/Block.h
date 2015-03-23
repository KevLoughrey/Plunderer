// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This Class Is used for all the platform and destructable blocks used in the tiled
//			 map

#pragma once

#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <Constants.h>

class Block {
public:
	Block() {}
	/// Used to create a Block Object
	/// \param[world] The Box2d world used to add bodies
	/// \param[dimensions] the width and height of the object
	/// \param[position] the position to place the block
	/// \param[renderer] the renderer used to draw the block
	Block(b2World *world, 
		  b2Vec2 dimensions, 
		  b2Vec2 position, 
		  SDL_Renderer *renderer) 
	: m_renderer(renderer) {}

	/// Destroys the Object
	~Block() {}

	/// Draws the Block Object
	/// \param[offset] the offset the player has moved to draw tyhe block in the correct position
	virtual void Render(b2Vec2 offset) = 0;

protected:
	/// Used to store the box2d body information
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2Fixture *m_fixture;
	b2FixtureDef m_fixtureDef;

	/// the width and height of the object
	b2Vec2 m_dimensions;

	/// the renderer used to draw the object
	SDL_Renderer *m_renderer;
};