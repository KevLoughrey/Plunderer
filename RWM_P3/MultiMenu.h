// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : The menu used to setup a multiplayer game. Players enter their name and are matched together
#pragma once
#include <TextBox.h>
#include <Constants.h>
#include <SDL_image.h>
#include <Button.h>
#include <KeyboardManager.h>
#include <TileBase.h>

class MultiMenu
{
public:
	///Create a multiplayer menu
	/// \param[renderer] pointer to renderer for drawing
	/// \param[world] box2d world
	MultiMenu(SDL_Renderer *renderer, b2World *world);
	~MultiMenu(void);
	///Render the multiplayer menu
	void Render();
	///Update the multiplayer menu
	void update();
	///Check which keys are being pressed to update text boxes
	void CheckKeys();
	///Check if start is pressed so we can start searching for a game
	bool checkStartButton();
	///Check if quit is pressed so we can go back to the main menu
	bool checkQuitBtn();
	///Get the name entered in first text box
	std::string getMyName();
	///Get the name entered in second text box
	std::string getFriendsName();
protected:
	TextBox *m_nameBox;
	TextBox *m_friendsBox;
	Button *m_startButton;
	Button *m_quitButton;
	SDL_Renderer *m_renderer;
	SDL_Rect m_position;
	SDL_Texture *m_texture;
	bool m_buttonTABPrevPressed; 
	int m_currButton;
	bool buttonPressed;
};

