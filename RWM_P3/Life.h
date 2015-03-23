// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This Is a life pickup object which gives the player an extra life when a contact occours

#pragma once

#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <SoundManager.h>
#include <TileBase.h>
#include <Subject.h>

class Life : public BaseObject
{
public:
	/// Used to create a Block Object
	/// \param[world] The Box2d world used to add bodies
	/// \param[dimensions] the width and height of the object
	/// \param[position] the position to place the block
	/// \param[renderer] the renderer used to draw the block
	/// \param[subject] notifys the observer when collided with
	Life(b2World *world, 
		  b2Vec2 dimensions, 
		  b2Vec2 position, 
		  SDL_Renderer *renderer,
		  Subject *subject);
	/// Destroy the object
	~Life(void);
	/// Draw the Object
	/// \param[offset] draws the player in the correct posiiton
	void Render(b2Vec2 offset);
	/// Sets if the life is dead
	/// \param[toggle] sets if the life is alive or not
	void SetIsDead(bool toggle);
	/// \return if the life is dead
	bool GetIsDead();
	/// \return the body of the life
	b2Body* GetBody();
	/// notifys the observer a life has been collected
	/// \param[theEvent] a string to send which event was fired
	virtual void OnNotify(char* theEvent) {}

protected:
	/// used to define the body
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	b2Vec2 m_dimensions;
	/// renderer used for drawing
	SDL_Renderer *m_renderer;
	/// track if the life is alive
	bool m_isDead;
	/// used for the observer to check if a life has been picked up
	Subject *m_subject;
};

