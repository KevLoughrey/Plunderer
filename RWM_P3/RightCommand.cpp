#include <RightCommand.h>

RightCommand::RightCommand(void)
{
}


RightCommand::~RightCommand(void)
{
}

void RightCommand::moveRight(Player* p, 
							 bool modifier) 
{
	execute(p, modifier);
}

void RightCommand::execute(Player* p, 
						   bool modifier) 
{
	modifier == true ? p->SetLinearVelocity(b2Vec2(PLAYERSPRINTSPEED,0)) 
					 : p->SetLinearVelocity(b2Vec2(PLAYERSPEED,0));
}