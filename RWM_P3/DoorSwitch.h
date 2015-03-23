// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This Is used in multiplayer it has a sensor and is used to trigger the exit door to open

#pragma once

#include <SDL_image.h>
#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <Block.h>
#include <vector>
#include <KeyboardManager.h>
#include <SoundManager.h>
#include <TileBase.h>

class DoorSwitch : public Block
{
public:
	/// Used to create a DoorSwitch Object
	/// \param[world] The Box2d world used to add bodies
	/// \param[renderer] the renderer used to draw the block
	/// \param[position] the position to place the block
	DoorSwitch(b2World *world,
			   SDL_Renderer *renderer,
			   b2Vec2 position);
	/// Destroy the object
	~DoorSwitch(void);
	/// Draw the object
	/// \param[offset] used to draw the player in correct position based on the camera
	void Render(b2Vec2 offset);
	/// \return if the player has collided with the object
	bool CheckCollision();
	/// play the switch close animation
	void PlayClose();
	/// \return if the animation has finished
	bool GetAnimEnded();
	/// set the close variable to start the animation
	/// \param[close] used to set if the animation should play
	void setClose(bool close);

protected:
	/// the box2d world
	b2World *m_world;
	/// the renderer for drawing
	SDL_Renderer *m_renderer;
	/// the position to draw 
	SDL_Rect pos;
	/// used to define the body of the object
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	b2Vec2 m_dimensions;
	b2PolygonShape m_leftSensorShape;
	b2FixtureDef m_leftSensorDef;
	/// the current frame of the animation
	int m_frame;
	/// the initial position of the object
	b2Vec2 m_position;
	/// to store if the animation should be started
	bool startAnim;
	/// to store if the player has collided with the object
	bool hasCollided;
	/// so the sound only plays once
	bool once;
	/// for the current frame 
	int m_count;
	/// to track if the switch should be reset
	int m_resetCount;
	/// track if the animation has ended
	bool animEnded;
};

