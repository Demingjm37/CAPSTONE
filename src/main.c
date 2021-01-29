#include "../inc/functions.h"

// current map for testing and placing
EnvItem envItems [] = {
    {{0, SCREEN_HEIGHT - 300 , 3800, 50}, BROWN, true}
};

int main() {

    Entity player = { 0 };
    CreatePlayer(&player);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Our game");

    int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);
    float deltaTime = 0;

    while(!WindowShouldClose()) {

        ClearBackground(WHITE);

        deltaTime = GetFrameTime();
        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);

        BeginDrawing();
            DrawRectangleRec(player.hitBox, player.color);
            DrawText(TextFormat("Player X velocity: %f", player.velocity.x), 0, 0, 20, BLACK);

            for (int i = 0; i < envItemsLength; i ++) {
                DrawRectangleRec(envItems[i].hitBox, envItems[i].color);
            }

        EndDrawing();
    }

    return 0;
}