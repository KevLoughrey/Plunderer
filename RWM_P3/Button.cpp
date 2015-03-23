#include <Button.h>


Button::Button(SDL_Renderer *renderer, 
			   b2Vec2 position,
			   int type,
			   b2World *world)
	: m_renderer(renderer)
{
	m_world = world;
	m_type = type;
	m_pressed = false;

	if(type == 0)
	{
		m_texture = TileBase::getBase()->m_textureStartBtn;
		m_position.w = 307;
		m_position.h = 175;
	}
	else if (m_type == 2)
	{
		m_texture = TileBase::getBase()->m_textureMultiBtn;
		m_position.w = 297;
		m_position.h = 193;
	}
	else if (m_type == 3)
	{
		m_texture = TileBase::getBase()->m_textureCuttingRoom;
		m_position.w = 277;
		m_position.h = 145;
	}
	else if (m_type == 4)
	{
		m_texture = TileBase::getBase()->m_textureGuyBtn;
		m_position.w = 277;
		m_position.h = 145;
	}
	else if (m_type == 5)
	{
		m_texture = TileBase::getBase()->m_textureGirlBtn;
		m_position.w = 277;
		m_position.h = 145;
	}
	else if (m_type == 6)
	{
		m_texture = TileBase::getBase()->m_textureBoxOffice;
		m_position.w = 277;
		m_position.h = 145;
	}

	m_position.x = position.x;
	m_position.y = position.y;
	
}

Button::~Button()
{
}



void Button::setPressed(bool pressed)
{
	SoundManager::getSoundManager()->PlayMenuClick();
	m_pressed = pressed;
}

void Button::ScaleUp()
{
	
	if (m_type == 2)
	{
		m_position.w = 327;
		m_position.h = 223;
	}
	else
	{
		m_position.w = 307;
		m_position.h = 175;
	}
}

void Button::ScaleDown()
{
	if (m_type == 2)
	{
		m_position.w = 297;
		m_position.h = 193;
	}
	else
	{
		m_position.w = 277;
		m_position.h = 145;
	}
}

bool Button::Pressed()
{
	return m_pressed;
}

void Button::Render()
{
	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_position);
}
