// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This Class Is used for a button for the menu system in the game E.g ( Play , Quit)

#pragma once

#include <SDL_image.h>
#include <Box2D\Box2D.h>
#include <KeyboardManager.h>
#include <MultiplayerGame.h>
#include <TileBase.h>

class Button
{
public:
	/// Used to create a Button Object
	/// \param[renderer] the renderer used to draw the block
	/// \param[position] the position to place the block
	/// \param[type] the button scale size
	/// \param[world] The Box2d world used to add bodies
	Button(SDL_Renderer *renderer, 
		   b2Vec2 position,
		   int type,
		   b2World *world);

	/// Destroys the Button Object
	~Button();
	
	/// Draws the Object
	void Render();

	/// Returns whether the button has been pressed or not
	bool Pressed();

	/// Set if the button is pressed or not
	/// \param[pressed] a bool to set the var pressed
	void setPressed(bool pressed);

	/// Scales the button up
	void ScaleUp();

	/// Scales the booton down
	void ScaleDown();

	/// Returns the multiplayer game Object
	MultiplayerGame *getMultiGame();

protected:
	/// The renderer used for drawing
	SDL_Renderer *m_renderer;
	/// the texture of the image
	SDL_Texture *m_texture;
	/// the original position of the object
	SDL_Rect m_position;
	/// the box2d world 
	b2World *m_world;
	/// which button texture to load
	int m_type;
	/// sets if the button is pressed or not
	bool m_pressed;
};

