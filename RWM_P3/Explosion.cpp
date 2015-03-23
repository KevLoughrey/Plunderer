#include "Explosion.h"


Explosion::Explosion(SDL_Renderer *renderer,
					 b2Vec2 position)
{
	m_renderer = renderer;
	m_position = position;
	pos.w = 396;
	pos.h = 346;
	m_frame = 0;
	m_count = 0;
	m_alive = false;
	m_finished = false;
}


Explosion::~Explosion(void)
{
}

bool Explosion::getFinished()
{
	return m_finished;
}

void Explosion::setAlive(bool alive)
{
	m_alive = alive;
}

void Explosion::Render(b2Vec2 offset)
{
	SDL_Rect stretchRect;
	stretchRect.x = ((m_position.x * METRESTOPIXELS)  - (pos.w/2) - offset.x) + 25;
	stretchRect.y = (-(m_position.y * METRESTOPIXELS)  - (pos.h/2) + offset.y) - 25;
	stretchRect.w = pos.w;
	stretchRect.h = pos.h; 

	if (m_alive)
	{
		SDL_RenderCopyEx ( m_renderer, TileBase::getBase()->m_explosionVector.at(m_frame), NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );

		if (m_frame != 10)
		{
			m_frame++;
		}
		else
		{
			m_finished = true;
		}
	}
}
