#include <JumpCommand.h>

JumpCommand::JumpCommand(void)
{
}


JumpCommand::~JumpCommand(void)
{
}

void JumpCommand::jump(Player* p, 
					   bool modifier) 
{
	execute(p, modifier);
}

void JumpCommand::execute(Player* p, 
						  bool modifier) {
	modifier == true ? p->ApplyForceToCenter(b2Vec2(0,PLAYERSPRINTJUMPFORCE)) 
					 : p->ApplyForceToCenter(b2Vec2(0,PLAYERJUMPFORCE));
}