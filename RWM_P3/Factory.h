// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This is an abstract factory which is used to declare other types of factories from here


#pragma once
#include <Snake.h>
#include <Mummy.h>
#include <Bat.h>

class Factory 
{
public:
	//virtual Snake* CreateSnake(b2World *world,b2Vec2 position,SDL_Renderer *renderer) = 0;
	//virtual Mummy* CreateMummy(b2World *world,b2Vec2 position,SDL_Renderer *renderer) = 0;
};