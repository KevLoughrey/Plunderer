#include <KeyboardManager.h>

KeyboardManager *KeyboardManager::m_instance;
bool KeyboardManager::Key_A;
bool KeyboardManager::Key_B;
bool KeyboardManager::Key_C;
bool KeyboardManager::Key_D;
bool KeyboardManager::Key_E;
bool KeyboardManager::Key_F;
bool KeyboardManager::Key_G;
bool KeyboardManager::Key_H;
bool KeyboardManager::Key_I;
bool KeyboardManager::Key_J;
bool KeyboardManager::Key_K;
bool KeyboardManager::Key_L;
bool KeyboardManager::Key_M;
bool KeyboardManager::Key_N;
bool KeyboardManager::Key_O;
bool KeyboardManager::Key_P;
bool KeyboardManager::Key_Q;
bool KeyboardManager::Key_R;
bool KeyboardManager::Key_S;
bool KeyboardManager::Key_T;
bool KeyboardManager::Key_U;
bool KeyboardManager::Key_V;
bool KeyboardManager::Key_W;
bool KeyboardManager::Key_X;
bool KeyboardManager::Key_Y;
bool KeyboardManager::Key_Z;

bool KeyboardManager::Key_Left;
bool KeyboardManager::Key_Right;
bool KeyboardManager::Key_Up;
bool KeyboardManager::Key_Space;
bool KeyboardManager::Key_Down;
bool KeyboardManager::Key_Enter;
bool KeyboardManager::Key_Shift;
bool KeyboardManager::QUIT;
bool KeyboardManager::leftMouseDown;
bool KeyboardManager::Key_Backspace;
bool KeyboardManager::Key_Tab;

KeyboardManager* KeyboardManager::getKeys()
{
	if (m_instance == NULL)
	{
		m_instance = new KeyboardManager();
		Key_Left = false;
		Key_Right = false;
		Key_Up = false;
		Key_Space = false;
		Key_Down = false;
		Key_A= false;
		Key_B= false;
		Key_C= false;
		Key_D= false;
		Key_E= false;
		Key_F= false;
		Key_G= false;
		Key_H= false;
		Key_I= false;
		Key_J= false;
		Key_K= false;
		Key_L= false;
		Key_M= false;
		Key_N= false;
		Key_O= false;
		Key_P= false;
		Key_Q= false;
		Key_R= false;
		Key_S= false;
		Key_T= false;
		Key_U= false;
		Key_V= false;
		Key_W= false;
		Key_X= false;
		Key_Y= false;
		Key_Z= false;
		Key_Shift = false;
		QUIT = false;
		leftMouseDown = false;
		Key_Backspace = false;
		Key_Tab = false;
	}
	return m_instance;
}

KeyboardManager::KeyboardManager(void)
{
	 gGameController = SDL_JoystickOpen( 0 );
}


KeyboardManager::~KeyboardManager(void)
{
}

