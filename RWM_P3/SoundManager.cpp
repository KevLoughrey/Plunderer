#include <SoundManager.h>

SoundManager* SoundManager::m_instance;

SoundManager* SoundManager::getSoundManager()
{
	if(m_instance == NULL)
	{
		Mix_AllocateChannels(99999);
		m_instance = new SoundManager();
	}
	return m_instance;
}

SoundManager::SoundManager() 
{
	 m_clickSound		= Mix_LoadWAV("sounds/Click.wav");
	 m_pickupSound		= Mix_LoadWAV("sounds/Pickup.wav");
	 m_popSound			= Mix_LoadWAV("sounds/Pop.wav");
	 m_explosion		= Mix_LoadWAV("sounds/Explosion.wav");
	 m_fuseBurning		= Mix_LoadWAV("sounds/FuseBurning.wav");
	 m_menuTheme		= Mix_LoadWAV("sounds/menu.wav");
	 m_gameplayTheme	= Mix_LoadWAV("sounds/gameplay.wav");
	 m_dingSound		= Mix_LoadWAV("sounds/achievement.wav");
	 m_scarabSound		= Mix_LoadWAV("sounds/Scarabs.wav");
	 m_scarabMusic		= Mix_LoadWAV("sounds/scarabMusic.wav");
	 m_purchase			= Mix_LoadWAV("sounds/Purchase.wav");
	 m_menuClick		= Mix_LoadWAV("sounds/menuClick.wav");
	 m_doorSlide		= Mix_LoadWAV("sounds/DoorSlide.wav");
	 m_whipCrack		= Mix_LoadWAV("sounds/WhipCrack.wav");
	 m_hitSound			= Mix_LoadWAV("sounds/Hit.wav");
	 m_arrowFire		= Mix_LoadWAV("sounds/arrowFire.wav");
	 
}


SoundManager::~SoundManager()
{
	
}

void SoundManager::PlayScarabSound()
{
	Mix_FadeOutChannel(3, 4000);
	Mix_PlayChannel(-1, m_scarabSound, 0);
	Mix_FadeInChannelTimed(3, m_scarabMusic, -1, 4000, -1);
}

void SoundManager::PlayHit()
{
	Mix_PlayChannel(-1 ,m_hitSound, 0);
}

void SoundManager::PlayPurchase()
{
	Mix_PlayChannel(-1 ,m_purchase, 0);
}

void SoundManager::PlayAchievemnt()
{
	Mix_PlayChannel(-1, m_dingSound, 0);
}

void SoundManager::PlayClick()
{
	Mix_PlayChannel(-1, m_clickSound, 0);
}

void SoundManager::PlayPickup()
{
	Mix_PlayChannel(-1, m_pickupSound, 0);
}

void SoundManager::PlayPop()
{
	Mix_PlayChannel(-1, m_popSound, 0);
}

void SoundManager::PlayExplosion()
{
	Mix_PlayChannel(-1, m_explosion, 0);
}

void SoundManager::PlayFuseSound()
{
	Mix_PlayChannel(-1, m_fuseBurning, 0);
}

void SoundManager::PlayDoorSound()
{
	Mix_PlayChannel(-1, m_doorSlide, 0);
}
	
void SoundManager::PlayMenuTheme()
{
	Mix_PlayChannel(2, m_menuTheme, 10);
}

void SoundManager::PlayMenuClick()
{
	Mix_PlayChannel(-1, m_menuClick, 0);
}

void SoundManager::PlayGameplayTheme()
{
	Mix_PlayChannel( 3, m_gameplayTheme, 50 );
}

void SoundManager::PlayButtonClick()
{
	Mix_PlayChannel( -1, m_buttonClick, 0 );
}

void SoundManager::PlayWhipCrack()
{
	Mix_PlayChannel( -1, m_whipCrack, 0 );
}

void SoundManager::PlaySnakeHiss()
{
	Mix_PlayChannel( -1, m_snakeHiss, 0 );
}

void SoundManager::PlayBatFlapping()
{
	Mix_PlayChannel( -1, m_batFlapping, 0 );
}

void SoundManager::PlayBombExploding()
{
	Mix_PlayChannel( -1, m_bombExploding, 0 );
}

void SoundManager::PlayRopeThudding()
{
	Mix_PlayChannel( -1, m_ropeThudding, 0 );
}

void SoundManager::PlayArrowFire()
{
	Mix_PlayChannel( -1, m_arrowFire, 0 );
}

void SoundManager::PlayEndLevelSound()
{
	Mix_PlayChannel( -1, m_endLevelSound, 0 );
}

void SoundManager::PlayDeathSound()
{
	Mix_PlayChannel( -1, m_deathSound, 0 );
}

void SoundManager::StopMenuAudio()
{
	Mix_Pause(2);
}

void SoundManager::StopGameAudio()
{
	Mix_FreeChunk(m_gameplayTheme);
	m_gameplayTheme	= Mix_LoadWAV("sounds/gameplay.wav");
	Mix_FreeChunk(m_scarabMusic);
	m_scarabMusic	= Mix_LoadWAV("sounds/scarabMusic.wav");
	Mix_FreeChunk(m_doorSlide);
	m_doorSlide		= Mix_LoadWAV("sounds/DoorSlide.wav");
}

void  SoundManager::PlayGroundStep(int index)
{
	//Mix_PlayChannel( -1, m_groundStepSounds[index], 0 );
}