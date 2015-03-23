#include <RayCastListener.h>

RayCastListener::RayCastListener() 
	: intersectedObject(false)
{
}

RayCastListener::~RayCastListener()
{
}

float32 RayCastListener::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	if (fixture->GetUserData() == "mummy")
	{
		static_cast<Mummy*>(fixture->GetBody()->GetUserData())->SetIsDead(true);
	}
	else if (fixture->GetUserData() == "snake")
	{
		static_cast<Snake*>(fixture->GetBody()->GetUserData())->SetIsDead(true);
	}
	else if (fixture->GetUserData() == "bat")
	{
		static_cast<Bat*>(fixture->GetBody()->GetUserData())->SetIsDead(true);
	}
	intersectedObject = true;
	return 0.0f;
}

bool RayCastListener::ObjectIntersected()
{
	return intersectedObject;
}