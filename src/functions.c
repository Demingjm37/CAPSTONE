#include "../inc/functions.h"

void UpdatePlayer(Entity *player) {

    //todo: implement the physics and movement
    
}

void CreatePlayer(Entity *player) {
    //todo: move to create player function
    player->hitBox = (Rectangle) {10, SCREEN_HEIGHT -350, PLYR_SZ, PLYR_SZ};
    player->velocity = (Vector2) {0,0};
    player->color = GREEN;
    player->speed = DFLT_SPD;
    player->jumpHeight = DFLT_JMP_HT;
    player->canJump = YES;
}