#include "HUD.h"

HUD::HUD(SDL_Renderer *renderer, MapManager *mapManager) :
	m_renderer(renderer),
	m_mapManager(mapManager),
	textSurface(NULL),
	textBombs(NULL),
	textJewels(NULL)
{
	m_visible = true;
	m_hourAlive = true;
	m_hourCount = 0;

	int height = 18; 
	m_bgPos.x = 10; 
	m_bgPos.y = 15; 
	m_bgPos.w = 300 / TileBase::getBase()->m_zoomScale;;
	m_bgPos.h = 85 / TileBase::getBase()->m_zoomScale;;

	m_heartPos.x = 25;
	m_heartPos.y = height;
	m_heartPos.w = 70 / TileBase::getBase()->m_zoomScale;;
	m_heartPos.h = 70 / TileBase::getBase()->m_zoomScale;;

	m_livesTextPos.x = 45;
	m_livesTextPos.y = height + 5;
	m_livesTextPos.w = 30 / TileBase::getBase()->m_zoomScale;;
	m_livesTextPos.h = 40 /TileBase::getBase()->m_zoomScale;;

	m_bombsTextPos = m_livesTextPos;
	m_bombsTextPos.x += 100;

	m_jewelTextPos = m_bombsTextPos;
	m_jewelTextPos.x += 100 ;

	m_bombPos.x = 130 ;
	m_bombPos.y = height + (3);
	m_bombPos.w = 65 / TileBase::getBase()->m_zoomScale;;
	m_bombPos.h = 65 / TileBase::getBase()->m_zoomScale;;

	m_pickupPos.x = 225;
	m_pickupPos.y = height + (3);
	m_pickupPos.w = 70 / TileBase::getBase()->m_zoomScale;;
	m_pickupPos.h = 61 / TileBase::getBase()->m_zoomScale;;

	m_hourGlassPos.x = CONSTANTS::SCREEN_WIDTH * 0.92 / TileBase::getBase()->m_zoomScale;
	m_hourGlassPos.y = height;
	m_hourGlassPos.w = 60 / TileBase::getBase()->m_zoomScale;;
	m_hourGlassPos.h = 87 / TileBase::getBase()->m_zoomScale;;

	c = new SDL_Color();
	c->r=255;
	c->g=255;
	c->b=255;
	m_font = TTF_OpenFont( "images/Gothic.ttf", 28 );
	textSurface = TTF_RenderText_Solid( m_font, "5",*c );
	textBombs = TTF_RenderText_Solid( m_font, "5",*c );
	textJewels = TTF_RenderText_Solid( m_font, "0",*c );

	mTextLives = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	mTextBombs = SDL_CreateTextureFromSurface(m_renderer, textBombs);
	mTextJewels = SDL_CreateTextureFromSurface(m_renderer, textJewels);

	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(textBombs);
	SDL_FreeSurface(textJewels);
}

HUD::~HUD(void)
{
}

bool HUD::GetHourALive()
{
	return m_hourAlive;
}

void HUD::SetVisible(bool visible)
{
	m_visible = visible;
}

