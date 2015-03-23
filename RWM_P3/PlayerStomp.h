#pragma once
#include <PlayerState.h>
class PlayerStomp :
	public PlayerState
{
public:
	PlayerStomp();
	virtual ~PlayerStomp();
	virtual PlayerState* HandleInput(Player &player);
	virtual void Update(Player &player);

private:	
	int m_counter;
	int m_curFrame;
};