void KeyboardManager::Update(SDL_Event eHandler)
{
	while(SDL_PollEvent( &eHandler ) != 0) 
	{ 
		if (eHandler.type == SDL_MOUSEBUTTONDOWN)
		{
			leftMouseDown = true;
			mousePos.x = eHandler.button.x;
			mousePos.y = eHandler.button.y;
		}
		else if (eHandler.type == SDL_MOUSEBUTTONUP && leftMouseDown)
		{	
			mouseClickPos.x = eHandler.button.x;
			mouseClickPos.y = eHandler.button.y;
			leftMouseDown=false;
		}

		int xDir = 0;

		if ( eHandler.type == SDL_QUIT )
		{ 
			QUIT = true; 
		} 

		if(eHandler.type == SDL_JOYBUTTONDOWN)
		{
			if(eHandler.jbutton.button == 10)
			{
				Key_Space = true;
			}
			else if(eHandler.jbutton.button == 11)
			{
				Key_S = true;
			}
			else if(eHandler.jbutton.button == 8)
			{
				Key_Shift = true;
			}
			else if(eHandler.jbutton.button == 9)
			{
				Key_R = true;
			}
			 if(eHandler.jbutton.button == 0)
			{
				Key_Up = true;
			}
			 if(eHandler.jbutton.button == 4)
			{
				Key_Down = true;
			}
			 if (eHandler.jbutton.button == 0)
			 {
				 Key_P = true;
			 }
			 if (eHandler.jbutton.button == 1)
			 {
				 Key_O = true;
			 }
			 if (eHandler.jbutton.button == 5)
			 {
				 Key_W = true;
			 }
			 if (eHandler.jbutton.button == 13)
			 {
				 Key_Q = true;
			 }
			 if (eHandler.jbutton.button == 12)
			 {
				 Key_X = true;
			 }
			 if (eHandler.jbutton.button == 14)
			 {
				 QUIT = true;
			 }
			 if (eHandler.jbutton.button == 3)
			 {
				Key_B = true;
			 }

		}

		if(eHandler.type == SDL_JOYBUTTONUP)
		{
			if(eHandler.jbutton.button == 10)
			{
				Key_Space = false;
			}
			else if(eHandler.jbutton.button == 11)
			{
				Key_S = false;
			}
			else if(eHandler.jbutton.button == 8)
			{
				Key_Shift = false;
			}
			else if(eHandler.jbutton.button == 9)
			{
				Key_R = false;
			}
			 if(eHandler.jbutton.button == 0)
			{
				Key_Up = true;
			}
			if(eHandler.jbutton.button == 4)
			{
				Key_Down = true;
			}
			if (eHandler.jbutton.button == 0)
			{
				Key_P = false;
			}
			if (eHandler.jbutton.button == 1)
			{
				Key_O = false;
			}
			if (eHandler.jbutton.button == 5)
			{
				Key_W = false;
			}
			if (eHandler.jbutton.button == 13)
			{
				Key_Q = false;
			}
			if (eHandler.jbutton.button == 12)
			{
				Key_X = false;
			}
			if (eHandler.jbutton.button == 14)
			{
				QUIT = false;
			}
			if (eHandler.jbutton.button == 3)
			{
				Key_B = false;
			}
		  }

		else if( eHandler.type == SDL_JOYAXISMOTION )
					{
						//Motion on controller 0
						if( eHandler.jaxis.which == 0 )
						{                        
							//X axis motion
							if( eHandler.jaxis.axis == 0 )
							{
								//Left of dead zone
								if( eHandler.jaxis.value < -CONSTANTS::JOYSTICK_DEAD_ZONE )
								{
									Key_Left = true;
								}
								//Right of dead zone
								else if( eHandler.jaxis.value > CONSTANTS::JOYSTICK_DEAD_ZONE )
								{
									Key_Right = true;
								}
								else
								{
									Key_Right = false;
									Key_Left = false;
								}
							}
							 else if( eHandler.jaxis.axis == 1 )
							{
								//Below of dead zone
								if( eHandler.jaxis.value < -CONSTANTS::JOYSTICK_DEAD_ZONE )
								{
									Key_Up = true;
								}
								//Above of dead zone
								else if( eHandler.jaxis.value > CONSTANTS::JOYSTICK_DEAD_ZONE )
								{
									Key_Down = true;
									Key_Up = false;
								}
								else
								{
									Key_Up = false;
									Key_Down = false;
								}
							}
						}
		}


		else if ( eHandler.type == SDL_KEYDOWN )
		{ 
			switch( eHandler.key.keysym.sym )
			{
			case SDLK_ESCAPE: 
				QUIT = true;
				break; 
			case SDLK_UP:
				Key_Up = true;
				break; 
			case SDLK_DOWN:
				Key_Down = true;
				break; 
			case SDLK_LEFT:
				Key_Left = true;
				break; 
			case SDLK_RIGHT:
				Key_Right = true;
				break; 
			case SDLK_SPACE:
				Key_Space = true;
				break; 
			case SDLK_RETURN:
				Key_Enter = true;
				Key_Space = true;
				break;
			case SDLK_a:
				Key_A = true;
				break;
			case SDLK_b:
				Key_B = true;
				break;
			case SDLK_c:
				Key_C = true;
				break;
			case SDLK_d:
				Key_D = true;
				break;
			case SDLK_e:
				Key_E = true;
				break;
			case SDLK_f:
				Key_F = true;
				break;
			case SDLK_g:
				Key_G = true;
				break;
			case SDLK_h:
				Key_H = true;
				break;
			case SDLK_i:
				Key_I = true;
				break;
			case SDLK_j:
				Key_J = true;
				break;
			case SDLK_k:
				Key_K = true;
				break;
			case SDLK_l:
				Key_L = true;
				break;
			case SDLK_m:
				Key_M = true;
				break;
			case SDLK_n:
				Key_N = true;
				break;
			case SDLK_o:
				Key_O = true;
				break;
			case SDLK_p:
				Key_P = true;
				break;
			case SDLK_q:
				Key_Q = true;
				break;
			case SDLK_r:
				Key_R = true;
				break;
			case SDLK_s:
				Key_S = true;
				break;
			case SDLK_t:
				Key_T = true;
				break;
			case SDLK_u:
				Key_U = true;
				break;
			case SDLK_v:
				Key_V = true;
				break;
			case SDLK_w:
				Key_W = true;
				break;
			case SDLK_x:
				Key_X = true;
				break;
			case SDLK_y:
				Key_Y = true;
				break;
			case SDLK_z:
				Key_Z = true;
				break;
			case SDLK_LSHIFT:
				Key_Shift = true;
				break;
			case SDLK_BACKSPACE:
				Key_Backspace = true;
				break;
			case SDLK_TAB:
				Key_Tab = true;
				break;
			default: 
				break; 
			}
		}
		else if ( eHandler.type == SDL_KEYUP )
		{ 
			switch( eHandler.key.keysym.sym )
			{
			case SDLK_ESCAPE: 
				QUIT = false;
				break; 
			case SDLK_UP:
				Key_Up = false;
				break; 
			case SDLK_DOWN:
				Key_Down = false;
				break; 
			case SDLK_LEFT:
				Key_Left = false;
				break; 
			case SDLK_RIGHT:
				Key_Right = false;
				break; 
			case SDLK_SPACE:
				Key_Space = false;
				break; 
			case SDLK_RETURN:
				Key_Enter = false;
				Key_Space = false;
				break;
			case SDLK_a:
				Key_A = false;
				break;
			case SDLK_b:
				Key_B = false;
				break;
			case SDLK_c:
				Key_C = false;
				break;
			case SDLK_d:
				Key_D = false;
				break;
			case SDLK_e:
				Key_E = false;
				break;
			case SDLK_f:
				Key_F = false;
				break;
			case SDLK_g:
				Key_G = false;
				break;
			case SDLK_h:
				Key_H = false;
				break;
			case SDLK_i:
				Key_I = false;
				break;
			case SDLK_j:
				Key_J = false;
				break;
			case SDLK_k:
				Key_K = false;
				break;
			case SDLK_l:
				Key_L = false;
				break;
			case SDLK_m:
				Key_M = false;
				break;
			case SDLK_n:
				Key_N = false;
				break;
			case SDLK_o:
				Key_O = false;
				break;
			case SDLK_p:
				Key_P = false;
				break;
			case SDLK_q:
				Key_Q = false;
				break;
			case SDLK_r:
				Key_R = false;
				break;
			case SDLK_s:
				Key_S = false;
				break;
			case SDLK_t:
				Key_T = false;
				break;
			case SDLK_u:
				Key_U = false;
				break;
			case SDLK_v:
				Key_V = false;
				break;
			case SDLK_w:
				Key_W = false;
				break;
			case SDLK_x:
				Key_X = false;
				break;
			case SDLK_y:
				Key_Y = false;
				break;
			case SDLK_z:
				Key_Z = false;
				break;
			case SDLK_LSHIFT:
				Key_Shift = false;
				break;
			case SDLK_BACKSPACE:
				Key_Backspace = false;
				break;
			case SDLK_TAB:
				Key_Tab = false;
				break;
			default: 
				break; 
			}
		}
	}							
}