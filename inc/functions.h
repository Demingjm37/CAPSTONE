#ifndef FUCNTIONS_H
#define FUNCTIONS_H

#include "raylib.h"
#include "raymath.h"
#include "stdint.h"
#include "stdio.h"

//general purpose macros

//screen dimensions
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

//physics constants
#define GRAVITY 9.80665f
#define MAX_VELOCITY 10.0f
#define FRICTION 1.0f

//player constants
#define MAX_JMP_HT 5
#define DFLT_JMP_HT 2
#define DFLT_SPD 1.5f
#define DFLT_SPRNT_SPD 4.0f
#define PLYR_SZ 50.0f
#define ITEM_SZ 25.0f

//camera constants
#define MAX_CMA_X 1600
#define MAX_CMA_Y 5000

#define DEBUG true //set to true for debug info

//for fun
#define YES 1

typedef struct Blocking {
    bool right;
    bool left;
    bool top;
    bool bottom;
} Blocking;

typedef struct Entity {
    Rectangle hitBox;
    Vector2 velocity;
    Color color;
    Blocking blocking;
    bool canJump; //used to prevent double jumps
    bool grounded;
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

typedef struct Ray2 {
    Vector2 position;
    Vector2 direction;
} Ray2;



//Functions.c
void UpdatePlayer(Entity *player, EnvItem *envItems, int envItemsLength, float deltaTime);
void UpdateCameraCenter(Camera2D *camera, Entity *player, EnvItem *envItems, int width, int height);
void CreatePlayer(Entity *player);
void CreateCamera(Camera2D *camera, Entity *player, int width, int height);
void ResetGame(Entity *player, EnvItem *envItems, int envItemsLength);
void Debug(Entity *player);

//Textures.c
Texture2D* LoadTextures();

//Helper.c
bool myCheckCollisionPointRec(Vector2 point, Rectangle rec);
bool CheckCollisionRayRec(Ray2 ray, Rectangle hitBox, Vector2 *contact_point, Vector2 *contact_normal, float *time);
bool CheckDynamicCollisionRec(Entity player, EnvItem target, Vector2 *contact_point, Vector2 *contact_normal, float *time, float deltaTime);
bool ResolveDynamicCollisionRec(Entity *player, EnvItem target, float deltaTime);
void swap(float *x, float *y);
Vector2 Vector2Abs(Vector2 v);

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