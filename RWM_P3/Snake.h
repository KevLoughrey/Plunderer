// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: SNAKE ENEMY.

#pragma once

#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <FSM.h>
#include <SoundManager.h>
#include <TileBase.h>
#include <Subject.h>
#include <BlockParticles.h>

class Snake 
:	public BaseObject
{

private:
	/// AI Finite State Machine.
	static FSM m_fsm;

	/// Map which stores function pointers.
	static std::map<std::string, std::function<void(Snake&)>> m_actionMap;

	/// Body size.
	static b2Vec2 s_dimensions;
 
	static float s_speed;
	static float s_attackMultiplier;
	static float s_slowdownMultiplier;
	static float s_minVelXBeforeTurning ;
	static float s_pitCheckValue;

	static bool s_initializedFSM;


public:
	/// Constructor.
	/// Creates a Snake object.
	/// \world[in] the world the snake will be created in
	/// \position[in] pixel position of the snake
	/// \renderer[in] the sdl renderer
	/// \subject[in] the subject for unlocking achievements
	Snake(b2World *world, 
		  b2Vec2 position, 
		  SDL_Renderer *renderer,
		  Subject* subject);

	/// Destructor.
	/// Destroys the object.
	~Snake();

	/// Render.
	/// Renders the snake.
	/// \offset[in] player offset - offset the snake so the camera appears to follow the player
	void Render(b2Vec2 offset);

	/// Set is dead.
	/// Set whether the snake is dead or not.
	/// \toggle[in] the value to set to
	void SetIsDead(bool toggle);

	/// Set look.
	/// Set the direction the snake is facing.
	/// \dir[in] the direction (left or right)
	void SetLook(std::string dir);

	/// Get is dead.
	/// Get whether the snake is dead.
	/// \return bool is the snake dead
	bool GetIsDead() const;

	/// Get look.
	/// Get the direction the snake is facing.
	/// \return string direction (left or right)
	std::string GetLook() const;

	/// Get Body.
	/// Returns the snake's body.
	/// \return b2Body* of the snake
	b2Body* GetBody() const;

	/// Destroy.
	/// Destroys all entities associated with the snake.
	void Destroy();

	/// Destroy Body.
	/// Destroys the snake's box2d body.
	void DestroyBody();

	/// Update particles.
	/// Update the snake's particles when it is killed.
	/// \deltaTime[in] time since the last update
	void Update(double deltaTime);

	/// Should remove
	/// Should the snake be removed?
	/// \return bool should remove
	bool ShouldRemove();

	/// Get Initialized.
	/// Returns snake's FSM Initialized boolean.
	/// \return bool is FSM Initialized
	static bool GetInit();

	/// Set Initialized.
	/// Set the FSM Initialized.
	/// \par[in] toggle
	static void SetInit(bool);

	/// Get Size.
	/// Returns the snake's size.
	/// \return b2Vec2 size the mummy
	static b2Vec2 GetSize();

	/// Get Pit Check value.
	/// Returns the Pit Check value for snake, 
	/// which is used for AI.
	/// \return float deepness.
	static float GetPitCheck();

	/// Inserts new FSM Element.
	/// Inserts FSM Element for Snake AI handling.
	/// \state1[in] current state
	/// \evnt[in] event (or trigger)
	/// \action[in] action (or responce)
	/// \state2[in] new state
	static void Snake::PushFSMelement(	std::string state1,
										std::string evnt,
										std::string action,
										std::string state2);

	/// Update FSM.
	/// Update snake's FSM.
	/// \evnt[in] current Event
	void FSMUpdate(std::string evnt);

	virtual void OnNotify(char* theEvent) {}

protected:
	///basic box2d setup
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	
	///reference to the sdl renderer 
	SDL_Renderer *m_renderer;

	///is the snake dead.
	bool m_isDead;

	///which direction is snake facing.
	std::string m_look;

	///the current state of the snake.
	std::string m_state;

	void Move();
	void Turn();
	void Attack();

	///subject for unlocking achievements.
	Subject* m_subject;

	///is the snake alive? should it be removed at the next update.
	bool m_alive;

	///vector of particles for blood when snake dies.
	std::vector<BlockParticles*> m_blockBits;

	///number of blood particles to be created.
	int m_numParticles;

	///has the snake's box2d body been destroyed?
	bool m_isBodyDestroyed;
};