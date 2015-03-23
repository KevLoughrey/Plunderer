#include "OptionsMenu.h"


OptionsMenu::OptionsMenu(SDL_Renderer *renderer,b2World *world) :
	m_renderer(renderer)
{
	if(TileBase::getBase()->GetPlayer() == "Guy")
	{
		currButton = 0;
	}
	else
	{
		currButton = 1;
	}

	m_texture = TileBase::getBase()->m_textureOptionsMenuBG;
	m_controlTexture = TileBase::getBase()->m_textureControls;

	m_position.x = 0;
	m_position.y = 0;
	m_position.w = CONSTANTS::SCREEN_WIDTH;
	m_position.h = CONSTANTS::SCREEN_HEIGHT;

	m_controlPosition.x = CONSTANTS::SCREEN_WIDTH * 0.35;
	m_controlPosition.y = CONSTANTS::SCREEN_HEIGHT * 0.24;
	m_controlPosition.w = 450;
	m_controlPosition.h = 282;
	
	m_guyBtn = new Button(renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.26,CONSTANTS::SCREEN_HEIGHT * 0.75),4,world);
	m_girlBtn = new Button(renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.56,CONSTANTS::SCREEN_HEIGHT * 0.75),5,world);
}


OptionsMenu::~OptionsMenu(void)
{
}

bool OptionsMenu::checkGuyPressed()
{
	return m_guyBtn->Pressed();
}

bool OptionsMenu::checkGirlPressed()
{
	return m_girlBtn->Pressed();
}

void OptionsMenu::CheckKeys()
{
	if (currButton == 0)
	{
		m_guyBtn->ScaleUp();
		m_girlBtn->ScaleDown();
		if(KeyboardManager::getKeys()->Key_Space)
		{
			m_guyBtn->setPressed(true);
			TileBase::getBase()->SetPlayer("Guy");
		}

		if ((KeyboardManager::getKeys()->Key_Right || KeyboardManager::getKeys()->Key_Left) && buttonPressed == false)
		{
			currButton = 1;
			buttonPressed = true;
		}
	}
	else if (currButton == 1)
	{
		m_guyBtn->ScaleDown();
		m_girlBtn->ScaleUp();
		if(KeyboardManager::getKeys()->Key_Space)
		{
			m_girlBtn->setPressed(true);
			TileBase::getBase()->SetPlayer("Girl");
		}

		if ((KeyboardManager::getKeys()->Key_Right || KeyboardManager::getKeys()->Key_Left) && buttonPressed == false)
		{
			currButton = 0;
			buttonPressed = true;
		}
	}

	if (!KeyboardManager::getKeys()->Key_Right && !KeyboardManager::getKeys()->Key_Left && buttonPressed)
	{
		buttonPressed = false;
	}
}

void OptionsMenu::Render()
{
	CheckKeys();
	SDL_RenderClear( m_renderer );
	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_position);
	SDL_RenderCopy(m_renderer, m_controlTexture, NULL, &m_controlPosition);
	m_guyBtn->Render();
	m_girlBtn->Render();
	SDL_RenderPresent( m_renderer );
}