#include <BatFlyTowardPlayer.h>


BatFlyTowardPlayer::BatFlyTowardPlayer()
:	m_counter(0),
	m_frame(0),
	m_flapAt(10)
{

}

BatFlyTowardPlayer::~BatFlyTowardPlayer()
{

}

BatState* BatFlyTowardPlayer::Update(Bat &bat)
{
	b2Body* player = bat.GetPlayerBody();

	if(!bat.GetSeesPlayer())
	{
		return new BatFlyToCeiling();
	}


	if( m_frame == 1  )
	{
		bat.GetBody()->ApplyForceToCenter(b2Vec2(0,5),true);
	}

	else
	{
		b2Vec2 l_direction = bat.GetBody()->GetPosition() - player->GetPosition();
		l_direction.Normalize();
		l_direction.x *=-5;
		l_direction.y *=-5;

		bat.GetBody()->SetLinearVelocity(l_direction);
	}

	bat.GetBody()->GetPosition().x <= player->GetPosition().x ? bat.SetLook("Right"): bat.SetLook("Left");


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

	

	return NULL;
}


