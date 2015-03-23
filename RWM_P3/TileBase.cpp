#include <TileBase.h>

TileBase* TileBase::m_instance;

SDL_Texture *TileBase::m_textureBottom;
SDL_Texture *TileBase::m_textureLeft;
SDL_Texture *TileBase::m_textureRight;
SDL_Texture *TileBase::m_textureTop;
SDL_Texture *TileBase::m_textureTopLeft;
SDL_Texture *TileBase::m_textureBtmLeft;
SDL_Texture *TileBase::m_textureTopRight;
SDL_Texture *TileBase::m_textureBtmRight;
SDL_Texture *TileBase::m_textureCentre;
SDL_Texture *TileBase::m_textureSquareWindow;
SDL_Texture *TileBase::m_textureRoundWindow;
SDL_Texture *TileBase::m_textureArrowLeft;
SDL_Texture *TileBase::m_textureArrowRight;
SDL_Texture *TileBase::m_textureArrowTrap;
SDL_Texture *TileBase::m_textureBlockBit;
SDL_Texture *TileBase::m_textureBomb;
SDL_Texture *TileBase::m_textureStartBtn;
SDL_Texture *TileBase::m_textureMultiBtn;
SDL_Texture *TileBase::m_textureCuttingRoom;
SDL_Texture *TileBase::m_textureBoxOffice;
SDL_Texture *TileBase::m_textureGuyBtn;
SDL_Texture *TileBase::m_textureGirlBtn;
SDL_Texture *TileBase::m_textureBlock;
SDL_Texture *TileBase::m_textureRewind1;
SDL_Texture *TileBase::m_textureRewind2;
SDL_Texture *TileBase::m_textureRewind3;
SDL_Texture *TileBase::m_textureRewind4;
SDL_Texture *TileBase::m_textureBorder;
SDL_Texture *TileBase::m_textureHudBg;
SDL_Texture *TileBase::m_textureHudHeart;
SDL_Texture *TileBase::m_textureHudBomb;
SDL_Texture *TileBase::m_textureHudPickup;
SDL_Texture *TileBase::m_textureHudHourglass;
SDL_Texture *TileBase::m_textureLadder;
SDL_Texture *TileBase::m_textureMenuBg;
SDL_Texture *TileBase::m_textureMultiMenuBG;
SDL_Texture *TileBase::m_textureOptionsMenuBG;
SDL_Texture *TileBase::m_textureControls;
SDL_Texture *TileBase::m_textureSnake;
SDL_Texture *TileBase::m_textureSpike;
SDL_Texture *TileBase::m_textureTextBoxInactive;
SDL_Texture *TileBase::m_textureTextBoxActive;
SDL_Texture *TileBase::m_textureJewel;
SDL_Texture *TileBase::m_textureGameOver;
SDL_Texture *TileBase::m_textureArrowTrapLeft;
SDL_Texture *TileBase::m_textureMummy;
SDL_Texture *TileBase::m_textureBloodParticle;
SDL_Texture *TileBase::m_textureBatParticle;
SDL_Texture *TileBase::m_textureMummyParticle;
SDL_Texture *TileBase::m_textureArrowHead;

SDL_Texture *TileBase::m_textureArrowTrapRight;

std::vector<SDL_Texture*> TileBase::m_scarabVector;
std::vector<SDL_Texture*> TileBase::m_batVector;
std::vector<SDL_Texture*> TileBase::m_bombVector;
std::vector<SDL_Texture*> TileBase::m_doorStartVector;
std::vector<SDL_Texture*> TileBase::m_doorExitVector;
std::vector<SDL_Texture*> TileBase::m_explosionVector;
std::vector<SDL_Texture *> TileBase::m_torchVector;


