// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Player - Box2D object that the player controls. The player character.

#pragma once

#include <Box2D\Box2D.h>
#include <KeyboardManager.h>
#include <BaseObject.h>

#include <Bomb.h>
#include <Explosion.h>
#include <vector>

#include <Memento.h>
#include <TileBase.h>
#include <string>
#include <PacketStream.h>

#include <FSM.h>
#include <PlayerState.h>
#include <PlayerIdle1.h>
#include <PlayerIdle2.h>
#include <PlayerIdle3.h>
#include <PlayerWalk.h>
#include <PlayerJump.h>
#include <PlayerClimb.h>
#include <PlayerThrowBomb.h>
#include <PlayerSprinting.h>
#include <PlayerDying.h>
#include <PlayerSprintJump.h>
#include <PlayerGrab.h>
#include <PlayerWhipState.h>
#include <PlayerStomp.h>

#include <Subject.h>
#include <sstream>

#include <RaycastListener.h>
#include <Mummy.h>
#include <MapManager.h>


class LeftCommand;
class RightCommand;
class JumpCommand;

class Player : public BaseObject, public Observer
{

public:
	/// Constructor
	/// Creates a Player object
	/// \world[in] the world the player will be created in
	/// \dimensions[in] pixel dimensions of the player
	/// \position[in] pixel position of the player
	/// \renderer[in] the sdl renderer
	/// \subject[in] the subject for unlocking achievements
	/// \subject[in] reference to the map manager
	Player(b2World *world, 
		   b2Vec2 dimensions, 
		   b2Vec2 position, 
		   SDL_Renderer *renderer,
		   Subject* subject,
		   MapManager *mapManager);

	/// Destructor
	/// Destroys the player object
	~Player();

	/// Serialize
	/// Serialize the player's info to a packet
	/// \return PacketStream* the packet stream
	PacketStream* Serialize();

	/// Deserialize
	/// Converts a packet back into info
	/// \PacketStream[in] the stream to be converted
	/// \return tuple containing the info
	std::tuple<bool,bool,bool> Deserialize(PacketStream*);

	/// Update network players
	/// Update the network player in a multiplayer game
	/// \deltaTime[in] time since the last update
	/// \return bool updated
	bool UpdateNetworkPlayers(double deltatime);

	/// Set linear velocity
	/// Set the player body's linear velocity
	/// \vel[in] the new velocity
	void SetLinearVelocity(b2Vec2 vel);

	/// Apply force to centre
	/// Apply a force to the centre of the player's body
	/// \vel[in] the force to be applied
	void ApplyForceToCenter(b2Vec2 vel);

	/// Update the player
	/// Update the local player in singleplayer and multiplayer
	/// \deltaTime[in] time since the last update
	/// \return bool updated
	bool Update(double deltatime);

	/// Handle input
	/// Handle all keyboard input
	void HandleInput();

	/// Render
	/// Renders the player
	/// \offset[in] player offset - offset the player so the camera appears to follow the player
	void Render(b2Vec2 offset);

	/// Get position
	/// Get the position of the player's body
	/// \return b2Vec2 position
	b2Vec2 GetPosition();

	/// Set Can Jump
	/// Set whether the player can jump
	/// \toggle[in] the value to set the bool to
	void SetCanJump(bool toggle);

	/// Decrease health
	/// Decrease the player's health
	/// \difference[in] the amount to decrease by
	void DecreaseHealth(int difference);

	/// Decrease health
	/// Decrease the player's health
	/// \difference[in] the amount to decrease by
	/// \cause[in] what caused the injury
	void DecreaseHealth(int difference, char* cause);

	/// Increase required right ladder contacts
	/// Increase the number of ladder contacts to the right of the player by one
	void IncreaseRequiredRightLadderContacts();

	/// Decrease required right ladder contacts
	/// Decrease the number of ladder contacts to the right of the player by one
	void DecreaseRequiredRightLadderContacts();
	
	/// Increase required left ladder contacts
	/// Increase the number of ladder contacts to the left of the player by one	
	void IncreaseRequiredLeftLadderContacts();

	/// Decrease required left ladder contacts
	/// Decrease the number of ladder contacts to the left of the player by one
	void DecreaseRequiredLeftLadderContacts();

	/// Increase jump contacts
	/// Increase the number of jump contacts by one
	void IncreaseJumpContacts();

