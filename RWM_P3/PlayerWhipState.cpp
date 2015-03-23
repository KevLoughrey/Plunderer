#include <PlayerWhipState.h>

PlayerWhipState::PlayerWhipState()
:	m_counter(0),
	m_curFrame(0)
{
	
}


PlayerWhipState::~PlayerWhipState()
{

}

PlayerState* PlayerWhipState::HandleInput(Player &player)
{
	if(	m_curFrame == CONSTANTS::S_TOTAL_WHIP_FRAMES-1)
	{
		return new PlayerIdle1();
	}


	return NULL;
}

void PlayerWhipState::Update(Player &player)
{
	if(m_curFrame < CONSTANTS::S_TOTAL_WHIP_FRAMES - 1)
	{
		 m_counter < 0 ? m_counter++ :( m_counter = 0, m_curFrame+=2 );
	}

	player.SetWhipping(true);

	if(m_curFrame == 16)
	{
		player.UseWhip();
	}
	else if ((m_curFrame == CONSTANTS::S_TOTAL_WHIP_FRAMES - 1))
	{
		player.SetWhipping(false);
	}


	// AUDIO
	//if(m_curFrame == 4 || m_curFrame == 9 )
	//{
		//SoundManager::getSoundManager()->PlayGroundStep(rand() % SoundManager::S_TOTAL_GROUND_STEP_SOUNDS);
	//}

	player.SetCurrentImage("whip", m_curFrame);
}
