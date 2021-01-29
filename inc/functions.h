#ifndef FUCNTIONS_H
#define FUNCTIONS_H

#include "raylib.h"
#include "raymath.h"
#include "stdint.h"
#include "stdio.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

//physics constants
#define GRAVITY 9.80665f
#define MAX_VELOCITY 200.0f
#define FRICTION 1.0f

//player constants
#define MAX_JMP_HT 5
#define DFLT_JMP_HT 2
#define DFLT_SPD 1.5f
#define DFLT_SPRNT_SPD 4.0f
#define PLYR_SZ 50.0f

//for fun
#define YES 1


typedef struct Entity {
    Rectangle hitBox;
    Vector2 velocity;
    Color color;
    bool canJump; //used to prevent double jumps
    float speed;  //for setting the players speed
    float jumpHeight; //for setting the players jump height
} Entity;

typedef struct EnvItem {
    Rectangle hitBox;
    Color color;
    bool blocking;
} EnvItem;

void UpdatePlayer(Entity *player, EnvItem *envItems, int envItemsLength, float deltaTime);
void CreatePlayer(Entity *player);

#endif