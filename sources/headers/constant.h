
#define CONSTANT

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "../../SDL/include/SDL.h"
#include <time.h>

#define TRUE 1
#define FALSE 0

// Map items
enum
{
    TERRAIN, FOREST, RIVER, EXPLOSION, CHARACTER0, CHARACTER1, CHARACTER2, CHARACTER3
};

// Settings
// Do not change the number of players, WIP
#define NBR_PLAYERS 2
#define NBR_TOUR_MAX 10

// Size of the Map
#define BLOCK_SIZE 32
#define NBR_BLOCK_X 28
#define NBR_BLOCK_Y 16
// Size of the game
#define SCREEN_WIDTH NBR_BLOCK_X * BLOCK_SIZE
#define SCREEN_HEIGHT NBR_BLOCK_Y * BLOCK_SIZE
// Offset is for the text at the bottom, size of the window (game + text)
#define WINDOW_OFFSET 32
#define REAL_SCREEN_WIDTH NBR_BLOCK_X * BLOCK_SIZE + WINDOW_OFFSET
#define REAL_SCREEN_HEIGHT NBR_BLOCK_Y * BLOCK_SIZE + WINDOW_OFFSET


// Actions
#define STAY 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


typedef struct PawnStruct
{
    int id;
    char type;
    int player_id;
    int hasEnemyFlag;
    int max_displacement;
    int displacement_left;
    int alive;
    SDL_Rect position;
} Pawn;


typedef struct PlayerStruct
{
    int id;
    int alive;
    int *pawns_ptr;
} Player;



typedef struct GameStruct
{
    Player players[2];
    int turn;
    int playerTurn; // Which player is playing


} Game;