std::vector<SDL_Texture*> TileBase::m_idle1TexturesM;
std::vector<SDL_Texture*> TileBase::m_idle2TexturesM;
std::vector<SDL_Texture*> TileBase::m_idle3TexturesM;
std::vector<SDL_Texture*> TileBase::m_runningTexturesM;
std::vector<SDL_Texture*> TileBase::m_climbTexturesM;
std::vector<SDL_Texture*> TileBase::m_deathTexturesM;
std::vector<SDL_Texture*> TileBase::m_jumpTexturesM;
std::vector<SDL_Texture*> TileBase::m_whipTexturesPlayerM;
std::vector<SDL_Texture*> TileBase::m_bombThrowTexturesM;
std::vector<SDL_Texture*> TileBase::m_sprintTexturesM;
std::vector<SDL_Texture*> TileBase::m_sprintJumpTexturesM;
std::vector<SDL_Texture*> TileBase::m_lootGrabTexturesM;
std::vector<SDL_Texture*> TileBase::m_landingTexturesM;
std::vector<SDL_Texture*> TileBase::m_snakeBiteTexturesM;
std::vector<SDL_Texture*> TileBase::m_batFearTexturesM;
std::vector<SDL_Texture*> TileBase::m_onLedgeTexturesM;


std::vector<SDL_Texture*> TileBase::m_idle1TexturesF;
std::vector<SDL_Texture*> TileBase::m_idle2TexturesF;
std::vector<SDL_Texture*> TileBase::m_idle3TexturesF;
std::vector<SDL_Texture*> TileBase::m_runningTexturesF;
std::vector<SDL_Texture*> TileBase::m_climbTexturesF;
std::vector<SDL_Texture*> TileBase::m_deathTexturesF;
std::vector<SDL_Texture*> TileBase::m_jumpTexturesF;
std::vector<SDL_Texture*> TileBase::m_whipTexturesPlayerF;
std::vector<SDL_Texture*> TileBase::m_bombThrowTexturesF;
std::vector<SDL_Texture*> TileBase::m_sprintTexturesF;
std::vector<SDL_Texture*> TileBase::m_sprintJumpTexturesF;
std::vector<SDL_Texture*> TileBase::m_lootGrabTexturesF;
std::vector<SDL_Texture*> TileBase::m_landingTexturesF;
std::vector<SDL_Texture*> TileBase::m_snakeBiteTexturesF;
std::vector<SDL_Texture*> TileBase::m_batFearTexturesF;
std::vector<SDL_Texture*> TileBase::m_onLedgeTexturesF;


std::vector<SDL_Texture*> TileBase::m_switchTextures;
std::vector<SDL_Texture*> TileBase::m_whipTexturesWhip;
std::vector<SDL_Texture*> TileBase::m_interTileTextures;

TileBase::~TileBase() 
{}


