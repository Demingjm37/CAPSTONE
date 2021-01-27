#include "../inc/functions.h"

int main() {

    //todo: move to create player function
    Entity player = { 0 };
    player.hitBox = (Rectangle) {10, SCREEN_HEIGHT -350, PLYR_SZ, PLYR_SZ};
    player.velocity = (Vector2) {0,0};
    player.color = GREEN;
    player.speed = DFLT_SPD;
    player.jumpHeight = DFLT_JMP_HT;
    player.canJump = YES;

    EnvItem platform = { 0 };
    platform.hitBox = (Rectangle) {0, SCREEN_HEIGHT - 300 , 3800, 50};
    platform.color = BROWN;
    platform.blocking = YES;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Our game");

    while(!WindowShouldClose()) {

        ClearBackground(WHITE);

        BeginDrawing();
            DrawRectangleRec(player.hitBox, player.color);
            DrawRectangleRec(platform.hitBox, platform.color);
        EndDrawing();
    }

    return 0;
}