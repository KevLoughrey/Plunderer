#include "Achievement.h"


Achievement::Achievement(char* name, 
						 SDL_Renderer* renderer)
	: m_name(name),
	m_renderer(renderer),
	m_isUnlocked(false),
	m_count(0),
	m_alive(true)
{
	m_position.x = CONSTANTS::SCREEN_WIDTH;
	m_position.y = -100;
	m_position.w = 200;
	m_position.h = 100;
	std::string s;
	s.append("images/achievements/");
	s.append(m_name);
	s.append(".png");
	m_texture = SDL_CreateTextureFromSurface(renderer, IMG_Load(s.c_str()));
}


Achievement::~Achievement()
{

}

void Achievement::Render()
{
	float speed = 1;
	if (m_isUnlocked)
	{
		m_count++;
	}

	if (m_count == 101)
	{
		SoundManager::getSoundManager()->PlayAchievemnt();
	}
	if (m_count <= 100)
	{
		m_position.y += speed * (1/TileBase::getBase()->m_zoomScale);
	}
	else if (m_count >= 300 && m_count <= 400)
	{
		m_position.y -= speed * (1/TileBase::getBase()->m_zoomScale);
	}
	else if (m_count > 400)
	{
		m_alive = false;
	}

	m_position.x = (CONSTANTS::SCREEN_WIDTH * 0.75) / TileBase::getBase()->m_zoomScale;
	m_position.w = 300 / TileBase::getBase()->m_zoomScale;
	m_position.h = 100 / TileBase::getBase()->m_zoomScale;

	SDL_RenderCopy( m_renderer, m_texture, NULL, &m_position);

}

char* Achievement::GetName()
{
	return m_name;
}

void Achievement::Unlock()
{
	m_isUnlocked = true;
	std::cout << m_name << std::endl;
}

bool Achievement::GetIsAlive()
{
	return m_alive;
}

bool Achievement::GetIsUnlocked()
{
	return m_isUnlocked;
}