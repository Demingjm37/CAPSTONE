/**
 * main.c
 */

#include "../inc/functions.h"

// current map for testing and placing
/* EnvItem envItems [] = {
    * {{0, SCREEN_HEIGHT, 3800, 150 }, BROWN, true, 0, false}, //don't change this
    * {{250, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GREEN, false, 5, false}, //speed boost
    * {{100, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, BLUE, false, 6, false}, //jump boost
    * {{150, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, RED, false, 7, false},  //heart
    * {{200, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false}, //coin
    * {{3500, SCREEN_HEIGHT - 50, 100, 200}, BLACK, false, 10, false} //goal post
* };
*/ 

//Level 1 test code
EnvItem envItems[] = {
    {{0, SCREEN_HEIGHT, 150, 150}, BROWN, true, 0, false},
    {{150, SCREEN_HEIGHT, 150, 150}, BROWN, true, 0, false},
    {{200, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{300, SCREEN_HEIGHT, 150, 150}, BROWN, true, 0, false},
    {{400, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{450, SCREEN_HEIGHT, 150, 150}, BROWN, true, 0, false},
    {{600, SCREEN_HEIGHT, 150, 150}, BROWN, true, 0, false},
    {{600, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{750, SCREEN_HEIGHT, 150, 150}, BROWN, true, 0, false},
    {{800, SCREEN_HEIGHT - 75, 75, 100}, RED, true, 1, false},
    {{825, SCREEN_HEIGHT - 100 - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{1100, SCREEN_HEIGHT, 100, 150}, BROWN, true, 0, false},
    {{1135, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{1300, SCREEN_HEIGHT, 300, 150}, BROWN, true, 0, false},
    {{1500, SCREEN_HEIGHT - 50, 100, 200}, BLACK, false, 10, false}
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
        if (IsKeyPressed(KEY_R)) ResetGame(&player, envItems, envItemsLength);
        // update delta time, player, and camera
        deltaTime = GetFrameTime();
        UpdateCameraCenter(&camera, &player, envItems, SCREEN_WIDTH, SCREEN_HEIGHT);

        // begin drawing the window
        BeginDrawing();

            // reset the window and set background to white
            ClearBackground(WHITE);

            // used to initialize 2d mode with the camera 
            BeginMode2D(camera);
                // draw the environment items
                for (int i = 0; i < envItemsLength; i ++) {
                   if (!envItems[i].used) DrawRectangleRec(envItems[i].hitBox, envItems[i].color);
                }

                //update and draw the player
                UpdatePlayer(&player, envItems, envItemsLength, deltaTime);
                if (DEBUG) DrawRectangleRec(player.hitBox, player.color);

            EndMode2D();

            //This is simply for debugging
            //Todo: replace with helper function for debug uses
            if (DEBUG) Debug(&player);
            
        EndDrawing();
    }

    return 0;
}