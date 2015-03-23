#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(void)
{

}

EnemyFactory::~EnemyFactory(void)
{
}

Snake* EnemyFactory::CreateSnake(b2World *world,b2Vec2 position,SDL_Renderer *renderer, Subject* subject)
{
	Snake *s = new Snake(world,position,renderer, subject);
	return s;
}

Mummy* EnemyFactory::CreateMummy(b2World *world,b2Vec2 position,SDL_Renderer *renderer, Subject* subject)
{
	Mummy *m = new Mummy(world, position, renderer, subject);
	return m;
}

Bat*  EnemyFactory::CreateBat(b2World* world, b2Vec2 position, SDL_Renderer* renderer, Subject* subject)
{
	Bat *b = new Bat(world, position, renderer, subject);
	return b;
}