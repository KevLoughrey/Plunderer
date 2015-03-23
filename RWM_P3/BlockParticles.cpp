#include <BlockParticles.h>

BlockParticles::BlockParticles(b2Vec2 pos, 
							   SDL_Renderer *renderer,
							   int type) 
	: m_pos(pos), 
	m_size(b2Vec2(7, 7)), 
	m_renderer(renderer),
	m_alive(true), 
	m_secondsToLive(3),
	m_gravityScale(100),
	m_gravity(-9.81),
	m_type(type)
{
	if (type == 1)
	{
		m_timeToLive = 3 * ( (float)rand() / RAND_MAX );
	}
	else if (type == 2 || type == 3 || type == 4)
	{
		m_timeToLive = 1 * ( (float)rand() / RAND_MAX );
	}

	m_pos.x *= METRESTOPIXELS;
	m_pos.y *= METRESTOPIXELS;

	float randomX = rand() % 100 -50;//-3 + 4 * ( (float)rand() / RAND_MAX );
	float randomY;
	if (type == 1)
	{
		randomY = rand() % 100 + 200 ;
	}
	else if (type == 2 || type == 3 || type == 4)
	{
		randomY = rand() % 100 + 100 ;
	}
	randomY *= -1;

	b2Vec2 randomVelocity(randomX, randomY);
	randomVelocity *= -2.5f;

	m_velocity = randomVelocity;
}


BlockParticles::~BlockParticles()
{
}

void BlockParticles::Update(double deltatime) 
{
	m_timeToLive -= deltatime;
	m_velocity +=  b2Vec2(0,m_gravity*deltatime*m_gravityScale);
	m_pos += b2Vec2(m_velocity.x*deltatime,m_velocity.y*deltatime) ;
}

bool BlockParticles::isAlive()
{
	return m_timeToLive > 0;
}

void BlockParticles::Destroy()
{
}

void BlockParticles::Draw(b2Vec2 offset)
{
	if (m_timeToLive > 0)
	{ 
		SDL_Rect stretchRect;
		stretchRect.x = m_pos.x - offset.x;
		stretchRect.y =  -m_pos.y + offset.y;
		stretchRect.w = m_size.x;
		stretchRect.h = m_size.y;
		if (m_type == 1)
		{
			SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_textureBlockBit, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
		}
		else if (m_type == 2)
		{
			SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_textureBloodParticle, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
		}
		else if (m_type == 3)
		{
			SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_textureBatParticle, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
		}
		else if (m_type == 4)
		{
			SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_textureMummyParticle, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
		}
		
	}
}