// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This is for the explosion animation when a bomb is destroyed it olayes the animation


#pragma once

#include <SDL_image.h>
#include <Box2D\Box2D.h>
#include <vector>
#include <Constants.h>
#include <TileBase.h>

class Explosion
{
public:
	Explosion(SDL_Renderer *renderer,
			  b2Vec2 position);
	~Explosion(void);
	void Render(b2Vec2 offset);
	void setAlive(bool alive);
	bool getFinished();

protected:
	SDL_Renderer *m_renderer;
	SDL_Rect pos;
	b2Vec2 m_position;
	int m_frame;
	int m_count;
	bool m_alive;
	bool m_finished;
	
};

