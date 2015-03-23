// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This is used for the entrance and exit of each level it contains sensors
//			 to detect if they player is within range of exiting the door

#pragma once
#include <SDL_image.h>
#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <Block.h>
#include <vector>
#include <KeyboardManager.h>
#include <SoundManager.h>
#include <TileBase.h>
#include <DoorSwitch.h>

class Door : public Block
{
public:
	// Used to create a Block Object
	/// \param[world] The Box2d world used to add bodies
	/// \param[renderer] the renderer used to draw the block
	/// \param[position] the position to place the block
	/// \param[type] if the block is destructable or not
	/// \param[doorSwitch] the refrence to the switch to activate the door
	Door(b2World *world,
		 SDL_Renderer *renderer,
		 b2Vec2 position,
		 int type,
		 DoorSwitch *doorSwitch = NULL);
	/// Destroys the door object
	~Door(void);
	/// draws the door
	/// \param[offset] draws the door in the correct position minus the offset
	void Render(b2Vec2 offset);
	/// \return if there was a collision between player and door
	bool CheckCollision();
	/// plays the door close animation
	void PlayClose();
	/// sets the bool to close the door
	/// \param[close] bool to set if the door is closed or not
	void setClose(bool close);
	/// \return if the animation has ended
	bool GetAnimEnded();
	/// \return if the anim ended in multiplayer
	bool GetMultiEnd();

protected:
	/// the Box2d world so we can add the bbody
	b2World *m_world;
	/// the renderer used for drawing
	SDL_Renderer *m_renderer;
	/// the drawing position of the object
	SDL_Rect pos;
	/// the initial position of the door
	b2Vec2 m_position;
	/// if its a start door or end door
	int m_type;
	/// vector for the door animations
	std::vector<SDL_Texture*> m_textureVector;
	/// used for the definition of the body
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	b2Vec2 m_dimensions;
	b2PolygonShape m_leftSensorShape;
	b2FixtureDef m_leftSensorDef;
	/// the door switch to activate the door in multiplayer
	DoorSwitch *m_doorSwitch;
	/// tracking when to start the animation
	bool startAnim;
	/// the current frame in the animation
	int m_frame;
	int m_count;
	/// if the player has collided with the door
	bool hasCollided;
	/// if the animation has ended
	bool animEnded;
	/// only play the sound once when entering or exiting door
	bool once;
	/// if the multiplayer game has ended
	bool multiEnd;
};

