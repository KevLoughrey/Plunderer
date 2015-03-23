// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : MUMMY ENEMY  

#pragma once

#include <BaseObject.h>
#include <FSM.h>
#include <SoundManager.h>
#include <TileBase.h>
#include <BlockParticles.h>
#include <Subject.h>

class Mummy 
:	public BaseObject
{

public:
	/// Constructor
	/// Creates a Mummy object
	/// \world[in] the world the mummy will be created in
	/// \position[in] pixel position of the mummy
	/// \renderer[in] the sdl renderer
	/// \subject[in] the subject for unlocking achievements
	Mummy(b2World *world, 
		  b2Vec2 position, 
		  SDL_Renderer *renderer,
		  Subject* subject);

	/// Destructor
	/// Destroys the object
	~Mummy();

	/// Render
	/// Renders the snake
	/// \offset[in] player offset - offset the mummy so the 
	/// camera appears to follow the player
	void Render(b2Vec2 offset);

	/// Set is dead.
	/// Set whether the mummy is dead or not.
	/// \toggle[in] the value to set to
	void SetIsDead(bool toggle);

	/// Set look.
	/// Set the direction the mummy is facing.
	/// \dir[in] the direction (left or right)
	void SetLook(std::string dir);

	/// Get is dead.
	/// Get whether the mummy is dead.
	/// \return bool is the mummy dead
	bool GetIsDead() const;

	/// Get look.
	/// Get the direction the mummy is facing.
	/// \return string direction (left or right)
	std::string GetLook() const;

	/// Get Body.
	/// Returns the mummy's body.
	/// \return b2Body* of the mummy
	b2Body* GetBody() const;

	/// Get Size.
	/// Returns the mummy's size.
	/// \return b2Vec2 size the mummy
	static b2Vec2 GetSize();

	/// Get Pit Check value.
	/// Returns the Pit Check value for mummy, 
	/// which is used for AI.
	/// \return float deepness.
	static float GetPitCheck();

	/// Inserts new FSM Element.
	/// Inserts FSM Element for Mummy AI handling.
	/// \state1[in] current state
	/// \evnt[in] event (or trigger)
	/// \action[in] action (or responce)
	/// \state2[in] new state
	static void Mummy::PushFSMelement(	std::string state1,
										std::string evnt,
										std::string action,
										std::string state2);
	/// Get Initialized.
	/// Returns mummy's FSM Initialized boolean.
	/// \return bool is FSM Initialized
	static bool GetInit();

	/// Set Initialized.
	/// Set the FSM Initialized.
	/// \par[in] toggle
	static void SetInit(bool);


	/// Update FSM.
	/// Update mummy's FSM.
	/// \evnt[in] current Event
	void FSMUpdate(std::string evnt);

	/// Destroy.
	/// Destroys all entities associated with the mummy.
	void Destroy();

	/// Destroy Body.
	/// Destroys the mummy's box2d body.
	void DestroyBody();

	/// Update particles.
	/// Update the mummy's particles when it is killed.
	/// \deltaTime[in] time since the last update
	void Update(double deltaTime);

	/// Should remove
	/// Should the mummy be removed?
	/// \return bool should remove
	bool ShouldRemove();

	/// Lower health of a mummy.
	/// \v[in] amount to lower by.
	void DecreaseHealth(int v);


	virtual void OnNotify(char* theEvent) {}

private:
	/// AI Finite State Machine.
	static FSM m_fsm;

	/// Map which stores function pointers.
	static std::map<std::string, std::function<void(Mummy&)>> m_actionMap;

	/// Body size.
	static b2Vec2 s_dimensions;

	static float s_speed;
	static float s_attackMultiplier;
	static float s_slowdownMultiplier;
	static float s_minVelXBeforeTurning ;
	static float s_pitCheckValue;

	static bool s_initializedFSM;

	int m_health;


protected:
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	
	SDL_Renderer *m_renderer;

	bool m_isDead;
	std::string m_look;
	std::string m_state;

	void Move();
	void Turn();
	void Attack();
	void Jump();

	bool m_alive;
	std::vector<BlockParticles*> m_blockBits;
	int m_numParticles;
	bool m_isBodyDestroyed;

	Subject* m_subject;
};

