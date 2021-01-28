#include "../inc/functions.h"

int main() {

    Entity player = { 0 };
    CreatePlayer(&player);

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