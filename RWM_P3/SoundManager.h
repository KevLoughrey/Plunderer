// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : Loads and plays all the sounds in the game.

#pragma once
#include <SDL_mixer.h>
#include <sstream>
class SoundManager
{
public:
	~SoundManager();

	static SoundManager *m_instance;

	///Sets up the sound manager with more than enough channels for all the sounds possible
	static SoundManager *getSoundManager();
	
	///The theme played on the menu
	void PlayMenuTheme();
	
	///The main gameplay theme
	void PlayGameplayTheme();
	
	///A sound effect played when the player selects something on the menu
	void PlayMenuClick();
	
	///A sound effect played when a player activates a button
	void PlayButtonClick();
	
	///A sound effect played when the player uses their whip
	void PlayWhipCrack();
	
	///An unused sound effect for the snake
	void PlaySnakeHiss();
	
	///An unused sound effect for the bat
	void PlayBatFlapping();
	
	///A sound effect played when a bomb is about to explode
	void PlayBombExploding();
	
	///An unused sound effect for the rope
	void PlayRopeThudding();
	
	///A sound effect played when an arrow is fired
	void PlayArrowFire();
	
	///An unused sound effect for the end of the level
	void PlayEndLevelSound();
	
	///An unused sound effect for the player dying
	void PlayDeathSound();
	
	///A sound effect played when a door is opening or closing
	void PlayDoorSound();

	void PlayFuseSound();
	
	///A sound effect played when a bomb explodes
	void PlayExplosion();
	
	///A sound effect played when an enemy is defeated
	void PlayPop();
	
	///A sound effect played when the player picks up an item
	void PlayPickup();
	
	///A sound effect played when the player selects something
	void PlayClick();
	
	///This method will stop the menu theme from playing, such as when the game begins
	void StopMenuAudio();
	
	///This method will stop the main gameplay theme(s) and other sound effects that might persist into the menu
	void StopGameAudio();
	
	///A sound effect player when the player gets an achievement
	void PlayAchievemnt();

	///Plays the scarab gameplay theme. First fades out the old menu theme before playing the new one
	void PlayScarabSound();
	
	///An unused sound effect
	void PlayPurchase();

	///A generic hit sound effect played when the player sustains damage. The -1 means the sound will always find a new empty channel to play on
	void PlayHit();
	
	///An unused sound effect for the player walking
	/// \param[index] a counter to indicate the type of step in the array.
	void PlayGroundStep(int index);

	///The number of steps before the sound loops
	static const int S_TOTAL_GROUND_STEP_SOUNDS = 5;


protected:
	///Loads all the music we need for the game
	SoundManager();

	///Variables to store all the variou sound effects of the game
	Mix_Chunk *m_dingSound;
	Mix_Chunk *m_clickSound;
	Mix_Chunk *m_menuTheme;
	Mix_Chunk *m_gameplayTheme;
	Mix_Chunk *m_menuClick;
	Mix_Chunk *m_buttonClick;
	Mix_Chunk *m_pickupSound;
	Mix_Chunk *m_fuseBurning;
	Mix_Chunk *m_whipCrack;
	Mix_Chunk *m_snakeHiss;
	Mix_Chunk *m_batFlapping;
	Mix_Chunk *m_bombExploding;
	Mix_Chunk *m_ropeThudding;
	Mix_Chunk *m_arrowFire;
	Mix_Chunk *m_endLevelSound;
	Mix_Chunk *m_deathSound;
	Mix_Chunk *m_doorSlide;
	Mix_Chunk *m_explosion;
	Mix_Chunk *m_popSound;
	Mix_Chunk *m_scarabSound;
	Mix_Chunk *m_scarabMusic;
	Mix_Chunk *m_purchase;
	Mix_Chunk *m_hitSound;

	Mix_Chunk* m_groundStepSounds[S_TOTAL_GROUND_STEP_SOUNDS];

};