TileBase::TileBase(SDL_Renderer* renderer) 
{
	if(m_textureBottom == NULL)
	{
		m_textureBottom = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Bottom.png"));
		m_textureLeft = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Left.png"));
		m_textureRight = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Right.png"));
		m_textureTop = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Top.png"));
		m_textureTopLeft = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/TopLeft.png"));
		m_textureBtmLeft = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/BtmLeft.png"));
		m_textureTopRight = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/TopRight.png"));
		m_textureBtmRight = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/BtmRight.png"));
		m_textureRoundWindow = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/roundWindow.png"));
		m_textureCentre = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/CentreTile.png"));
		m_textureSquareWindow = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/squareWindow.png"));
		m_textureArrowLeft = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/arrowLeft.png"));
		m_textureArrowRight = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/arrowRight.png"));
		m_textureArrowTrap = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/arrowTrap.png"));
		m_textureBlockBit = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/BlockBit.png"));
		m_textureBomb = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bomb/bomb.png"));
		m_textureStartBtn =  SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Menu/startBtn.png"));
		m_textureMultiBtn = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Menu/multiBtn.png"));
		m_textureCuttingRoom = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Menu/CuttingRoom.png"));
		m_textureBoxOffice = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Menu/BackButton.png"));
		m_textureGuyBtn = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Menu/guyBtn.png"));
		m_textureGirlBtn = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Menu/girlBtn.png"));
		m_textureBlock = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Block.png"));
		m_textureRewind1 = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Sepia1.png"));
		m_textureRewind2 = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Sepia2.png"));
		m_textureRewind3 = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Sepia3.png"));
		m_textureRewind4 = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Sepia4.png"));
		m_textureBorder = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/border.png"));
		m_textureHudBg = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/HUD/HudBg.png"));
		m_textureHudHeart = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/HUD/Heart.png"));
		m_textureHudBomb = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/HUD/bomb.png"));
		m_textureHudPickup = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/HUD/pickup.png"));
		m_textureHudHourglass = SDL_CreateTextureFromSurface(renderer,IMG_Load("images/HUD/hourglass.png"));
		m_textureLadder = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/ladder.png"));
		m_textureMenuBg = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/menu.png"));
		m_textureMultiMenuBG = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/multiMenu.png"));
		m_textureOptionsMenuBG = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/optionsMenu.png"));
		m_textureControls = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Controls.png"));
		m_textureSnake = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Snake.png"));
		m_textureSpike = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/spike.png"));
		m_textureTextBoxInactive = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Menu/TextBoxInactive.png"));
		m_textureTextBoxActive = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Menu/TextBoxActive.png"));
		m_textureJewel = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/pickup.png"));
		m_textureGameOver = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/GameOver.png"));
		m_textureArrowTrapLeft = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/arrowTrapLeft.png"));
		m_textureArrowTrapRight = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/arrowTrapRight.png"));
		m_textureMummy = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Mummy.png"));
		m_textureBloodParticle = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/BlockBitBlood.png"));
		m_textureBatParticle = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/BlockBitBat.png"));
		m_textureMummyParticle = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/BlockBitMummy.png"));;
		m_textureArrowHead = SDL_CreateTextureFromSurface(renderer, IMG_Load("images/arrowHead.png"));
		
		m_scarabVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Scarab/_0.png")));
		m_scarabVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Scarab/_1.png")));

		m_batVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bat/_0.png")));
		m_batVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bat/_1.png")));

		m_bombVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bomb/bomb10.png")));
		m_bombVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bomb/bomb9.png")));
		m_bombVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bomb/bomb8.png")));
		m_bombVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bomb/bomb7.png")));
		m_bombVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bomb/bomb6.png")));
		m_bombVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bomb/bomb5.png")));
		m_bombVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bomb/bomb4.png")));
		m_bombVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bomb/bomb3.png")));
		m_bombVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bomb/bomb2.png")));
		m_bombVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Bomb/bomb1.png")));

		m_doorStartVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/start/doorStart.png")));
		m_doorStartVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/start/door1.png")));
		m_doorStartVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/start/door2.png")));
		m_doorStartVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/start/door3.png")));
		m_doorStartVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/start/door4.png")));
		m_doorStartVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/start/door5.png")));

		m_doorExitVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/end/doorStart.png")));
		m_doorExitVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/end/door0.png")));
		m_doorExitVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/end/door1.png")));
		m_doorExitVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/end/door2.png")));
		m_doorExitVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/end/door3.png")));
		m_doorExitVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/end/door4.png")));

		m_explosionVector.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Explosion/MidAirExplo__010.png")));
		m_explosionVector.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Explosion/MidAirExplo__009.png")));
		m_explosionVector.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Explosion/MidAirExplo__008.png")));
		m_explosionVector.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Explosion/MidAirExplo__007.png")));
		m_explosionVector.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Explosion/MidAirExplo__006.png")));
		m_explosionVector.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Explosion/MidAirExplo__005.png")));
		m_explosionVector.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Explosion/MidAirExplo__004.png")));
		m_explosionVector.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Explosion/MidAirExplo__003.png")));
		m_explosionVector.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Explosion/MidAirExplo__002.png")));
		m_explosionVector.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Explosion/MidAirExplo__001.png")));
		m_explosionVector.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load("images/Explosion/MidAirExplo__000.png")));

		m_torchVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Torch/torch4.png")));
		m_torchVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Torch/torch3.png")));
		m_torchVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Torch/torch2.png")));
		m_torchVector.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Torch/torch1.png")));

		m_interTileTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/interTitles/intertitle1.png")));
		m_interTileTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/interTitles/intertitle2.png")));
		m_interTileTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/interTitles/intertitle3.png")));
		m_interTileTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/interTitles/intertitle4.png")));
		m_interTileTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/interTitles/intertitle5.png")));
		m_interTileTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/interTitles/intertitle6.png")));
		m_interTileTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/interTitles/intertitle7.png")));

		m_switchTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Switch/lever1.png")));
		m_switchTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Switch/lever2.png")));
		m_switchTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Switch/lever3.png")));
		m_switchTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Switch/lever4.png")));
		m_switchTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load("images/Switch/lever5.png")));

		
		std::stringstream l_stream;
		LoadData(renderer,m_idle1TexturesM,		"images/Guy/IdleAnimation1/",			l_stream,CONSTANTS::S_TOTAL_IDLE1_FRAMES);
		LoadData(renderer,m_idle2TexturesM,		"images/Guy/IdleAnimation2/",			l_stream,CONSTANTS::S_TOTAL_IDLE2_FRAMES);
		LoadData(renderer,m_idle3TexturesM,		"images/Guy/IdleAnimation3/",			l_stream,CONSTANTS::S_TOTAL_IDLE3_FRAMES);
		LoadData(renderer,m_runningTexturesM,	"images/Guy/RunningAnimation/",			l_stream,CONSTANTS::S_TOTAL_RUN_FRAMES);
		LoadData(renderer,m_climbTexturesM,		"images/Guy/ClimbingLadderAnimation/",	l_stream,CONSTANTS::S_TOTAL_CLIMB_LADDER_FRAMES);
		LoadData(renderer,m_jumpTexturesM,		"images/Guy/JumpAnimation/",			l_stream,CONSTANTS::S_TOTAL_JUMP_FRAMES);
		LoadData(renderer,m_deathTexturesM,		"images/Guy/DeathAnimation/",			l_stream,CONSTANTS::S_TOTAL_DEATH_FRAMES);
		LoadData(renderer,m_whipTexturesPlayerM,"images/Guy/WhipAnimationPlayer/",		l_stream,CONSTANTS::S_TOTAL_WHIP_FRAMES);
		LoadData(renderer,m_bombThrowTexturesM,	"images/Guy/ThrowBombs/",				l_stream,CONSTANTS::S_TOTAL_BOMB_FRAMES);
		LoadData(renderer,m_sprintTexturesM,	"images/Guy/RunningAnimation/",			l_stream,CONSTANTS::S_TOTAL_SPRINT_FRAMES);
		LoadData(renderer,m_sprintJumpTexturesM,"images/Guy/RunJump/",					l_stream,CONSTANTS::S_TOTAL_SPRINT_JUMP_FRAMES);
		LoadData(renderer,m_lootGrabTexturesM,	"images/Guy/LootGrab/",					l_stream,CONSTANTS::S_TOTAL_LOOT_GRAB_FRAMES);
		LoadData(renderer,m_landingTexturesM,	"images/Guy/LandingAnimation/",			l_stream,CONSTANTS::S_TOTAL_LANDING_FRAMES);

		// Memory too low
		//LoadData(renderer,m_batFearTexturesM,	"images/Guy/BatScare/",					l_stream,CONSTANTS::S_TOTAL_BATSCARE_FRAMES);
		//LoadData(renderer,m_snakeBiteTexturesM,	"images/Guy/SnakeBite/",				l_stream,CONSTANTS::S_TOTAL_SNAKE_BITE_FRAMES);
		//LoadData(renderer,m_onLedgeTexturesM,	"images/Guy/BalanceAnimation/",			l_stream,CONSTANTS::S_TOTAL_ON_LEDGE_FRAMES);


		LoadData(renderer,m_idle1TexturesF,		"images/Girl/IdleAnimation1/",			l_stream,CONSTANTS::S_TOTAL_IDLE1_FRAMES);
		LoadData(renderer,m_idle2TexturesF,		"images/Girl/IdleAnimation2/",			l_stream,CONSTANTS::S_TOTAL_IDLE2_FRAMES);
		LoadData(renderer,m_idle3TexturesF,		"images/Girl/IdleAnimation3/",			l_stream,CONSTANTS::S_TOTAL_IDLE3_FRAMES);
		LoadData(renderer,m_runningTexturesF,	"images/Girl/RunningAnimation/",		l_stream,CONSTANTS::S_TOTAL_RUN_FRAMES);
		LoadData(renderer,m_climbTexturesF,		"images/Girl/ClimbingLadderAnimation/",	l_stream,CONSTANTS::S_TOTAL_CLIMB_LADDER_FRAMES);
		LoadData(renderer,m_jumpTexturesF,		"images/Girl/JumpAnimation/",			l_stream,CONSTANTS::S_TOTAL_JUMP_FRAMES);
		LoadData(renderer,m_deathTexturesF,		"images/Girl/DeathAnimation/",			l_stream,CONSTANTS::S_TOTAL_DEATH_FRAMES);
		LoadData(renderer,m_whipTexturesPlayerF,"images/Girl/WhipAnimationPlayer/",		l_stream,CONSTANTS::S_TOTAL_WHIP_FRAMES);
		LoadData(renderer,m_bombThrowTexturesF,	"images/Girl/ThrowBombs/",				l_stream,CONSTANTS::S_TOTAL_BOMB_FRAMES);
		LoadData(renderer,m_sprintTexturesF,	"images/Girl/RunningAnimation/",		l_stream,CONSTANTS::S_TOTAL_SPRINT_FRAMES);
		LoadData(renderer,m_sprintJumpTexturesF,"images/Girl/RunJump/",					l_stream,CONSTANTS::S_TOTAL_SPRINT_JUMP_FRAMES);
		LoadData(renderer,m_lootGrabTexturesF,	"images/Girl/LootGrab/",				l_stream,CONSTANTS::S_TOTAL_LOOT_GRAB_FRAMES);

		LoadData(renderer,m_landingTexturesF,	"images/Girl/LandingAnimation/",		l_stream,CONSTANTS::S_TOTAL_LANDING_FRAMES);

		// Memory too low

		//LoadData(renderer,m_batFearTexturesF,	"images/Girl/BatScare/",				l_stream,CONSTANTS::S_TOTAL_BATSCARE_FRAMES);
		//LoadData(renderer,m_snakeBiteTexturesF,	"images/Girl/SnakeBite/",				l_stream,CONSTANTS::S_TOTAL_SNAKE_BITE_FRAMES);
		//LoadData(renderer,m_onLedgeTexturesF,	"images/Girl/BalanceAnimation/",		l_stream,CONSTANTS::S_TOTAL_ON_LEDGE_FRAMES);


		LoadData(renderer,m_whipTexturesWhip,	"images/WhipAnimationWhip/",			l_stream,CONSTANTS::S_TOTAL_WHIP_FRAMES);
	}
	m_zoomScale = 1;
	m_player = "Guy";
}

TileBase* TileBase::getTileBase(SDL_Renderer *renderer) 
{
	if (m_instance == NULL) 
	{
		m_instance = new TileBase(renderer);
	}
	return m_instance;
}

void TileBase::ResetZoom()
{
	m_zoomScale = 1;
}

void TileBase::AddZoom()
{
	if (m_zoomScale <= 2.3)
	{
		m_zoomScale += 0.01;
	}	
}

void TileBase::MinusZoom()
{
	if (m_zoomScale > 1)
	{
		m_zoomScale -= 0.01;
	}
}

void TileBase::LoadData(SDL_Renderer *renderer,std::vector<SDL_Texture*> &storage, std::string path, std::stringstream &stream, int size)
{
	stream<<path;
	for(int i = 0; i < size; i++)
	{
		stream << "_" << i << ".png";
		storage.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load(stream.str().c_str())));
		stream.str("");
		stream<<path;
	}
	stream.str("");
}


TileBase* TileBase::getBase()
{
	return m_instance;
}

void TileBase::SetPlayer(std::string thePlayer)
{
	m_player = thePlayer;
}

std::string TileBase::GetPlayer()
{
	return m_player;
}