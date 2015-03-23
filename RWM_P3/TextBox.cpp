#include "TextBox.h"


TextBox::TextBox(SDL_Renderer *renderer, b2Vec2 position)
	: active(false),
	m_renderer(renderer)
{
	textWidth = 0;
	m_text = " ";
	gFont = TTF_OpenFont( "Fonts/Nathan.ttf", 42 );
	m_position.x = position.x;
	m_position.y = position.y;
	m_position.w = 325;
	m_position.h = 100;

	SDL_Color* c = new SDL_Color();
	c->r=44;
	c->g=44;
	c->b=44;
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, m_text.c_str(),*c );


	mTextImage=SDL_CreateTextureFromSurface(m_renderer, textSurface);
	SDL_FreeSurface(textSurface);

	 m_buttonAPrevPressed = false;
	 m_buttonBPrevPressed = false;
	 m_buttonCPrevPressed = false;
	 m_buttonDPrevPressed = false;
	 m_buttonEPrevPressed = false;
	 m_buttonFPrevPressed = false;
	 m_buttonGPrevPressed = false;
	 m_buttonHPrevPressed = false;
	 m_buttonIPrevPressed = false;
	 m_buttonJPrevPressed = false;
	 m_buttonKPrevPressed = false;
	 m_buttonLPrevPressed = false;
	 m_buttonMPrevPressed = false;
	 m_buttonNPrevPressed = false;
	 m_buttonOPrevPressed = false;
	 m_buttonPPrevPressed = false;
	 m_buttonQPrevPressed = false;
	 m_buttonRPrevPressed = false;
	 m_buttonSPrevPressed = false;
	 m_buttonTPrevPressed = false;
	 m_buttonUPrevPressed = false;
	 m_buttonVPrevPressed = false;
	 m_buttonWPrevPressed = false;
	 m_buttonXPrevPressed = false;
	 m_buttonYPrevPressed = false;
	 m_buttonZPrevPressed = false;
	 m_buttonBackSpacePrevPressed = false;
}


TextBox::~TextBox(void)
{
}