	/// Decrease jump contacts
	/// Decrease the number of jump contacts by one
	void DecreaseJumpContacts();

	/// Increase the number of top ladder contacts
	/// Increase the number of ladder contacts above the player by one	
	void IncreaseTopLadderContacts();

	/// Decrease the number of top ladder contacts
	/// Decrease the number of ladder contacts above the player by one	
	void DecreaseTopLadderContacts();

	/// Increase the number of upper ladder contacts
	/// Increase the number of upper ladder contacts by one	
	void IncreaseLadderAboveContacts();

	/// Decrease the number of upper ladder contacts
	/// Decrease the number of upper ladder contacts by one	
	void DecreaseLadderAboveContacts();

	/// Increase gold
	/// Increase the gold the player has
	void IncreaseGold();

	/// Bounce
	/// Bounce up after jumping on an enemy
	void Bounce();

	/// Kickback
	/// Get knocked back after being hit by an enemy
	void Kickback(b2Vec2 position);

	/// Set injured
	/// Set whether the player is injured
	/// \toggle[in] the value to set it to
	void SetInjured(bool toggle);

	/// Rewind
	/// Reverse time by popping positions from the memento vector
	void Rewind();

	/// Render
	/// Renders an explosion
	/// \offset[in] player offset - offset the explosion so the camera appears to follow the player
	void RenderExplosion(b2Vec2 offset);

	/// Set Alive
	/// Set whether the player is alive
	/// \alive[in] the value to set it to
	void SetAlive(bool alive);

	/// Set Draw
	/// Set whether the player should be drawn
	/// \set[in] the value to set it to
	void setDraw(bool set);

	/// Decrease bombs
	/// Decrease the number of bombs the player has
	void DecreaseNumBombs();

	/// Increase bombs
	/// Increase the number of lives the player has
	void IncreaseLives();

	/// Can throw bomb
	/// Can the player throw a bomb
	/// \return bool can the player throw
	bool CanThrowBomb();

	/// Check dead
	/// Check if the player is dead
	/// \return bool is the player dead
	bool CheckDead();

	/// Append next level
	/// Add the next level
	void AppendNextLevel();

	/// Append door open
	/// Add if a door has been opened
	void AppendDoorOpen();

	/// Append game over
	/// Add a gameover state
	void AppendGameOver();

	/// Set look
	/// Set the direction the player is facing
	/// \string[in] the direction (left/right)
	void SetLook(std::string);

	/// Get look
	/// Get the direction the player is facing
	/// \return string the direction (left/right)
	std::string GetLook();

	/// Set current image
	/// Set the current player image for rendering
	/// \type[in] image type
	/// \index[in] index of image
	void SetCurrentImage(std::string type, int index);

	/// Increase Hourglasses
	/// Increase the number of hourglasses the player has by one
	void InceraseNumHourglasses();

	/// Get hourglasses
	/// Get the number of hourglasses the player has
	/// \return int number of hourglasses 
	int GetHourglasses();

	/// Get idle counter
	/// Get the value of idle counter
	/// \return int the current value of the counter
	int GetIdleCounter();

	/// Set idle counter
	/// Set the value of idle counter
	/// \int[in] new value
	void SetIdleCounter(int);

	/// Get on ground
	/// Get the value of this state
	/// \return bool is player in this state
	bool GetOnGround() const;

	/// Get on ladder
	/// Get the value of this state
	/// \return bool is player in this state
	bool GetOnLadder() const;

	/// Get on moving up ladder
	/// Get the value of this state
	/// \return bool is player in this state
	bool GetMovesUpLadder() const;

	/// Get moving down ladder
	/// Get the value of this state
	/// \return bool is player in this state
	bool GetMovesDownLadder() const;

	/// Get number of bombs
	/// Get the number of bombs the player has
	/// \return int total bombs
	int GetBombs();

	/// Drop bomb
	/// Spawn and drop a new bomb
	void DropBomb();

	/// Get velocity
	/// Get the velocity of the player
	/// \return b2vec2 body velocity
	b2Vec2 GetVelocity() const;

	/// Get can jump
	/// Get whether the player can jump
	/// \return bool can jump?
	bool GetCanJump() const;

	/// Use whip
	/// Use the whip - raycast in direction facing and kill any enemies that are hit
	void UseWhip();

	/// On notify
	/// What to do when notified of an event by a subject
	/// \theEvent[in] the event that has occured
	virtual void OnNotify(char* theEvent) {}

