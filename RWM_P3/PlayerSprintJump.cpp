#include <PlayerSprintJump.h>


PlayerSprintJump::PlayerSprintJump()
:	m_counter(0),
	m_curFrame(0)
{

}

PlayerSprintJump::~PlayerSprintJump()
{

}

PlayerState* PlayerSprintJump::HandleInput(Player &player)
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

		if(abs(player.GetVelocity().x) < 0.0001) 
		{
			return new PlayerJump();
		}
	}



	else if(abs(player.GetVelocity().y) == 0 &&
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

void PlayerSprintJump::Update(Player &player)
{
	if(m_curFrame < CONSTANTS::S_TOTAL_SPRINT_JUMP_FRAMES-1)
	{
		 m_counter < 1 ? m_counter++ :( m_counter = 0, m_curFrame++ ); 
	}

	player.SetCurrentImage("sprintjumping", m_curFrame);
}
