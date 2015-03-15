


#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// Window Size
#define WORLD_WINDOW_WIDTH 550
#define WORLD_WINDOW_HEIGHT 380
#define MAGNIFICATION 2

#define DOWN 0
#define UP 1
#define NONE -1
#define LEFT 2
#define RIGHT 3

static bool FAST_PC = false;
static int GAME_SPEED = (FAST_PC ? 2 : 1);

#define PLAYER_SPEED ((int)(4/GAME_SPEED))
#define FALLING_SPEED ((int)4/GAME_SPEED)
static float CLIMBING_SPEED = (float)(3 / (float)GAME_SPEED);
static float JUMP_SPEED = (float)(3 / (float)GAME_SPEED);
#define JUMP_MAX_HEIGHT 22
#define ANIMATION_REFRESH_INTERVAL ((int)2*GAME_SPEED)

#define CLIMBING_ANIMATION_REFRESH_INTERVAL ((int)4*GAME_SPEED)

#define PLAYER_ANIMATION_0_WIDTH 11
#define PLAYER_ANIMATION_0_HEIGHT 42
#define PLAYER_ANIMATION_0_LOOKING_LEFT_COMPENSATION 4


#define GROUND_Y 140
#define TUNNEL_FLOOR_Y 32

static int WAIT_TIME = (FAST_PC ? 15 : 25);
//static int WAIT_TIME = 2000;

#define SPACE_BAR 32


#endif