	/// Set behind door
	/// Set if the player is behind the exit door (has exited the level)
	/// \toggle[in] new value
	void SetBehindDoor(bool toggle);

	/// Get behind door
	/// Get if the player is behind the exit door (has exited the level)
	/// \return bool behind door
	bool GetBehindDoor() const;

	/// Execute left command
	/// Execute the player's left command
	void ExecuteLeftCommand();

	/// Execute right command
	/// Execute the player's right command
	void ExecuteRightCommand();

	/// Execute X command
	/// Execute the player's X button command (jump)
	void ExecuteXCommand();

	/// Set whipping
	/// Set whether the player is whipping
	/// \bool[in] new value
	void SetWhipping(bool);

	/// Modify state
	/// Set the player's state
	/// \newState[in] the new state
	void ModifyState(PlayerState *newState);
	
	/// Set gravity scale
	/// Set the player body gravity scale
	/// \float[in] new scale
	void SetGravityScale(float);

protected:
	///basic box2d setup
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	b2Vec2 m_dimensions;
	b2PolygonShape m_sensorShape;
	b2FixtureDef m_sensorDef;
	b2EdgeShape m_edgeShape;

	///friction for base of player
	b2PolygonShape m_frictionShape;
	b2FixtureDef m_frictionDef;

	///ladder sensors - detect player contacts with ladder
	b2PolygonShape m_topLadderSensorShape;
	b2FixtureDef m_topLadderSensorDef;
	b2PolygonShape m_bottomLadderSensorShape;
	b2FixtureDef m_bottomLadderSensorDef;
	b2PolygonShape m_jumpSensorShape;
	b2FixtureDef m_jumpLadderSensorDef;

	///box2d world which contains the player
	b2World *m_world;

	///reference to the sdl renderer
	SDL_Renderer *m_renderer;

	///the button commands
	LeftCommand *m_buttonLeft;
	RightCommand *m_buttonRight;
	JumpCommand *m_buttonX;

	///map manager reference
	MapManager *m_mapManager;

	///player health
	int m_health;

	///is the player alive
	bool m_alive;

	///is the player injured (have they just been hit by an enemy)
	bool m_injured;

	///were these buttons pressed at the previous update
	bool m_buttonXPrevPressed;
	bool m_buttonSPrevPressed;

	///is time rewinding
	bool m_rewindPressed;

	///is the player sprinting
	bool m_isSprinting;

	///should the player be drawn
	bool m_shouldDraw;

	///how many surfaces that can be jumped off are beneath the player
	int m_numJumpContacts;

	///is the player touching a ladder
	int m_numRequiredRightLadderContacts;
	int m_numRequiredLeftLadderContacts;
	int m_numTopLadderContacts;
	int m_numLadderAboveContacts;
	bool m_onLadder;
	
    ///how many hourglasses does the player have
	int m_numHourglasses;
	
	///was the whip in use last update
	bool m_whipPrevUsed;

	///counters
	int count;
	int m_idleCounter;

	///vector of player bombs
	std::vector<Bomb*> bombs;
	///vector of bomb explosions
	std::vector<Explosion*> explosions;

	///the packet stream for multiplayer 
	PacketStream* m_packetStream;
	
	/// Append bomb to packet stream
	/// When a player throws a bomb in multiplayer, serialize the bomb to the packet stream
	/// \pos[in] bomb position
	/// \dir[in] bomb direction
	void AppendBombToPStream(b2Vec2 pos, b2Vec2 dir);

	/// Split string
	/// Split the string contained in the packet stream
	/// \s[in] the string from packet stream
	/// \return vector<string> the split strings
	vector<string> splitString(std::string s);

	///the player's memento
	Memento *m_memento;

	///finite state machine
	static FSM s_fsm;
	PlayerState *m_state; 
	std::string m_direction;
	std::string m_event;

	///reference to the subject for achievement unlocking
	Subject *m_subject;

	///is the player exiting the level (prevent collisions with things in the level)
	bool m_behindDoor;

	///is the player running the dying animation (prevent actions like exiting level, jumping)
	bool m_dying;

	///texture for the whip
	SDL_Texture *m_whipTexture;

	///is the player whipping
	bool whipping;
};

#include "LeftCommand.h"
#include "RightCommand.h"
#include "JumpCommand.h"