// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Custom collision listener to detect and react to Box2D collisions.

#pragma once

#include <Box2D\Box2D.h>
#include <vector>
#include <string>
#include <Game.h>
#include <DoorSwitch.h>
using namespace std;

class CollisionListener : public b2ContactListener
{
public:
	///Instance of the listener - singleton
	static CollisionListener *m_instance;

	/// Get Listener
	/// Returns the listener instance
	/// \return CollisionListener* the listener
	static CollisionListener* getListener();

	/// Constructor
	/// Creates an Collision Listener object
	CollisionListener();

	/// Destructor
	/// Destroys the object
	~CollisionListener();

	/// Begin Contact
	/// What to do when two fixtures come into contact
	/// \contact[in] the contact
	void BeginContact(b2Contact *contact);

	/// End Contact
	/// What to do when two fixtures stop contact/colliding
	/// \contact[in] the contact
	void EndContact(b2Contact *contact);

	/// Pre Solve
	/// What to do when two fixtures are about to collide
	/// \contact[in] the contact
	/// \oldManifold[in] the old box2d manifold
	void PreSolve(b2Contact *contact, 
				  const b2Manifold *oldManifold);

	/// Post Solve
	/// What to do when two fixtures have finished colliding
	/// \contact[in] the contact
	/// \impulse[in] the impulse of the collision
	void PostSolve(b2Contact *contact, 
				   const b2ContactImpulse *impulse);

	/// Set World
	/// Set the world for this listener
	/// \world[in] the box2d world 
	void SetWorld(b2World *world);
	
	///The world containing the listener
	static b2World *m_world;
};

