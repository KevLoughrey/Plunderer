#include "Torch.h"


Torch::Torch(SDL_Renderer *renderer,b2Vec2 position)
{
	m_renderer = renderer;
	m_position = position;
	pos.w = 80;
	pos.h = 49;
	m_frame = 0;
	m_count = 0;
}

Torch::~Torch(void)
{
}

void Torch::Render(b2Vec2 offset)
{

	if (m_count % 10 == 0)
	{
		m_frame++;
	}
	
	m_count++;

	if(m_frame == 4)
	{
		m_frame = 0;
	}

	pos.x = m_position.x - offset.x - 25;
	pos.y = m_position.y + offset.y + 25;
	SDL_RenderCopy(m_renderer,TileBase::getBase()->m_torchVector.at(m_frame),NULL,&pos);
}