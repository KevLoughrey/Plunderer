// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : Acts like a standard text box, allows the user to type information
#pragma once
#include <SDL_image.h>
#include <Constants.h>
#include <Box2D\Box2D.h>
#include <KeyboardManager.h>
#include <SDL_ttf.h>
#include <string>
#include <TileBase.h>
class TextBox
{
public:
	TextBox(SDL_Renderer *renderer, b2Vec2 position);
	~TextBox(void);
	void Render();
	void update();
	bool getActive();
	void setActive(bool);
	
	void appendInputToString();
	std::string getText();
protected:
	SDL_Renderer *m_renderer;
	SDL_Texture *m_inactiveTexture;
	SDL_Texture *m_activeTexture;
	SDL_Rect m_position;	
	SDL_Texture* mTextImage;
	std::string m_text;
	bool active;
	int textWidth;
	TTF_Font *gFont;

	bool m_buttonAPrevPressed;
	bool m_buttonBPrevPressed;
	bool m_buttonCPrevPressed;
	bool m_buttonDPrevPressed;
	bool m_buttonEPrevPressed;
	bool m_buttonFPrevPressed;
	bool m_buttonGPrevPressed;
	bool m_buttonHPrevPressed;
	bool m_buttonIPrevPressed;
	bool m_buttonJPrevPressed;
	bool m_buttonKPrevPressed;
	bool m_buttonLPrevPressed;
	bool m_buttonMPrevPressed;
	bool m_buttonNPrevPressed;
	bool m_buttonOPrevPressed;
	bool m_buttonPPrevPressed;
	bool m_buttonQPrevPressed;
	bool m_buttonRPrevPressed;
	bool m_buttonSPrevPressed;
	bool m_buttonTPrevPressed;
	bool m_buttonUPrevPressed;
	bool m_buttonVPrevPressed;
	bool m_buttonWPrevPressed;
	bool m_buttonXPrevPressed;
	bool m_buttonYPrevPressed;
	bool m_buttonZPrevPressed;
	bool m_buttonBackSpacePrevPressed;
};

