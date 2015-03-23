// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This is the main entry point menu of the game displays play, multi game and options

#pragma once

#include <SDL_image.h>
#include <Constants.h>
#include <Button.h>
#include <Box2D\Box2D.h>
#include <MultiplayerGame.h>
#include <KeyboardManager.h>
#include <TileBase.h>

class MainMenu
{
public:
	/// Used to create a MainMenu Object
	/// \param[renderer] the renderer used to draw the block
	/// \param[world] The Box2d world used to add bodies
	MainMenu(SDL_Renderer *renderer,
			 b2World *world);
	/// Destroy the Object
	~MainMenu();
	/// Draw the object
	void Render();
	/// \return if any of the buttons are pressed
	bool CheckPlayButton();
	bool CheckQuitButton();
	bool CheckMultiButton();
	bool CheckOptionButton();
	/// update the key handler to check for input
	void CheckKeys();
	/// set all the buttons to false on a reset
	void SetButtons();
	/// \return a multiplayer game object
	MultiplayerGame *getMultiGame();
	/// the sound plays only once
	bool doOnce;

protected:
	/// renderer to draw the object
	SDL_Renderer *m_renderer;
	SDL_Texture *m_textureBg;
	/// the position of the menu
	SDL_Rect m_position;
	/// Definition of the buttons
	Button *m_playBtn;
	Button *m_quitBtn;
	Button *m_multiBtn;
	Button *m_optionBtn;
	/// which button is currently highlighted
	int currButton;
	/// if the button has been pressed or not
	bool buttonPressed;
	
};

