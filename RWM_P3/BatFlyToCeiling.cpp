#include "BatFlyToCeiling.h"


BatFlyToCeiling::BatFlyToCeiling()
:	m_counter(0),
	m_frame(0),
	m_flapAt(10)
{

}

BatFlyToCeiling::~BatFlyToCeiling()
{

}

BatState* BatFlyToCeiling::Update(Bat &bat)
{
	b2Body* player = bat.GetPlayerBody();

	if(bat.GetSeesPlayer())
	{
		return new BatFlyTowardPlayer();
	}


	if(bat.GetOnCeiling())
	{
		return new BatSleep();
	}


	if( m_counter < m_flapAt)
	{
		m_counter++;
	}
	else
	{
		m_counter = 0; 
		m_frame = abs(m_frame -1 ); 
		bat.SetTexture(TileBase::getBase()->m_batVector.at(m_frame));
	}

	if( m_frame == 1  )
	{
		bat.GetBody()->ApplyForceToCenter(b2Vec2(-bat.GetBody()->GetLinearVelocity().x * 12,-300),true);
	}

	return NULL;
}