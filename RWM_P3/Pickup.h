// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Gem pickups which will be scattered throughout the level.


#pragma once

#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <SoundManager.h>
#include <TileBase.h>
#include <Subject.h>

class Pickup : public BaseObject, public Observer
{
public:
	/// Constructor
	/// Creates a Pickup object
	/// \world[in] the world the pickup will be created in
	/// \dimensions[in] pixel dimensions of the pickup
	/// \position[in] pixel position of the pickup
	/// \renderer[in] the sdl renderer
	/// \subject[in] the subject for achievement unlocking
	Pickup(b2World *world, 
		  b2Vec2 dimensions, 
		  b2Vec2 position, 
		  SDL_Renderer *renderer,
		  Subject* subject);

	/// Destructor
	/// Destorys the pickup
	~Pickup();

	/// Render
	/// Renders the pickup
	/// \offset[in] player offset - offset the pickup so the camera appears to follow the player
	void Render(b2Vec2 offset);

	/// Set is dead
	/// Set whether the pickup has been picked up or not
	/// \toggle[in] what to set it to
	void SetIsDead(bool toggle);

	/// Get is dead
	/// Returns whether the pickup is dead - should it be deleted next update? 
	/// \return bool the value of m_isDead
	bool GetIsDead();

	/// Get Body
	/// Returns the pickup's body
	/// \return b2Body* of the pickup
	b2Body* GetBody();

	/// On notify
	/// What to do when notified
	/// \theEvent[in] the event that has occured
	virtual void OnNotify(char* theEvent) {}

protected:
	///basic box2d setup
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;

	///dimensions in pixels
	b2Vec2 m_dimensions;

	///reference to the sdl renderer
	SDL_Renderer *m_renderer;
	
	///is the pickup dead? should it be removed at the next update?
	bool m_isDead;

	///reference to the subject for the observer pattern
	Subject *m_subject;
};