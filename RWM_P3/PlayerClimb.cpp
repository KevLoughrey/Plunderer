#include "PlayerClimb.h"


PlayerClimb::PlayerClimb()
:	m_counter(0),
	m_curFrame(0)
{

}

PlayerClimb::~PlayerClimb()
{

}

PlayerState* PlayerClimb::HandleInput(Player &player)
{
	player.SetGravityScale(0);
	if(	KeyboardManager::getKeys()->Key_Space  && 
		!player.GetOnLadder())
	{
		player.SetGravityScale(1);
		return new PlayerJump();
	}

	if (KeyboardManager::getKeys()->Key_Space)
	{
		player.ExecuteXCommand();
	}

	if(		(KeyboardManager::getKeys()->Key_Left || 
			 KeyboardManager::getKeys()->Key_Right) &&
			 !player.GetOnLadder())
	{
		player.SetGravityScale(1);
		return new PlayerWalk();
	}

	if(	player.GetOnGround() &&
		!player.GetOnLadder())
	{
		player.SetGravityScale(1);
		return new PlayerIdle1();
	}

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

	return NULL;
}

void PlayerClimb::Update(Player &player)
{
	if(player.GetMovesUpLadder())
	{
		m_counter < 1 ? m_counter++ :( m_counter = 0, m_curFrame++ ); 

		if(m_curFrame > CONSTANTS::S_TOTAL_CLIMB_LADDER_FRAMES-1)
		{
			 m_curFrame = 0 ;
		}
	}

	else if (player.GetMovesDownLadder())
	{
		m_counter < 1 ? m_counter++ :( m_counter = 0, m_curFrame-- ); 

		if(m_curFrame < 0)
		{
			m_curFrame = CONSTANTS::S_TOTAL_CLIMB_LADDER_FRAMES - 1 ;
		}
	}


	player.SetCurrentImage("climbladder", m_curFrame);
}
