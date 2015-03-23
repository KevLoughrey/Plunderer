// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : Create a bomb that explodes after a set time, destroying nearby platforms
#pragma once

#include <BaseObject.h>
#include <Box2D\Box2D.h>
#include <DirtBlock.h>
#include <vector>
#include <SoundManager.h>
#include <TileBase.h>

class Bomb : public BaseObject
{
protected:
	///pointer to renderer
	SDL_Renderer *m_renderer;
	///pointer to box2d world
	b2World *m_world;
	///size of body 
	b2Vec2 m_dimensions;
	///box2d body params
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	///time until bomb explodes
	double m_fuseTime;
	///sensor for checking nearby platforms
	b2FixtureDef m_sensorDef;
	///vector to store blocks were colliding with
	std::vector<DirtBlock*> collidingWithBlocks;
public:
	///Creates a bomb
	/// \param[world] pointer to box2d world, used to create bodies
	/// \param[renderer] pointer to the renderer for drawing on screen
	/// \param[dimensions] size of the body
	/// \param[position] starting position of body
	/// \param[force] direction the body will travel when created
	Bomb(b2World *world, 
		SDL_Renderer *renderer,
		   b2Vec2 dimensions, 
		   b2Vec2 position,
		   b2Vec2 force
		   );
	bool alive;
	~Bomb(void);
	///Update the bombs fuse timer 
	/// \param[deltatime] time since last frame.
	bool Update(double deltatime);
	///Renders the particle
	/// \param[offset] the vector used offset the bomb by the camera position.
	void Render(b2Vec2 offset);
	///play a sound, vibrate controller, destroy nearby blocks
	void Explode();
	///remove body from works
	void DeleteBody();
	///add block to destroy
	void AddBlock(DirtBlock*);
	///remove block from destroy list
	void RemoveBlock(DirtBlock*);
	///return body
	b2Body *getBody();
	SDL_Rect stretchRect;
};

