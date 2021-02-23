#ifndef FUCNTIONS_H
#define FUNCTIONS_H

#include "raylib.h"
#include "raymath.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

//physics constants
#define GRAVITY 9.80665f
#define MAX_VELOCITY 200.0f
#define FRICTION 0.5f

//player constants
#define MAX_JMP_HT 6
#define DFLT_JMP_HT 3
#define DFLT_SPD 1.5f
#define DFLT_SPRNT_SPD 4.0f
#define PLYR_SZ_X 32.0f
#define PLYR_SZ_Y 64.0f

// envItems constants
#define ITEM_SZ 25.0f
#define PLTFRM_SZ 150.f

//camera constants
#define MAX_CMA_X 1600
#define MAX_CMA_Y 5000

#define DEBUG true //set to true for debug info

//for fun
#define YES 1

typedef struct Sprite {
    Texture2D texture;
    Vector2 frameSize; // dimensions for each frame
    int maxFrame;   // 
    int framesWide; // number of columns in the sprite frame
    Vector2 origin; // starting point for drawing the sprite
    int frame;      // 
} Sprite;

typedef struct Entity {
    Rectangle hitBox;
    Vector2 velocity;
    Color color;
    bool canJump; //used to prevent double jumps
    float speed;  //for setting the players speed
    float jumpHeight; //for setting the players jump height
    int coins;
} Entity;

typedef struct EnvItem {
    Rectangle hitBox;
    Color color;
    bool blocking;
    short id;
    bool used;
} EnvItem;

/**
 * Functions.c
 */
void UpdatePlayer(Entity *player, EnvItem *envItems, int envItemsLength, float deltaTime);
void UpdateCameraCenter(Camera2D *camera, Entity *player, EnvItem *envItems, int width, int height);
void CreatePlayer(Entity *player);
void CreateCamera(Camera2D *camera, Entity *player, int width, int height);
void ResetGame(Entity *player, EnvItem *envItems, int envItemsLength);
void Debug(Entity *player);

/**
 * Textures.c
 */
Texture2D* LoadTextures();
void UnloadTextures(Texture2D *textures);

/**
 * Helper.c
 */
Vector2 CalculateCollisionDistance(Entity player, EnvItem target);
void ResolveCollision(Entity *player, EnvItem target, float deltaTime);
bool PredictCollision(Entity player, EnvItem target);
Vector2 GetRectCenter(Rectangle rec);
Vector2 Vector2Abs(Vector2 v);

/**
 * Game.c
 */
void PlayGame();
void DrawBackground(Texture2D *bg_textures, Entity player, Camera2D camera);

/**
 * Environtment Items IDs:
 *  This is a list of all IDs for future reference when checking collision
 *  
 *  0 - basic platform 
 *  1 - raised platform
 *  2 - ice platform (implement in future: refactor physics)
 *  3 - fire
 *  4 - spikes/barbedwire
 *  5 - speed boost
 *  6 - jump boost
 *  7 - heart
 *  8 - coin
 *  9 - reserved
 * 10 - goal post
 */

#endif