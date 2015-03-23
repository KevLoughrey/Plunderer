#include "MultiMenu.h"


MultiMenu::MultiMenu(SDL_Renderer *renderer, b2World *world) :
	m_renderer(renderer),
	m_buttonTABPrevPressed(false)
{
	m_nameBox = new TextBox (renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.5,CONSTANTS::SCREEN_HEIGHT * 0.2));
	m_friendsBox = new TextBox (renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.5,CONSTANTS::SCREEN_HEIGHT * 0.45));
	m_startButton = new Button(renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.6,CONSTANTS::SCREEN_HEIGHT * 0.75),2,world);
	m_quitButton = new Button(renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.2,CONSTANTS::SCREEN_HEIGHT * 0.75),6,world);
	m_texture = TileBase::getBase()->m_textureMultiMenuBG;
	buttonPressed = false;
	m_currButton = 0;
	m_position.x = 0;
	m_position.y = 0;	
	m_position.w = CONSTANTS::SCREEN_WIDTH;
	m_position.h = CONSTANTS::SCREEN_HEIGHT;
	m_nameBox->setActive(true);
}


MultiMenu::~MultiMenu(void)
{
}
void MultiMenu::Render()
{
	SDL_RenderClear( m_renderer );
	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_position);
	m_startButton->Render();
	m_quitButton->Render();
	m_nameBox->Render();
	m_friendsBox->Render();
	SDL_RenderPresent( m_renderer );
}

void MultiMenu::CheckKeys()
{
	if (m_currButton == 0)
	{
		m_quitButton->ScaleUp();
		m_startButton->ScaleDown();
		if(KeyboardManager::getKeys()->Key_Space)
		{
			m_quitButton->setPressed(true);
		}

		if ((KeyboardManager::getKeys()->Key_Right || KeyboardManager::getKeys()->Key_Left) && buttonPressed == false)
		{
			m_currButton = 1;
			buttonPressed = true;
		}
	}
	else if (m_currButton == 1)
	{
		m_quitButton->ScaleDown();
		m_startButton->ScaleUp();
		if(KeyboardManager::getKeys()->Key_Space)
		{
			m_startButton->setPressed(true);
		}

		if ((KeyboardManager::getKeys()->Key_Right || KeyboardManager::getKeys()->Key_Left) && buttonPressed == false)
		{
			m_currButton = 0;
			buttonPressed = true;
		}
	}

	if (!KeyboardManager::getKeys()->Key_Right && !KeyboardManager::getKeys()->Key_Left && buttonPressed)
	{
		buttonPressed = false;
	}

	if(KeyboardManager::getKeys()-> Key_Tab && !m_buttonTABPrevPressed)
	{ 
		m_buttonTABPrevPressed = true;
		if(m_nameBox->getActive())
		{
			m_friendsBox->setActive(true);
			m_nameBox->setActive(false);
		}

		else
		{
			m_nameBox->setActive(true);
			m_friendsBox->setActive(false);
		}
	}
	else if(!KeyboardManager::getKeys()->Key_Tab)
	{
		m_buttonTABPrevPressed = false;
	}
}

void MultiMenu::update()
{
	m_nameBox->update();
	m_friendsBox->update();
	CheckKeys();
}

bool MultiMenu::checkQuitBtn()
{
	return m_quitButton->Pressed();
}

bool MultiMenu::checkStartButton()
{
	return m_startButton->Pressed();
}
std::string MultiMenu::getMyName()
{
	return m_nameBox->getText();
}
std::string MultiMenu::getFriendsName()
{
	return m_friendsBox->getText();
}