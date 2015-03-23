#include <PlayerIdle1.h>

PlayerIdle1::PlayerIdle1()
:	m_counter(0),
	m_curFrame(0),
	m_switchIdle(false)
{	
}

PlayerIdle1::~PlayerIdle1()
{

}

PlayerState* PlayerIdle1::HandleInput(Player &player)
{
	if (KeyboardManager::getKeys()->Key_Left
		||KeyboardManager::getKeys()->Key_Right)
	{
		return new PlayerWalk();
	}

	if (KeyboardManager::getKeys()->Key_Space)
	{
		player.ExecuteXCommand();
	}

	if(abs(player.GetVelocity().y) > 0  && !player.GetOnLadder())
	{
		return new PlayerJump();
	}
	
	if(abs(player.GetVelocity().y) > 0 && player.GetOnLadder())
	{
		return new PlayerClimb();
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

	if(m_switchIdle)
	{
		if(player.GetIdleCounter() == 5)
 		{
 			return new PlayerIdle2();
 		}
		else if (player.GetIdleCounter() ==  20)
 		{
 			return new PlayerIdle3();
 		}
		else 
 		{
 			m_switchIdle = false;
 		}
	}

	return NULL;
}

void PlayerIdle1::Update(Player &player)
{
	m_counter < 4 ? m_counter++ :( m_counter = 0, m_curFrame++ );
	if(m_curFrame > CONSTANTS::S_TOTAL_IDLE1_FRAMES - 1)
	{
		 m_curFrame = 0 ;
		 m_switchIdle = true;
	}
	else if(m_curFrame == CONSTANTS::S_TOTAL_IDLE1_FRAMES - 1)
	{
		player.SetIdleCounter(player.GetIdleCounter()+1);
		if(player.GetIdleCounter() >= 30)
		{
			player.SetIdleCounter(0);
		}
	}

	player.SetCurrentImage("idle1", m_curFrame);
}
