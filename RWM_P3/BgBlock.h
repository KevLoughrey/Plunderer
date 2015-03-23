// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This Class Is a tile for the background generated by the tiled map

#pragma once

#include <SDL_image.h>
#include <Box2D\Box2D.h>
#include <TileBase.h>

class BgBlock
{
public:
	///An unused sound effect for the player walking
	/// \param[renderer] the sdl renderer used for drawing
	/// \param[position] the position the block should be drawn at
	/// \param[type] used to set between destructable and indestructable blocks
	BgBlock(SDL_Renderer* renderer , 
			b2Vec2 position, 
			int type);
	/// Destroys the Object
	~BgBlock(void);

	/// used to draw the object
	/// \param[offset] used for where the "camera" is to draw the block in the correct position
	void Render(b2Vec2 offset);

protected:
	/// Stores the renderer used for drawing
	SDL_Renderer *m_renderer;

	// For decinding if its destructable or not
	int m_type;

	// the position the block should be drawn in
	SDL_Rect pos;

	// used for the starting positon of the block
	b2Vec2 m_position;
};
