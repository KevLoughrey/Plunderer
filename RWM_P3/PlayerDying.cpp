#include <PlayerDying.h>


PlayerDying::PlayerDying()
:	m_counter(0),
	m_curFrame(0)
{

}

PlayerDying::~PlayerDying()
{

}

PlayerState* PlayerDying::HandleInput(Player &player)
{
	if(m_curFrame == CONSTANTS::S_TOTAL_DEATH_FRAMES - 1 
		&&m_counter == 50)
	{
		player.SetAlive(false);
	}
	return NULL;
}

void PlayerDying::Update(Player &player)
{
	if(m_curFrame < CONSTANTS::S_TOTAL_DEATH_FRAMES-1)
	{
 		 m_counter < 3 ? m_counter++ :( m_counter = 0, m_curFrame++ ); 
	}
	else
	{
		m_counter++;
	}

	player.SetCurrentImage("dying", m_curFrame);
}
