// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : BAT ENEMY  

#pragma once
#include <Box2D\Box2D.h>

#include <BaseObject.h>
#include <SoundManager.h>
#include <TileBase.h>
#include <BlockParticles.h>
#include <Subject.h>

#include <BatState.h>
#include <BatFlyTowardPlayer.h>
#include <BatFlyToCeiling.h>
#include <BatSleep.h>

///  Bat Enemy.
///  Contains all logic and get/set methods
///  for the bat.
class Bat 
:	public BaseObject, 
	public Observer
{

private:

	/// Stores standard size.
	static b2Vec2 s_dimensions;

	/// Stores speed.
	static float s_speed;

	/// Tells by how much to slow down.
	static float s_slowdownMultiplier;

	/// Velocity value after which bat can turn. 
	static float s_minVelXBeforeTurning ;

	/// Used to initialize a bat.
	bool m_initStickToCeiling;

	/// Check is bat on ceiling.
	bool m_isOnCeiling;

	/// B2Sensor Detection bool.
	bool m_playerIsWithinRadius;	

	/// Raycast Detection bool.
	bool m_batSeesPlayer;		

	/// Stores pointer to the player.
	/// Used to follow player.
	b2Body* m_playerBody;

public:
	Bat(b2World *world, 
		b2Vec2 position, 
		SDL_Renderer *renderer,
		Subject* subject);
	~Bat();
	
	/// Draws Bat.
	/// \param[in] Camera Offset
	void Render(b2Vec2 offset);

	/// Toggles Bat's alive.
	/// \param[in] On/Off
	void SetIsDead(bool toggle);

	/// Toggles Bat's Look direction.
	/// \param[in] "Left" or "Right"
	void SetLook(std::string dir);

	
	/// Gets Bat's Live.
	/// \returns alive or not
	bool GetIsDead() const;

	/// Gets Bat's Look direction.
	/// \returns "Left" or "Right"
	std::string GetLook() const;

	/// Gets Bat's Body.
	/// \returns its b2Body
	b2Body* GetBody() const;

	/// Gets Bat's Size.
	/// \returns its size as b2Vec2
	static b2Vec2 GetSize();

	/// Updates Bat.
	/// \param[in] is player seen by raycast
	void Update(bool playerDetected);

	/// Gets is Bat on Ceiling.
	/// \returns true or false
	bool GetOnCeiling() const;

	/// Sets is Bat on Ceiling.
	/// \param[in] true or false
	void SetOnCeiling(bool v); 

	///  Fly action.
	void FlyForward();

	/// Turn action
	void Turn();

	void Destroy();
	void DestroyBody();

	/// Will update particles once bat is killed (pardon for a wierd name)
	/// \param[in] time delta
	void Update(double deltaTime);

	/// Method tells if Bat can be removed.
	/// \returns true or false
	bool ShouldRemove();

	/// Get/Set for "m_playerIsWithinRadius".
	bool GetPlayerIsClose() const;
	void SetPlayerIsClose(bool v); 

	/// Get/Set for Player Body.
	b2Body* GetPlayerBody() const;
	void SetPlayerBody(b2Body* v); 

	/// Sets Bat Texture.
	/// \param[in] pointer to texture
	void SetTexture(SDL_Texture*);

	bool GetSeesPlayer() const;
	virtual void OnNotify(char* theEvent) {}

protected:
	b2Body *m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	
	b2PolygonShape m_ceilingSensorShape;
	b2FixtureDef m_ceilingSensorDef;

	b2PolygonShape m_playerSensorShape;
	b2FixtureDef m_playerSensorDef;

	SDL_Renderer *m_renderer;

	bool m_isDead;
	std::string m_look;

	bool m_alive;
	std::vector<BlockParticles*> m_blockBits;
	int m_numParticles;
	bool m_isBodyDestroyed;

	BatState *m_state;
	Subject *m_subject;
};