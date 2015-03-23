#include <PlayerIdle3.h>


PlayerIdle3::PlayerIdle3()
:	m_counter(0),
	m_curFrame(0),
	m_switchIdle(false)
{	
}

PlayerIdle3::~PlayerIdle3()
{

}

PlayerState* PlayerIdle3::HandleInput(Player &player)
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

	if(!player.GetOnGround() && !player.GetOnLadder())
	{
		return new PlayerJump();
	}
	
	if(!player.GetOnGround() && player.GetOnLadder())
	{
		return new PlayerClimb();
	}

	if(KeyboardManager::getKeys()->Key_S)
	{
		if(player.GetBombs() != 0)
		{
			return new PlayerThrowBomb();
		}
	}

	if(KeyboardManager::getKeys()->Key_X)
	{
		return new PlayerWhipState();
	}

	if(m_switchIdle)
	{
		return new PlayerIdle1();
	}

	return NULL;

}

void PlayerIdle3::Update(Player &player)
{
	m_counter < 2 ? m_counter++ :( m_counter = 0, m_curFrame++ );
	if(m_curFrame > CONSTANTS::S_TOTAL_IDLE3_FRAMES-1)
	{
		m_curFrame = 0 ;
		m_switchIdle = true;
	}

	player.SetCurrentImage("idle3", m_curFrame);
}
