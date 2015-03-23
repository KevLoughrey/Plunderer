#include <PlayerStomp.h>



PlayerStomp::PlayerStomp()
:	m_counter(0),
	m_curFrame(0)
{

}

PlayerStomp::~PlayerStomp()
{

}

PlayerState* PlayerStomp::HandleInput(Player &player)
{
	player.SetGravityScale(1.f -(m_curFrame*.09f) );

	if (KeyboardManager::getKeys()->Key_Left)
	{
		player.SetLook("left");
		player.ExecuteLeftCommand();
	}

	else if (KeyboardManager::getKeys()->Key_Right)
	{
		player.SetLook("right");
		player.ExecuteRightCommand();
	}

	if(m_curFrame == CONSTANTS::S_TOTAL_LANDING_FRAMES - 1)
	{
		player.Bounce();
		player.SetGravityScale(1.f);
		return new PlayerSprintJump();
	}

	return NULL;
}

void PlayerStomp::Update(Player &player)
{
	if(m_curFrame < CONSTANTS::S_TOTAL_LANDING_FRAMES-1)
	{
		 m_counter < 0 ? m_counter++ :( m_counter = 0, m_curFrame++ ); 
	}

	player.SetCurrentImage("landing", m_curFrame);
}
