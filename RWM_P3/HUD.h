// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This Is used to display the game information to the player E.g (Lives , Bombs)

#pragma once

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <Player.h>
#include <TileBase.h>
#include <MapManager.h>

class HUD
{
public:
	/// Used to create a HUD Object
	/// \param[renderer] the renderer used to draw the object
	/// \param[mapManager] the mapmanager used to drive the HUD
	HUD(SDL_Renderer *renderer, 
		MapManager *mapManager);
	/// Destroy the object
	~HUD(void);
	/// used to draw the Object
	void Render();
	/// to set the hud visible or not
	/// \param[visible] used to toggle visibility
	void SetVisible(bool visible);
	/// count the number of hourglass
	void CountHourglass();
	/// \return if an hourglass available 
	bool GetHourALive();
	/// set the hourglass is alive
	/// \param[alive] toggles the hourglass alive or not
	void SetHOurAlive(bool alive);
	/// update the HUD
	void Update();

protected:
	/// Used to draw and update the HUD
	TTF_Font *m_font;
	SDL_Rect m_bgPos;
	SDL_Rect m_heartPos;
	SDL_Rect m_bombPos;
	SDL_Rect m_pickupPos;
	SDL_Rect m_livesTextPos;
	SDL_Rect m_bombsTextPos;
	SDL_Rect m_jewelTextPos;
	SDL_Rect m_hourGlassPos;

	/// renderer used for drawing
	SDL_Renderer *m_renderer;

	/// the text for the HUD
	std::string m_livesText;
	std::string m_bombsText;
	std::string m_jewelsText;
	
	/// the Textures used to draw the strings to
	SDL_Texture *mTextLives;
	SDL_Texture *mTextBombs;
	SDL_Texture *mTextJewels;
	
	/// the color of the writing
	SDL_Color* c;

	/// the surface used to draw the strings
	SDL_Surface* textSurface;
	SDL_Surface* textBombs;
	SDL_Surface* textJewels;

	/// if the hud is visible
	bool m_visible;

	/// if the hourglass is alive
	bool m_hourAlive;

	/// count to reset the hourglass
	int m_hourCount;

	/// the refrence to the player to access the stats
	Player* m_player;

	/// a refrence to the mapmanager to acces and set stats
	MapManager *m_mapManager;

};

