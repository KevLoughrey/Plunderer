#include <PlayerIdle2.h>

PlayerIdle2::PlayerIdle2()
:	m_counter(0),
	m_curFrame(0),
	m_switchIdle(false)
{

}

PlayerIdle2::~PlayerIdle2()
{

}

PlayerState* PlayerIdle2::HandleInput(Player &player)
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

void PlayerIdle2::Update(Player &player)
{
	m_counter < 2 ? m_counter++ :( m_counter = 0, m_curFrame++ );
	if(m_curFrame > CONSTANTS::S_TOTAL_IDLE2_FRAMES-1)
	{
		m_curFrame = 0 ;
		m_switchIdle = true;
	}

	player.SetCurrentImage("idle2", m_curFrame);
}
