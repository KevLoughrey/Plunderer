// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This inherits from the abstract factory to create and return new enemies.

#include <Factory.h>


#pragma once
class EnemyFactory : public Factory
{
public:
	EnemyFactory(void);
	~EnemyFactory(void);

	virtual Snake* CreateSnake(b2World *world,b2Vec2 position,SDL_Renderer *renderer, Subject* subject);
	virtual Mummy* CreateMummy(b2World *world,b2Vec2 position,SDL_Renderer *renderer, Subject* subject);
	virtual	Bat* CreateBat(	b2World* world,b2Vec2 position,SDL_Renderer* renderer,Subject* subject);
};