void HUD::Update()
{
	m_bgPos.x = 10 / TileBase::getBase()->m_zoomScale;  
	m_bgPos.y = 10 / TileBase::getBase()->m_zoomScale; 
	m_bgPos.w = 400 / TileBase::getBase()->m_zoomScale;
	m_bgPos.h = 85 / TileBase::getBase()->m_zoomScale;

	m_heartPos.x = 25 / TileBase::getBase()->m_zoomScale;
	m_heartPos.y = 18 / TileBase::getBase()->m_zoomScale;
	m_heartPos.w = 70 / TileBase::getBase()->m_zoomScale;
	m_heartPos.h = 70 / TileBase::getBase()->m_zoomScale;

	m_livesTextPos.x = 45 / TileBase::getBase()->m_zoomScale;
	m_livesTextPos.y = 23 / TileBase::getBase()->m_zoomScale;
	m_livesTextPos.w = 30 / TileBase::getBase()->m_zoomScale;
	m_livesTextPos.h = 40 /TileBase::getBase()->m_zoomScale;

	m_bombsTextPos = m_livesTextPos;
	m_bombsTextPos.x += 100  / TileBase::getBase()->m_zoomScale;;

	m_jewelTextPos = m_bombsTextPos;
	m_jewelTextPos.x += 100  / TileBase::getBase()->m_zoomScale;;

	m_bombPos.x = 130  / TileBase::getBase()->m_zoomScale;;
	m_bombPos.y = (18+3)  / TileBase::getBase()->m_zoomScale;
	m_bombPos.w = 65 / TileBase::getBase()->m_zoomScale;
	m_bombPos.h = 65 / TileBase::getBase()->m_zoomScale;

	m_pickupPos.x = 225 / TileBase::getBase()->m_zoomScale;;
	m_pickupPos.y = (18 + 3)  / TileBase::getBase()->m_zoomScale;;
	m_pickupPos.w = 70 / TileBase::getBase()->m_zoomScale;;
	m_pickupPos.h = 61 / TileBase::getBase()->m_zoomScale;;

	m_hourGlassPos.x = 338 / TileBase::getBase()->m_zoomScale;
	m_hourGlassPos.y = 25  / TileBase::getBase()->m_zoomScale;
	m_hourGlassPos.w = 40 / TileBase::getBase()->m_zoomScale;
	m_hourGlassPos.h = 55 / TileBase::getBase()->m_zoomScale;
}

void HUD::CountHourglass()
{
	if (!m_hourAlive)
	{
		m_hourCount++;
	}

	if (m_hourAlive == false && m_hourCount == CONSTANTS::HOURGLASS_RESPWAN)
	{
		m_hourAlive = true;
		m_hourCount = 0;
	}
}

void HUD::SetHOurAlive(bool alive)
{
	m_hourAlive = alive;
}

void HUD::Render()
{
	Update();
	CountHourglass();
	std::string lives;
	if (m_mapManager->GetLives() >= 0)
	{
		lives = to_string(m_mapManager->GetLives());
	}
	else
	{
		lives = "0";
	}
	std::string bombs = to_string(m_mapManager->GetBombs());
	std::string jewels = to_string(m_mapManager->GetJewels());

	try 
	{
		textSurface = TTF_RenderText_Solid( m_font, lives.c_str(), *c );
		textBombs = TTF_RenderText_Solid( m_font, bombs.c_str(), *c );
		textJewels = TTF_RenderText_Solid( m_font, jewels.c_str(), *c );

		SDL_DestroyTexture(mTextLives );
		SDL_DestroyTexture(mTextBombs);
		SDL_DestroyTexture(mTextJewels);

		mTextLives = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		mTextBombs = SDL_CreateTextureFromSurface(m_renderer, textBombs);
		mTextJewels = SDL_CreateTextureFromSurface(m_renderer, textJewels);

		SDL_FreeSurface(textSurface);
		SDL_FreeSurface(textBombs);
		SDL_FreeSurface(textJewels);
	}
	catch(int i)
	{
		std::cout << "Text error." << std::endl;
	}

	if (m_visible)
	{
		SDL_RenderCopy(m_renderer,TileBase::getBase()->m_textureHudBg,NULL,&m_bgPos);
		SDL_RenderCopy(m_renderer,TileBase::getBase()->m_textureHudHeart,NULL,&m_heartPos);
		SDL_RenderCopy(m_renderer,TileBase::getBase()->m_textureHudBomb,NULL,&m_bombPos);
		SDL_RenderCopy(m_renderer,TileBase::getBase()->m_textureHudPickup,NULL,&m_pickupPos);

		if (m_hourAlive)
		{
			SDL_RenderCopy(m_renderer,TileBase::getBase()->m_textureHudHourglass,NULL,&m_hourGlassPos);
		}

		SDL_RenderCopy(m_renderer, mTextLives, NULL, &m_livesTextPos);
		SDL_RenderCopy(m_renderer, mTextBombs, NULL, &m_bombsTextPos);
		SDL_RenderCopy(m_renderer, mTextJewels, NULL, &m_jewelTextPos);
	}
}
