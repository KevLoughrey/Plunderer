#include "BgBlock.h"

BgBlock::BgBlock(SDL_Renderer* renderer, 
				 b2Vec2 position,
				 int type)
{
	m_position = position;
	m_type = type;
	pos.w = 52;
	pos.h = 50;
	m_renderer = renderer;
}

BgBlock::~BgBlock(void)
{
}

void BgBlock::Render(b2Vec2 offset)
{
	pos.x = m_position.x - offset.x - 25;
	pos.y = m_position.y + offset.y + 25;
	SDL_Texture *temp;

	switch (m_type)
	{
	case 2:
		temp = TileBase::getBase()->m_textureTop;
		break;
	case 3:
		temp = TileBase::getBase()->m_textureLeft;
		break;
	case 4:
		temp = TileBase::getBase()->m_textureRight;
		break;
	case 5:
		temp = TileBase::getBase()->m_textureBottom;
		break;
	case 6:
		temp = TileBase::getBase()->m_textureTopLeft;
		break;
	case 7:
		temp = TileBase::getBase()->m_textureBtmLeft;
		break;
	case 8:
		temp = TileBase::getBase()->m_textureTopRight;
		break;
	case 9:
		temp = TileBase::getBase()->m_textureBtmRight;
		break;
	case 14:
		temp = TileBase::getBase()->m_textureCentre;
		break;
	case 15:
		temp =  TileBase::getBase()->m_textureSquareWindow;
		break;
	case 16:
		temp =  TileBase::getBase()->m_textureRoundWindow;
		break;

		break;
	}
	SDL_RenderCopy(m_renderer,temp,NULL,&pos);
}
