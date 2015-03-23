#include <BatSleep.h>


BatSleep::~BatSleep()
{

}

BatState* BatSleep::Update(Bat &bat)
{
	b2Body* player = bat.GetPlayerBody();

	if(bat.GetSeesPlayer())
	{
		return new BatFlyTowardPlayer();
	}

	return NULL;
}