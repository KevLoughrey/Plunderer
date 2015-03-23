#include <LeftCommand.h>


LeftCommand::LeftCommand()
{
}


LeftCommand::~LeftCommand()
{
}

void LeftCommand::moveRight(Player* p, 
							bool modifier) {
	execute(p, modifier);
}

void LeftCommand::execute(Player* p, 
						  bool modifier) {
	modifier == true ? p->SetLinearVelocity(b2Vec2(-PLAYERSPRINTSPEED,0)) 
					 : p->SetLinearVelocity(b2Vec2(-PLAYERSPEED,0));
}