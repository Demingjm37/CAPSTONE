#ifndef FUCNTIONS_H
#define FUNCTIONS_H

#include "raylib.h"
#include "math.h"
#include "stdint.h"
#include "stdio.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define GRAVITY 9.8f
#define MAX_JMP_HT 4.0f
#define DFLT_JMP_HT 2.0f
#define DFLT_SPD 2.0f
#define DFLT_SPRNT_SPD 4.0f
#define PLYR_SZ 50.0f
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

void UpdatePlayer(Entity *player);
void CreatePlayer(Entity *player);

#endif