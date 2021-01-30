#include "../inc/functions.h"

// current map for testing and placing
EnvItem envItems [] = {
    {{0, SCREEN_HEIGHT, 3800, 150 }, BROWN, true}
};

int main() {

    Entity player = { 0 };
    CreatePlayer(&player);

    Camera2D camera = { 0 };
    CreateCamera(&camera, &player, SCREEN_WIDTH, SCREEN_HEIGHT);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Our game");

    SetTargetFPS(60);
    
    int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);
    float deltaTime = 0;

    while(!WindowShouldClose()) {

        deltaTime = GetFrameTime();
        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);
        UpdateCameraCenter(&camera, &player, envItems, SCREEN_WIDTH, SCREEN_HEIGHT);

        BeginDrawing();
            ClearBackground(WHITE);

            BeginMode2D(camera);
                DrawRectangleRec(player.hitBox, player.color);
                
                for (int i = 0; i < envItemsLength; i ++) {
                    DrawRectangleRec(envItems[i].hitBox, envItems[i].color);
                }
            EndMode2D();
            DrawText(TextFormat("Player X velocity: %f", player.velocity.x), 0, 0, 20, BLACK);
        EndDrawing();
    }

    return 0;
}