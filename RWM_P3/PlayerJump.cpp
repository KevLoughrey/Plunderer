#include <PlayerJump.h>


PlayerJump::PlayerJump()
:	m_counter(0),
	m_curFrame(0)
{

}

PlayerJump::~PlayerJump()
{

}

PlayerState* PlayerJump::HandleInput(Player &player)
{
	if(!player.GetOnGround())
	{

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

		else
		{
			player.SetLinearVelocity(b2Vec2(0, player.GetVelocity().y));
		}

	}

	if(abs(player.GetVelocity().y) == 0&&
		!player.GetOnLadder())
	{
		return new PlayerIdle1();
	}


	if(player.GetOnLadder())
	{
		return new PlayerClimb();
	}


	return NULL;
}

void PlayerJump::Update(Player &player)
{
	if(m_curFrame < CONSTANTS::S_TOTAL_JUMP_FRAMES-1)
	{
		 m_counter < 1 ? m_counter++ :( m_counter = 0, m_curFrame++ ); 
	}

	player.SetCurrentImage("jumping", m_curFrame);
}
