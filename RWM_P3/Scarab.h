// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Scarab which flocks using the boids algorithm.

#pragma once

#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <TileBase.h>
#include <vector>

class Scarab : public BaseObject
{
public:
	/// Constructor
	/// Creates a Scarab object
	/// \world[in] the world the scarab will be created in
	/// \dimensions[in] pixel dimensions of the scarab
	/// \position[in] pixel position of the scarab
	/// \renderer[in] the sdl renderer
	Scarab(b2World *world, 
		  b2Vec2 dimensions, 
		  b2Vec2 position, 
		  SDL_Renderer *renderer);

	/// Destructor
	/// Destroys the object
	~Scarab();

	/// Render
	/// Renders the scarab
	/// \offset[in] player offset - offset the scarab so the camera appears to follow the player
	void Render(b2Vec2 offset);

	/// Get Body
	/// Returns the scarab's body
	/// \return b2Body* of the pickup
	b2Body* GetBody();

	/// Seek
	/// Seek towards a vector
	/// \target[in] the vector to seek
	/// \return b2Vec2 the force that should be applied to the scarab
	b2Vec2 Seek(b2Vec2 target);

	/// Separate
	/// Steer the scarab away from its neighbours
	/// \scarabs[in] the other scarabs in the flock
	/// \return b2Vec2 the force that should be applied to the scarab
	b2Vec2 Separate(std::vector<Scarab*> scarabs);

	/// Align
	/// Align the scarab to the average heading of its neighbours
	/// \scarabs[in] the other scarabs in the flock
	/// \return b2Vec2 the force that should be applied to the scarab
	b2Vec2 Align(std::vector<Scarab*> scarabs);

	/// Cohesion
	/// Steer the scarab towards the average position of its neighbours
	/// \scarabs[in] the other scarabs in the flock
	/// \return b2Vec2 the force that should be applied to the scarab
	b2Vec2 Cohesion(std::vector<Scarab*> scarabs);

	/// Flock
	/// Flock - call the separate, align, and cohesion methods for the scarab and apply their results
	/// \scarabs[in] the other scarabs in the flock
	/// \player[in] the player to seek towards
	void Flock(std::vector<Scarab*> scarabs, b2Vec2 playerPos);

protected:
	///basic box2d setup
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;

	///pixel dimensions of the scarab
	b2Vec2 m_dimensions;

	///reference to the sdl renderer
	SDL_Renderer *m_renderer;

	///max steering force of a scarab
	float m_maxSteeringForce;

	///max speed of a scarab
	float m_maxSpeed;

	///the desired separation for the flock
	float m_desiredSeparation;

	///distance to neighbours for the flock
	float m_distanceToNeighbour;

	///current animation frame
	int currFrame;
};