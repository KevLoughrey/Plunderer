#pragma once

#include <SDL_image.h>
#include <Box2D\Box2D.h>
#include <vector>
#include <TileBase.h>

class Torch
{
public:
	/// Used to create a Torch Object
	/// \param[renderer] the renderer used to draw the block
	/// \param[position] the position to place the block
	Torch(SDL_Renderer* renderer , 
		  b2Vec2 position);
	/// destory the object
	~Torch(void);
	/// draw the object
	/// \param[offset] used for drawing in the correct position
	void Render(b2Vec2 offset);

protected:
	/// current animation frame
	int m_frame;
	int m_count;
	/// the renderer used for drawing
	SDL_Renderer *m_renderer;
	/// the pos used for drawing
	SDL_Rect pos;
	/// the initial position for drawing
	b2Vec2 m_position;
};

