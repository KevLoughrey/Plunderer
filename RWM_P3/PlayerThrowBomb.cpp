#include <PlayerThrowBomb.h>


PlayerThrowBomb::PlayerThrowBomb()
:	m_counter(0),
	m_curFrame(0),
	m_bombPlanted(false)
{

}

PlayerThrowBomb::~PlayerThrowBomb()
{

}

PlayerState* PlayerThrowBomb::HandleInput(Player &player)
{
	if(m_curFrame == CONSTANTS::S_TOTAL_BOMB_FRAMES -1)
	{
		return new PlayerIdle1();
	}


	return NULL;
}

void PlayerThrowBomb::Update(Player &player)
{
	if ( player.CanThrowBomb())
	{
		if (m_curFrame == 3 &&
			!m_bombPlanted)
		{
			player.DecreaseNumBombs();
			player.DropBomb();
			m_bombPlanted = true;
		}

		m_counter < 1 ? m_counter++ :( m_counter = 0, m_curFrame++ ); 

		player.SetCurrentImage("throwbomb", m_curFrame);
	}
}
