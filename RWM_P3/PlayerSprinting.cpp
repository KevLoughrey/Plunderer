#include <PlayerSprinting.h>


PlayerSprinting::PlayerSprinting()
:	m_counter(0),
	m_curFrame(0)
{

}

PlayerSprinting::~PlayerSprinting()
{

}

PlayerState* PlayerSprinting::HandleInput(Player &player)
{	
	if (KeyboardManager::getKeys()->Key_Left)
	{
		player.SetLook("left");
		player.ExecuteLeftCommand();
	}
	if (KeyboardManager::getKeys()->Key_Right)
	{
		player.SetLook("right");
		player.ExecuteRightCommand();
	}



	if (KeyboardManager::getKeys()->Key_Left)
	{
		if (player.GetOnLadder())
		{
			return new PlayerClimb();
		}

		if(!KeyboardManager::getKeys()->Key_Shift)
		{
			return new PlayerWalk();
		}

	}
	
	if (KeyboardManager::getKeys()->Key_Right)
	{
		if (player.GetOnLadder())
		{
			return new PlayerClimb();
		}

		if(!KeyboardManager::getKeys()->Key_Shift)
		{
			return new PlayerWalk();
		}
	}

	if(	!KeyboardManager::getKeys()->Key_Right  &&
		!KeyboardManager::getKeys()->Key_Left  &&
		!KeyboardManager::getKeys()->Key_Space )
	{
		return new PlayerIdle1();
	}

	if (abs(player.GetVelocity().y) > 0 && KeyboardManager::getKeys()->Key_Space)
	{
		return new PlayerSprintJump();
	}

	if (KeyboardManager::getKeys()->Key_Space)
	{
		player.ExecuteXCommand();
	}

	if(KeyboardManager::getKeys()->Key_S && !m_buttonSPrevPressed)
	{
		if(player.GetBombs() != 0)
		{
			return new PlayerThrowBomb();
		}
		m_buttonSPrevPressed = true;
	}

	else if(!KeyboardManager::getKeys()->Key_S)
	{
		m_buttonSPrevPressed = false;
	}

	if(KeyboardManager::getKeys()->Key_X)
	{
		return new PlayerWhipState();
	}











	return NULL;
}

void PlayerSprinting::Update(Player &player)
{
	m_counter < 2 ? m_counter++ :( m_counter = 0, m_curFrame++ ); 


	if(m_curFrame > CONSTANTS::S_TOTAL_SPRINT_FRAMES-1)
	{
		 m_curFrame = 0 ;
	}

	if(m_curFrame == 4 || m_curFrame == 9 )
	{
		SoundManager::getSoundManager()->PlayGroundStep(rand() % SoundManager::S_TOTAL_GROUND_STEP_SOUNDS);
	}


	player.SetCurrentImage("sprinting", m_curFrame);
}
