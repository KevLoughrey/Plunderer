#include "EndingMenu.h"


EndingMenu::EndingMenu(SDL_Renderer *renderer,b2World *world, int myScore,int type)
	: m_score(myScore)
{
	SoundManager::getSoundManager()->StopGameAudio();
	SoundManager::getSoundManager()->PlayMenuTheme();
	m_renderer = renderer;
	m_errorActive = false;
	m_type = type;

	m_position.x = 0;
	m_position.y = 0;
	m_position.w = CONSTANTS::SCREEN_WIDTH;
	m_position.h = CONSTANTS::SCREEN_HEIGHT;
	if (type == 1 )
	{
		m_quitBtn = new Button(renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.6,CONSTANTS::SCREEN_HEIGHT * 0.79),6,world);
	}
	else
	{
		m_quitBtn = new Button(renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.45,CONSTANTS::SCREEN_HEIGHT * 0.79),6,world);
	}
	if (type == 1)
	{
		m_textBox = new TextBox(renderer,b2Vec2(CONSTANTS::SCREEN_WIDTH * 0.3,CONSTANTS::SCREEN_HEIGHT * 0.82));
		m_textBox->setActive(true);
	}
	server = ServerHelper();
	if (type == 1)
	{
		highScoreString = server.GetHighScores();
	}
	else 
	{
		highScoreString = server.GetCoopHighScores();
	}
	
	std::stringstream test(highScoreString);
	std::string segment;
	
	SDL_Color* c = new SDL_Color();
	c->r=255;
	c->g=255;
	c->b=255;
	int xPos = CONSTANTS::SCREEN_WIDTH * 0.42;
	int yPos = CONSTANTS::SCREEN_HEIGHT * 0.2;

	std::string s = std::to_string(m_score);
	SDL_Surface* textSurface = TTF_RenderText_Solid( TTF_OpenFont( "Fonts/Nathan.ttf", 42 ), s.c_str(),*c );
	m_scoreTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	m_scorePos.x = CONSTANTS::SCREEN_WIDTH * 0.52;
	m_scorePos.y =  CONSTANTS::SCREEN_HEIGHT * 0.715;
	m_scorePos.w = textSurface->w;
	m_scorePos.h = textSurface->h;

	SDL_Color* col = new SDL_Color();
	col->r=236;
	col->g=62;
	col->b=62;

	std::string error = "Error Please Enter Your Name";
	SDL_Surface *textSurfaceError = TTF_RenderText_Solid( TTF_OpenFont( "Fonts/Nathan.ttf", 54 ), error.c_str(),*col );
	m_errorTexture = SDL_CreateTextureFromSurface(m_renderer, textSurfaceError);
	m_errorPos.x = CONSTANTS::SCREEN_WIDTH * 0.35;
	m_errorPos.y = CONSTANTS::SCREEN_HEIGHT * 0.55;
	m_errorPos.w = textSurfaceError->w;
	m_errorPos.h = textSurfaceError->h;


	while(std::getline(test, segment, '&'))
	{		
		if(segment != " "){
			string buf; // Have a buffer string
			stringstream ss(segment); // Insert the string into a stream
			vector<string> tokens; // Create vector to hold our words
			while (ss >> buf)
			{
				tokens.push_back(buf);
			}
		
			SDL_Surface* textSurface = TTF_RenderText_Solid( TTF_OpenFont( "Fonts/Nathan.ttf", 42 ), tokens.at(0).c_str(),*c );
			mTextImages.push_back(SDL_CreateTextureFromSurface(m_renderer, textSurface));
		
			SDL_Rect renderQuad = { xPos, yPos,textSurface->w, textSurface->h};
			mTextPositions.push_back(renderQuad);
		
			SDL_FreeSurface(textSurface);
			if (m_type == 1)
			{
				textSurface = TTF_RenderText_Solid( TTF_OpenFont( "Fonts/Nathan.ttf", 42 ), tokens.at(1).c_str(),*c );
				mTextImages.push_back(SDL_CreateTextureFromSurface(m_renderer, textSurface));
		
				SDL_Rect renderQuad2 = { xPos + 300, yPos,textSurface->w, textSurface->h};		
				mTextPositions.push_back(renderQuad2);
			}
			else
			{
				textSurface = TTF_RenderText_Solid( TTF_OpenFont( "Fonts/Nathan.ttf", 42 ), tokens.at(1).c_str(),*c );
				mTextImages.push_back(SDL_CreateTextureFromSurface(m_renderer, textSurface));
		
				SDL_Rect renderQuad2 = { xPos + 100, yPos,textSurface->w, textSurface->h};		
				mTextPositions.push_back(renderQuad2);

				SDL_FreeSurface(textSurface);

				textSurface = TTF_RenderText_Solid( TTF_OpenFont( "Fonts/Nathan.ttf", 42 ), tokens.at(2).c_str(),*c );
				mTextImages.push_back(SDL_CreateTextureFromSurface(m_renderer, textSurface));
		
				SDL_Rect renderQuad3 = { xPos + 200, yPos,textSurface->w, textSurface->h};		
				mTextPositions.push_back(renderQuad3);
			}

			yPos += 50;

			SDL_FreeSurface(textSurface);
		}
	}

}


EndingMenu::~EndingMenu(void)
{
}

bool EndingMenu::CheckQuitButton()
{
	return m_quitBtn->Pressed();
}

void EndingMenu::SetButtons()
{
	m_quitBtn->setPressed(false);
}

void EndingMenu::CheckKeys()
{
	if (KeyboardManager::getKeys()->Key_Space)
	{
		if (m_type == 1)
		{
			if(m_textBox->getText().size() > 3)
			{
				m_quitBtn->setPressed(true);
				std::string text = m_textBox->getText();			
				server.PostHighScore(m_score,text);
			}
			else
			{
				m_errorActive = true;
			}
		}
		else
		{
			m_quitBtn->setPressed(true);
		}
		
	}
	if (m_type ==1)
	{
		m_textBox->update();
	}
}

void EndingMenu::Render()
{
	CheckKeys();
	SDL_RenderClear( m_renderer );
	SDL_RenderSetScale(m_renderer,1,1);
	SDL_RenderCopy(m_renderer,TileBase::getBase()->m_textureGameOver, NULL, &m_position);
	m_quitBtn->Render();
	if (m_type == 1)
	{
		m_textBox->Render();
	}

	for(int i =0; i < mTextImages.size(); ++i)
	{
		SDL_RenderCopy(m_renderer,mTextImages.at(i),NULL,&mTextPositions.at(i));
	}

	SDL_RenderCopy(m_renderer,m_scoreTexture,NULL,&m_scorePos);

	if (m_errorActive)
	{
		SDL_RenderCopy(m_renderer,m_errorTexture,NULL,&m_errorPos);
	}
	
	SDL_RenderPresent( m_renderer );
}