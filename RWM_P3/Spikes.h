// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This is a static spike trap, if the player collides they lose one health

#pragma once

#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <SoundManager.h>
#include <TileBase.h>

class Spikes : BaseObject
{
public:
	/// Used to create a Spikes Object
	/// \param[world] The Box2d world used to add bodies
	/// \param[dimensions] the width and height of the object
	/// \param[position] the position to place the block
	/// \param[renderer] the renderer used to draw the block
	Spikes(b2World *world, 
		  b2Vec2 dimensions, 
		  b2Vec2 position, 
		  SDL_Renderer *renderer);
	/// Destroys the object
	~Spikes(void);
	/// \return the body of the spike
	b2Body* GetBody();
	/// draw the object 
	/// \param[offset] to draw the player in the correct position
	void Render(b2Vec2 offset);
protected:
	/// used to store the body varibales
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	/// the width and height of the object
	b2Vec2 m_dimensions;
	/// the renderer used to draw
	SDL_Renderer *m_renderer;
};

