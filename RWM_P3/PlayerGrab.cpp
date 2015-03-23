#include "PlayerGrab.h"


PlayerGrab::PlayerGrab()
:	m_counter(0),
	m_curFrame(0)
{

}

PlayerGrab::~PlayerGrab()
{

}

PlayerState* PlayerGrab::HandleInput(Player &player)
{
	if(m_curFrame == CONSTANTS::S_TOTAL_LOOT_GRAB_FRAMES - 1)
	{
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

	if (KeyboardManager::getKeys()->Key_Space)
	{
		player.ExecuteXCommand();
	}

	return NULL;
}

void PlayerGrab::Update(Player &player)
{
	if(m_curFrame < CONSTANTS::S_TOTAL_LOOT_GRAB_FRAMES-1)
	{
		 m_counter < 0 ? m_counter++ :( m_counter = 0, m_curFrame++ ); 
	}

	player.SetCurrentImage("loot", m_curFrame);
}
