// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------

// PURPOSE : Shows the player the controls and allows them to select their player.

#pragma once
#include <TextBox.h>
#include <Constants.h>
#include <SDL_image.h>
#include <Button.h>
#include <KeyboardManager.h>
#include <TileBase.h>


class OptionsMenu
{
public:
	///Sets up the menu.
	/// \param[renderer] passes the renderer so it can display the menu.
	/// \param[world] passes the world so it can display the menu.
	OptionsMenu(SDL_Renderer *renderer,b2World *world);


	~OptionsMenu(void);
	void Render();

	///Previous option to check if the player returns to the main menu. No longer used.
	bool checkBackPressed();

	///Checks if the player has selected to play as the guy.
	bool checkGuyPressed();
	
	///Checks if the player has selected to play as the girl.
	bool checkGirlPressed();

	///Check if the player is pressing keys to select different options.
	void CheckKeys();

protected:

	///Rendering information.
	SDL_Renderer *m_renderer;
	SDL_Rect m_position;
	SDL_Rect m_controlPosition;
	SDL_Texture *m_texture;
	SDL_Texture *m_controlTexture;

	///The buttons the player can select.
	Button *m_exitBtn;
	Button *m_guyBtn;
	Button *m_girlBtn;

	///The current button the player has highlighted.
	int currButton;

	///Whether or not the player has pressed a button.
	bool buttonPressed;
};

