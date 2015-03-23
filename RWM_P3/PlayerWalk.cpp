#include <PlayerWalk.h>


PlayerWalk::PlayerWalk()
:	m_counter(0),
	m_curFrame(0)
{	
}


PlayerWalk::~PlayerWalk()
{

}

PlayerState* PlayerWalk::HandleInput(Player &player)
{

	if (KeyboardManager::getKeys()->Key_Left)
	{
		player.SetLook("left");
	}
	if (KeyboardManager::getKeys()->Key_Right)
	{
		player.SetLook("right");
	}

	if (KeyboardManager::getKeys()->Key_Space)
	{
		player.ExecuteXCommand();
	}

	if (KeyboardManager::getKeys()->Key_Left)
	{
		player.ExecuteLeftCommand();

		if (player.GetOnLadder())
		{
			return new PlayerClimb();
		}

		if(KeyboardManager::getKeys()->Key_Shift)
		{
			return new PlayerSprinting();
		}

	}

	if (KeyboardManager::getKeys()->Key_Right)
	{
		player.ExecuteRightCommand();
		if (player.GetOnLadder())
		{
			return new PlayerClimb();
		}

		if(KeyboardManager::getKeys()->Key_Shift)
		{
			return new PlayerSprinting();
		}
	}

	if (abs(player.GetVelocity().y) > 0 && KeyboardManager::getKeys()->Key_Space )
	{
		return new PlayerJump();
	}

	if(	!KeyboardManager::getKeys()->Key_Right  &&
		!KeyboardManager::getKeys()->Key_Left  &&
		!KeyboardManager::getKeys()->Key_Space)
	{
		return new PlayerIdle1();
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

void PlayerWalk::Update(Player &player)
{
	m_counter < 3 ? m_counter++ :( m_counter = 0, m_curFrame++ ); 

	if(m_curFrame > CONSTANTS::S_TOTAL_RUN_FRAMES-1)
	{
		 m_curFrame = 0 ;
	}

	if(m_curFrame == 4 || m_curFrame == 9 )
	{
		SoundManager::getSoundManager()->PlayGroundStep(rand() % SoundManager::S_TOTAL_GROUND_STEP_SOUNDS);
	}





	player.SetCurrentImage("running", m_curFrame);
}
