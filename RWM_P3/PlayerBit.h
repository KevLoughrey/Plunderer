#pragma once
#include "playerstate.h"
class PlayerBit :
	public PlayerState
{
public:
	PlayerBit();
	virtual ~PlayerBit();
	virtual PlayerState* HandleInput(Player &player);
	virtual void Update(Player &player);

private:	
	int m_counter;
	int m_curFrame;
};

