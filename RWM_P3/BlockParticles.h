// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : Multiple instances created when an object is destroyed for particle effects
#pragma once

#include <Box2D\Box2D.h>
#include <SDL.h>
#include <SDL_image.h>
#include <BaseObject.h>
#include <TileBase.h>

class BlockParticles
{
public:
	///Creates a particle
	/// \param[pos] particle position.
	/// \param[renderer] a pointer to the game renderer so we can draw the object.
	/// \param[type] 1 = block particle,  2 = blood particle, 3 = bat particle, 4 = mummy particle
	BlockParticles(b2Vec2 pos, 
				   SDL_Renderer *renderer,
				   int type);
	~BlockParticles();
	///Renders the particle
	/// \param[offset] the vector used offset the particle by the camera position.
	void Draw(b2Vec2 offset);
	void Destroy();
	///Update the particles position, time to live and its velocity
	/// \param[deltatime] time since last frame
	void Update(double deltatime);
	
	bool isAlive();

protected:	
	///position in world
	b2Vec2 m_pos;
	///size when rendering
	b2Vec2 m_size;
	///velocity for updating position
	b2Vec2 m_velocity;
	const double m_gravity;
	const int m_gravityScale;
	///colour of particle
	int m_type;
	///pointer to renderer for drawing
	SDL_Renderer *m_renderer;
	///alive bool for drawing
	bool m_alive;
	///how long until the particle is destroyed
	double m_timeToLive;
	
	const int m_secondsToLive;
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2Fixture *m_fixture;
	b2FixtureDef m_fixtureDef;
};
