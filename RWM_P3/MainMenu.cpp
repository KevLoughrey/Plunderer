#include <MainMenu.h>

MainMenu::MainMenu(SDL_Renderer* renderer, b2World *world)
{
	m_renderer = renderer;
	m_position.x = 0;
	m_position.y = 0;
	currButton = 0;
	doOnce = false;
	buttonPressed = false;
	m_position.w = CONSTANTS::SCREEN_WIDTH;
	m_position.h = CONSTANTS::SCREEN_HEIGHT;
	m_textureBg = TileBase::getBase()->m_textureMenuBg;
	m_playBtn = new Button(renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.1,CONSTANTS::SCREEN_HEIGHT * 0.75),0,world);
	m_multiBtn = new Button(renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.4,CONSTANTS::SCREEN_HEIGHT * 0.75),2,world);
	m_optionBtn = new Button(renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.7,CONSTANTS::SCREEN_HEIGHT * 0.75),3,world);
}


MainMenu::~MainMenu(void)
{
}



bool MainMenu::CheckMultiButton()
{
	return m_multiBtn->Pressed();
}

bool MainMenu::CheckPlayButton()
{
	return m_playBtn->Pressed();	
}
bool MainMenu::CheckOptionButton()
{
	return m_optionBtn->Pressed();
}

void MainMenu::CheckKeys()
{
	if (KeyboardManager::getKeys()->Key_Right && buttonPressed == false)
	{
		if (currButton == 0)
		{
			m_multiBtn->ScaleUp();
			m_playBtn->ScaleDown();
			m_optionBtn->ScaleDown();
			currButton = 1;
			buttonPressed = true;
		}
		else if (currButton == 1)
		{
			m_optionBtn->ScaleUp();
			m_multiBtn->ScaleDown();
			m_playBtn->ScaleDown();
			currButton = 2;
			buttonPressed = true;
		}
	}
	else if (KeyboardManager::getKeys()->Key_Left && buttonPressed == false)
	 {
		if (currButton == 1)
		{
			m_optionBtn->ScaleDown();
			m_multiBtn->ScaleDown();
			m_playBtn->ScaleUp();
			currButton = 0;
			buttonPressed = true;
		}
		else if (currButton == 2)
		{
			m_optionBtn->ScaleDown();
			m_multiBtn->ScaleUp();
			m_playBtn->ScaleDown();
			currButton = 1;
			buttonPressed = true;
		}
	}
	else if (!KeyboardManager::getKeys()->Key_Right && !KeyboardManager::getKeys()->Key_Left && buttonPressed)
	{
		if (currButton == 0)
		{
			m_playBtn->ScaleUp();
			m_optionBtn->ScaleDown();
			m_multiBtn->ScaleDown();
			buttonPressed = false;
		}
		else if (currButton == 1)
		{
			m_playBtn->ScaleDown();
			m_optionBtn->ScaleDown();
			m_multiBtn->ScaleUp();
			buttonPressed = false;
		}
		else if (currButton == 2)
		{
			m_multiBtn->ScaleDown();
			m_optionBtn->ScaleUp();
			m_playBtn->ScaleDown();
			buttonPressed = false;
		}
	}


	if (KeyboardManager::getKeys()->Key_Space)
	{
		if (currButton == 0)
		{
			m_playBtn->setPressed(true);
		}
		else if (currButton == 1)
		{
			m_multiBtn->setPressed(true);
		}
		else if (currButton == 2)
		{
			m_optionBtn->setPressed(true);
		}
	}
}


void MainMenu::SetButtons()
{
	m_multiBtn->setPressed(false);
	m_playBtn->setPressed(false);
	m_optionBtn->setPressed(false);
}

void MainMenu::Render()
{
	CheckKeys();
	SDL_RenderSetScale(m_renderer,1,1);
	SDL_RenderClear( m_renderer );
	SDL_RenderCopy(m_renderer, m_textureBg, NULL, &m_position);
	m_playBtn->Render();
	m_multiBtn->Render();
	m_optionBtn->Render();
	SDL_RenderPresent( m_renderer );

	if (doOnce == false)
	{
		SoundManager::getSoundManager()->PlayMenuTheme();
		doOnce = true;
	}
}
