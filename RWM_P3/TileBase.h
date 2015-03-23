// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This Class Is responsible for loading every texture in game using all static texture it follows the
//			 flyweight pattern


#pragma once

#include <SDL_image.h>
#include <Constants.h>
#include <string>
#include <sstream>
#include <vector>

static class TileBase
{
public:
	/// used to create a tilebase object
	/// \param[renderer] used to create the textures
	TileBase(SDL_Renderer *renderer);
	TileBase();
	/// Destorys the tilebase object
	~TileBase();
	/// Loads the player animations
	/// \param[renderer] to create the textures
	/// \param[storage] the vector that will be filled
	/// \param[path] the path to the directory
	/// \param[stream] the strings used to define each animation
	/// \param[size] the size of the animation list
	void LoadData(SDL_Renderer *renderer,std::vector<SDL_Texture*> &storage, std::string path, std::stringstream &stream, int size);
	/// \return the renderer
	SDL_Renderer* GetRenderer();
	SDL_Texture* GetDirtTexture();
	/// All static textures used in the game
	static TileBase *m_instance;
	static TileBase* getTileBase(SDL_Renderer *renderer);
	static TileBase* getBase();
	static SDL_Texture *m_textureBg;
	static SDL_Texture *m_textureTop;
	static SDL_Texture *m_textureLeft;
	static SDL_Texture *m_textureRight;
	static SDL_Texture *m_textureBottom;
	static SDL_Texture *m_textureTopLeft;
	static SDL_Texture *m_textureBtmLeft;
	static SDL_Texture *m_textureTopRight;
	static SDL_Texture *m_textureBtmRight;
	static SDL_Texture *m_textureCentre;
	static SDL_Texture *m_textureSquareWindow;
	static SDL_Texture *m_textureRoundWindow;
	static SDL_Texture *m_textureArrowLeft;
	static SDL_Texture *m_textureArrowRight;
	static SDL_Texture *m_textureArrowTrap;
	static SDL_Texture *m_textureBlockBit;
	static SDL_Texture *m_textureBomb;
	static SDL_Texture *m_textureStartBtn;
	static SDL_Texture *m_textureMultiBtn;
	static SDL_Texture *m_textureCuttingRoom;
	static SDL_Texture *m_textureBoxOffice;
	static SDL_Texture *m_textureGuyBtn;
	static SDL_Texture *m_textureGirlBtn;
	static SDL_Texture *m_textureBlock;
	static SDL_Texture *m_textureRewind1;
	static SDL_Texture *m_textureRewind2;
	static SDL_Texture *m_textureRewind3;
	static SDL_Texture *m_textureRewind4;
	static SDL_Texture *m_textureBorder;
	static SDL_Texture *m_textureHudBg;
	static SDL_Texture *m_textureHudHeart;
	static SDL_Texture *m_textureHudBomb;
	static SDL_Texture *m_textureHudPickup;
	static SDL_Texture *m_textureHudHourglass;
	static SDL_Texture *m_textureLadder;
	static SDL_Texture *m_textureMenuBg;
	static SDL_Texture *m_textureMultiMenuBG;
	static SDL_Texture *m_textureOptionsMenuBG;
	static SDL_Texture *m_textureControls;
	static SDL_Texture *m_textureSnake;
	static SDL_Texture *m_textureSpike;
	static SDL_Texture *m_textureTextBoxInactive;
	static SDL_Texture *m_textureTextBoxActive;
	static SDL_Texture *m_textureJewel;
	static SDL_Texture *m_textureGameOver;
	static SDL_Texture *m_textureMummy;
	static SDL_Texture *m_textureArrowTrapLeft;
	static SDL_Texture *m_textureArrowTrapRight;
	static SDL_Texture *m_textureBloodParticle;
	static SDL_Texture *m_textureBatParticle;
	static SDL_Texture *m_textureMummyParticle;
	static SDL_Texture *m_textureArrowHead;
	
	/// all static vectors for the animations in the game
	static std::vector<SDL_Texture *> m_scarabVector;
	static std::vector<SDL_Texture *> m_batVector;
	static std::vector<SDL_Texture*> m_bombVector;
	static std::vector<SDL_Texture*> m_doorStartVector;
	static std::vector<SDL_Texture *> m_doorExitVector;
	static std::vector<SDL_Texture *> m_explosionVector;
	static std::vector<SDL_Texture *> m_torchVector;

	static std::vector<SDL_Texture*> m_idle1TexturesM;
	static std::vector<SDL_Texture*> m_idle2TexturesM;
	static std::vector<SDL_Texture*> m_idle3TexturesM;
	static std::vector<SDL_Texture*> m_runningTexturesM;
	static std::vector<SDL_Texture*> m_climbTexturesM;
	static std::vector<SDL_Texture*> m_deathTexturesM;
	static std::vector<SDL_Texture*> m_jumpTexturesM;
	static std::vector<SDL_Texture*> m_whipTexturesPlayerM;
	static std::vector<SDL_Texture*> m_bombThrowTexturesM;
	static std::vector<SDL_Texture*> m_sprintTexturesM;
	static std::vector<SDL_Texture*> m_sprintJumpTexturesM;
	static std::vector<SDL_Texture*> m_lootGrabTexturesM;
	static std::vector<SDL_Texture*> m_landingTexturesM;
	static std::vector<SDL_Texture*> m_snakeBiteTexturesM;
	static std::vector<SDL_Texture*> m_batFearTexturesM;
	static std::vector<SDL_Texture*> m_onLedgeTexturesM;

	static std::vector<SDL_Texture*> m_idle1TexturesF;
	static std::vector<SDL_Texture*> m_idle2TexturesF;
	static std::vector<SDL_Texture*> m_idle3TexturesF;
	static std::vector<SDL_Texture*> m_runningTexturesF;
	static std::vector<SDL_Texture*> m_climbTexturesF;
	static std::vector<SDL_Texture*> m_deathTexturesF;
	static std::vector<SDL_Texture*> m_jumpTexturesF;
	static std::vector<SDL_Texture*> m_whipTexturesPlayerF;
	static std::vector<SDL_Texture*> m_bombThrowTexturesF;
	static std::vector<SDL_Texture*> m_sprintTexturesF;
	static std::vector<SDL_Texture*> m_sprintJumpTexturesF;
	static std::vector<SDL_Texture*> m_lootGrabTexturesF;
	static std::vector<SDL_Texture*> m_landingTexturesF;
	static std::vector<SDL_Texture*> m_snakeBiteTexturesF;
	static std::vector<SDL_Texture*> m_batFearTexturesF;
	static std::vector<SDL_Texture*> m_onLedgeTexturesF;

	static std::vector<SDL_Texture*> m_switchTextures;
	static std::vector<SDL_Texture*> m_whipTexturesWhip;
	static std::vector<SDL_Texture*> m_interTileTextures;

	/// the zoom factor for scalin
	float m_zoomScale;
	/// the string for which player to load
	std::string m_player;
	/// sets the players string
	/// \param[s] sets the string of the player
	void SetPlayer(std::string s);
	/// \return the players string value
	std::string GetPlayer();
	/// zoom in
	void AddZoom();
	/// zoom out
	void MinusZoom();
	/// reset the zoom to one
	void ResetZoom();
};