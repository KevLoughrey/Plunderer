// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Singleton which returns bools representing which keys have been pressed. 

#pragma once

#include <Box2D\Box2D.h>
#include <stddef.h>
#include <SDL.h>
#include <Constants.h>
#include <iostream>

using namespace std;

class KeyboardManager
{
protected:
	static KeyboardManager *m_instance;
	//Analog joystick dead zone
	
	//Game Controller 1 handler
	SDL_Joystick* gGameController;
	KeyboardManager();
public:
	~KeyboardManager();
	static KeyboardManager* getKeys();
	static bool Key_A;
	static bool Key_B;
	static bool Key_C;
	static bool Key_D;
	static bool Key_E;
	static bool Key_F;
	static bool Key_G;
	static bool Key_H;
	static bool Key_I;
	static bool Key_J;
	static bool Key_K;
	static bool Key_L;
	static bool Key_M;
	static bool Key_N;
	static bool Key_O;
	static bool Key_P;
	static bool Key_Q;
	static bool Key_R;
	static bool Key_S;
	static bool Key_T;
	static bool Key_U;
	static bool Key_V;
	static bool Key_W;
	static bool Key_X;
	static bool Key_Y;
	static bool Key_Z;

	static bool Key_Backspace;
	static bool Key_Left;
	static bool Key_Right;
	static bool Key_Up;
	static bool Key_Space;
	static bool Key_Down;
	static bool Key_Tab;
	
	static bool Key_Enter;
	static bool Key_Shift;
	static bool leftMouseDown;
	static bool KeyboardManager::QUIT;
	void Update(SDL_Event eHandler);
	b2Vec2 mouseClickPos;
	b2Vec2 mousePos;
};

