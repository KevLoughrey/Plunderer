// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Static constants which can be accessed anywhere in the project.

#pragma once

///Box2D scaling defines
#define METRESTOPIXELS 30
#define PIXELSTOMETRES 1/30.0f
#define RADTODEG  (-180/3.1415926536f)  
#define DEGTORAD -0.0174532925199432957f

#define GRAVITYSCALE 9.0f

///Player defines
#define PLAYERSPEED 7.5f
#define PLAYERJUMPFORCE 30.0f
#define PLAYERSPRINTSPEED 10.85f
#define PLAYERSPRINTJUMPFORCE 35.0f

#define PHYSICS_TICKS (1.0f / 60)
#define UPDATE_TICKS (1.0f / 60)

class CONSTANTS {
public:

///Screen dimension constants
static const int SCREEN_WIDTH = 1600;
static const int SCREEN_HEIGHT = 900;

//static const int SCREEN_WIDTH = 1280;
//static const int SCREEN_HEIGHT = 720;

static const int JOYSTICK_DEAD_ZONE = 8000;

static const int NUM_PARTICLES_DEATH = 30;

static const int HOURGLASS_RESPWAN = 900;

///Block constants
static const int BLOCK_EXPLOSION_PARTICLES = 3;

///Player constants
static const int PLAYER_STARTING_HEALTH = 4;

///Trap constants
static const int ARROW_TRIGGER_DISTANCE = 250;

///Animation Constants
static const int S_TOTAL_RUN_FRAMES = 10;
static const int S_TOTAL_IDLE1_FRAMES = 15;
static const int S_TOTAL_IDLE2_FRAMES = 41;
static const int S_TOTAL_IDLE3_FRAMES = 51;
static const int S_TOTAL_CLIMB_LADDER_FRAMES = 10;
static const int S_TOTAL_DEATH_FRAMES = 10;
static const int S_TOTAL_JUMP_FRAMES = 11;
static const int S_TOTAL_WHIP_FRAMES = 61;
static const int S_TOTAL_BOMB_FRAMES = 10;
static const int S_TOTAL_SPRINT_FRAMES = 10;
static const int S_TOTAL_SPRINT_JUMP_FRAMES = 10;
static const int S_TOTAL_LOOT_GRAB_FRAMES = 31;
static const int S_TOTAL_ON_LEDGE_FRAMES = 61;
static const int S_TOTAL_BATSCARE_FRAMES = 31;
static const int S_TOTAL_LANDING_FRAMES = 11;
static const int S_TOTAL_SNAKE_BITE_FRAMES = 11;

/// Map Borders
static const int MAP_LEFT_BORDER = 25;
static const int MAP_RIGHT_BORDER = 2580;
static const int MAP_BOTTOM_BORDER = 1730;
};