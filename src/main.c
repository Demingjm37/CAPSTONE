#include "../inc/functions.h"

// current map for testing and placing
EnvItem envItems [] = {
    {{0, SCREEN_HEIGHT, 3800, 150 }, BROWN, true}
};

/**
 * main
 * ----
 * 
 * Main method for the game. This function
 * makes calls to other game functions inside the main loop
 * to make the game function as intended.
 * 
 * @param  none - no parameters
 * 
 * @return none - returns nothing
 */

int main() {

    //Initialize everything
    Entity player = { 0 };
    CreatePlayer(&player);

    Camera2D camera = { 0 };
    CreateCamera(&camera, &player, SCREEN_WIDTH, SCREEN_HEIGHT);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Our game");

    SetTargetFPS(60);
    
    // Calculate length of items array 
    int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);
    float deltaTime = 0;

    // Main game loop
    // Loop runs as long as the window
    // isn't set to close.
    while(!WindowShouldClose()) {

        // update delta time, player, and camera
        deltaTime = GetFrameTime();
        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);
        UpdateCameraCenter(&camera, &player, envItems, SCREEN_WIDTH, SCREEN_HEIGHT);

        // begin drawing the window
        BeginDrawing();
            // reset the window and set background to white
            ClearBackground(WHITE);

            // used to initialize 2d mode with the camera 
            BeginMode2D(camera);
                // draw the players hitbox
                // this will later be replaced with textures
                // and eventually replaced with animated sprites
                DrawRectangleRec(player.hitBox, player.color);
                
                // Loop through map array and draw each items hitbox
                for (int i = 0; i < envItemsLength; i ++) {
                    DrawRectangleRec(envItems[i].hitBox, envItems[i].color);
                }
            EndMode2D();

            //This is simply for debugging
            //Todo: replace with helper function for debug uses
            DrawText(TextFormat("Player X velocity: %f", player.velocity.x), 0, 0, 20, BLACK);
        EndDrawing();
    }

    return 0;
}