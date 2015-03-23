// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This is a menu screen for when the player has died this displays the highscore table
//			 and lets you enter your name for the score.


#pragma once

#include <Button.h>
#include <SDL_image.h>
#include <Constants.h>
#include <Button.h>
#include <Box2D\Box2D.h>
#include <TextBox.h>
#include <ServerHelper.h>
class EndingMenu
{
public:
	EndingMenu(SDL_Renderer *renderer,b2World *world, int score,int type);
	~EndingMenu(void);
	void Render();
	void CheckKeys();
	bool CheckQuitButton();
	void SetButtons();

protected:
	
	SDL_Renderer *m_renderer;
	SDL_Texture *m_textureBg;
	SDL_Rect m_position;
	Button *m_quitBtn;
	TextBox *m_textBox;
	ServerHelper server;
	std::string highScoreString;
	std::vector<SDL_Rect> mTextPositions;
	std::vector<SDL_Texture*> mTextImages;
	SDL_Rect m_scorePos;
	SDL_Rect m_errorPos;
	SDL_Texture *m_scoreTexture;
	SDL_Texture *m_errorTexture;
	bool m_errorActive;
	int m_score;
	int m_type;
};