void TextBox::update()
{
	if (KeyboardManager::getKeys()->leftMouseDown == true)
	{
		if(KeyboardManager::getKeys()->mousePos.x > m_position.x 
		&& KeyboardManager::getKeys()->mousePos.x < m_position.x + m_position.w 
		&& KeyboardManager::getKeys()->mousePos.y > m_position.y 
		&& KeyboardManager::getKeys()->mousePos.y < m_position.y + m_position.h)
		{
			active = true;
		}
		else
		{
			active = false;
		}
	}
	if(active)
	{
		appendInputToString();
		SDL_Color* c = new SDL_Color();
		c->r=44;
		c->g=44;
		c->b=44;
	}
}
bool TextBox::getActive()
{
	return active;
}
void TextBox::setActive(bool b)
{
	active = b;
}
void TextBox::appendInputToString()
{
	if(m_text.size() < 10){
		if(KeyboardManager::getKeys()-> Key_A && !m_buttonAPrevPressed)
		{ 
			m_buttonAPrevPressed = true;
			m_text.append("a");
		}
		else if(!KeyboardManager::getKeys()->Key_A)
		{
			m_buttonAPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_B && !m_buttonBPrevPressed)
		{ 
			m_buttonBPrevPressed = true;
			m_text.append("b");
		}
		else if(!KeyboardManager::getKeys()->Key_B)
		{
			m_buttonBPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_C && !m_buttonCPrevPressed)
		{ 
			m_buttonCPrevPressed = true;
			m_text.append("c");
		}
		else if(!KeyboardManager::getKeys()->Key_C)
		{
			m_buttonCPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_D && !m_buttonDPrevPressed)
		{ 
			m_buttonDPrevPressed = true;
			m_text.append("d");
		}
		else if(!KeyboardManager::getKeys()->Key_D)
		{
			m_buttonDPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_E && !m_buttonEPrevPressed)
		{ 
			m_buttonEPrevPressed = true;
			m_text.append("e");
		}
		else if(!KeyboardManager::getKeys()->Key_E)
		{
			m_buttonEPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_F && !m_buttonFPrevPressed)
		{ 
			m_buttonFPrevPressed = true;
			m_text.append("f");
		}
		else if(!KeyboardManager::getKeys()->Key_F)
		{
			m_buttonFPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_G && !m_buttonGPrevPressed)
		{ 
			m_buttonGPrevPressed = true;
			m_text.append("g");
		}
		else if(!KeyboardManager::getKeys()->Key_G)
		{
			m_buttonGPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_H && !m_buttonHPrevPressed)
		{ 
			m_buttonHPrevPressed = true;
			m_text.append("h");
		}
		else if(!KeyboardManager::getKeys()->Key_H)
		{
			m_buttonHPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_I && !m_buttonIPrevPressed)
		{ 
			m_buttonIPrevPressed = true;
			m_text.append("i");
		}
		else if(!KeyboardManager::getKeys()->Key_I)
		{
			m_buttonIPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_J && !m_buttonJPrevPressed)
		{ 
			m_buttonJPrevPressed = true;
			m_text.append("j");
		}
		else if(!KeyboardManager::getKeys()->Key_J)
		{
			m_buttonJPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_K && !m_buttonKPrevPressed)
		{ 
			m_buttonKPrevPressed = true;
			m_text.append("k");
		}
		else if(!KeyboardManager::getKeys()->Key_K)
		{
			m_buttonKPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_L && !m_buttonLPrevPressed)
		{ 
			m_buttonLPrevPressed = true;
			m_text.append("l");
		}
		else if(!KeyboardManager::getKeys()->Key_L)
		{
			m_buttonLPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_M && !m_buttonMPrevPressed)
		{ 
			m_buttonMPrevPressed = true;
			m_text.append("m");
		}
		else if(!KeyboardManager::getKeys()->Key_M)
		{
			m_buttonMPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_N && !m_buttonNPrevPressed)
		{ 
			m_buttonNPrevPressed = true;
			m_text.append("n");
		}
		else if(!KeyboardManager::getKeys()->Key_N)
		{
			m_buttonNPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_O && !m_buttonOPrevPressed)
		{ 
			m_buttonOPrevPressed = true;
			m_text.append("o");
		}
		else if(!KeyboardManager::getKeys()->Key_O)
		{
			m_buttonOPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_P && !m_buttonPPrevPressed)
		{ 
			m_buttonPPrevPressed = true;
			m_text.append("p");
		}
		else if(!KeyboardManager::getKeys()->Key_P)
		{
			m_buttonPPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_Q && !m_buttonQPrevPressed)
		{ 
			m_buttonQPrevPressed = true;
			m_text.append("q");
		}
		else if(!KeyboardManager::getKeys()->Key_Q)
		{
			m_buttonQPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_R && !m_buttonRPrevPressed)
		{ 
			m_buttonRPrevPressed = true;
			m_text.append("r");
		}
		else if(!KeyboardManager::getKeys()->Key_R)
		{
			m_buttonRPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_S && !m_buttonSPrevPressed)
		{ 
			m_buttonSPrevPressed = true;
			m_text.append("s");
		}
		else if(!KeyboardManager::getKeys()->Key_S)
		{
			m_buttonSPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_T && !m_buttonTPrevPressed)
		{ 
			m_buttonTPrevPressed = true;
			m_text.append("t");
		}
		else if(!KeyboardManager::getKeys()->Key_T)
		{
			m_buttonTPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_U && !m_buttonUPrevPressed)
		{ 
			m_buttonUPrevPressed = true;
			m_text.append("u");
		}
		else if(!KeyboardManager::getKeys()->Key_U)
		{
			m_buttonUPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_V && !m_buttonVPrevPressed)
		{ 
			m_buttonVPrevPressed = true;
			m_text.append("v");
		}
		else if(!KeyboardManager::getKeys()->Key_V)
		{
			m_buttonVPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_W && !m_buttonWPrevPressed)
		{ 
			m_buttonWPrevPressed = true;
			m_text.append("w");
		}
		else if(!KeyboardManager::getKeys()->Key_W)
		{
			m_buttonWPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_X && !m_buttonXPrevPressed)
		{ 
			m_buttonXPrevPressed = true;
			m_text.append("x");
		}
		else if(!KeyboardManager::getKeys()->Key_X)
		{
			m_buttonXPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_Y && !m_buttonYPrevPressed)
		{ 
			m_buttonYPrevPressed = true;
			m_text.append("y");
		}
		else if(!KeyboardManager::getKeys()->Key_Y)
		{
			m_buttonYPrevPressed = false;
		}
		if(KeyboardManager::getKeys()-> Key_Z && !m_buttonZPrevPressed)
		{ 
			m_buttonZPrevPressed = true;
			m_text.append("z");
		}
		else if(!KeyboardManager::getKeys()->Key_Z)
		{
			m_buttonZPrevPressed = false;
		}
	}
	if(KeyboardManager::getKeys()->Key_Backspace && !m_buttonBackSpacePrevPressed)
	{ 
		m_buttonBackSpacePrevPressed = true;
		if(m_text.size() > 1)
		{
			m_text.pop_back();
		}
		
	}
	else if(!KeyboardManager::getKeys()->Key_Backspace)
	{
		m_buttonBackSpacePrevPressed = false;
	}

	
}
void TextBox::Render()
{
	if (active)
	{
		SDL_RenderCopy(m_renderer, TileBase::getBase()->m_textureTextBoxActive, NULL, &m_position);
		
	}
	else
	{
		SDL_RenderCopy(m_renderer, TileBase::getBase()->m_textureTextBoxInactive, NULL, &m_position);
	}
	SDL_Color b;
	b.a=255;
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, m_text.c_str(), b);
	if (textSurface != NULL)
	{
		mTextImage=SDL_CreateTextureFromSurface(m_renderer, textSurface);
		if (mTextImage == NULL)
		{
		}
		else
		{
			textWidth = textSurface->w;
		}
	}
	SDL_Rect renderQuad = { m_position.x+100, m_position.y+8,textWidth, 80};
	SDL_RenderCopy(m_renderer,mTextImage,NULL,&renderQuad);
	SDL_DestroyTexture(mTextImage);
	SDL_FreeSurface(textSurface);
}
std::string TextBox::getText()
{
	return m_text;
}