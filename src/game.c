#include "functions.h"

//Level 1 test code
EnvItem envItems[] = {
    {{0, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{150, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{200, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{300, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{400, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{450, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{600, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{600, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{750, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{800, SCREEN_HEIGHT - 75, 75, 100}, RED, true, 1, false},
    {{825, SCREEN_HEIGHT - 100 - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{1100, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{1135, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{1300, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{1450, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{1515, SCREEN_HEIGHT - PLYR_SZ_Y, PLYR_SZ_X, PLYR_SZ_Y}, WHITE, false, 10, false}
};

/**
 * PlayGame
 * -------
 * 
 * Contains the loop for the game itself
 * This function is called after the start menu
 * function has ended it's loop
 * 
 * @param none - no params currently
 * 
 * @return none - nothing to return;
 */

void PlayGame() {
    bool game_state = true; // change to false when game has complete

        //Initialize everything
    Entity player = { 0 };
    CreatePlayer(&player);

    Camera2D camera = { 0 };
    CreateCamera(&camera, &player, SCREEN_WIDTH, SCREEN_HEIGHT);

    Texture2D bg_textures [] = {
        LoadTexture("assets/background/parallax-mountain-bg.png"),
        LoadTexture("assets/background/parallax-mountain-montain-far.png"),
        LoadTexture("assets/background/parallax-mountain-mountains.png"),
        LoadTexture("assets/background/parallax-mountain-trees.png"),
        LoadTexture("assets/background/parallax-mountain-foreground-trees.png")
    };

    Texture2D playerTex = LoadTexture("assets/player/player-newest.png");


    Texture2D grass = LoadTexture("assets/map/grass.png");

    Texture2D house = LoadTexture("assets/map/house.png");

    int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);
    float deltaTime = 0;

    while(game_state)  {

        if (IsKeyPressed(KEY_ESCAPE)) return;
        if (IsKeyPressed(KEY_R)) ResetGame(&player, envItems, envItemsLength);
        
        // update delta time, player, and camera
        deltaTime = GetFrameTime();
        UpdateCameraCenter(&camera, &player, envItems, SCREEN_WIDTH, SCREEN_HEIGHT);

        // begin drawing the window
        BeginDrawing();

            // reset the window and set background to white
            ClearBackground(WHITE);
            DrawBackground(bg_textures, player, camera); // draw this outside of the camera to prevent issues with how the image is drawn

            // used to initialize 2d mode with the camera 
            BeginMode2D(camera);
                // draw the environment items
                DrawTextureEx(house, (Vector2){1350,SCREEN_HEIGHT-house.height*5}, 0.0f,5.0f,WHITE);
                for (int i = 0; i < envItemsLength; i ++) {
                   //if (!envItems[i].used) DrawRectangleRec(envItems[i].hitBox, envItems[i].color);
                   if (envItems[i].id == 0) DrawTextureEx(grass, (Vector2){envItems[i].hitBox.x, envItems[i].hitBox.y}, 0.0f, 1.0f, WHITE);
                   else if (!envItems[i].used) DrawRectangleRec(envItems[i].hitBox, envItems[i].color);
                }


                if (DEBUG) DrawRectangleRec(player.hitBox, player.color);
                DrawTextureEx(playerTex, (Vector2){player.hitBox.x, player.hitBox.y}, 0.0f,1.0f, WHITE);
                UpdatePlayer(&player, envItems, envItemsLength, deltaTime);

                


            EndMode2D();

            //This is simply for debugging
            //Todo: replace with helper function for debug uses
            if (DEBUG) Debug(&player);
            
        EndDrawing();

    }
        UnloadTexture(grass);
        UnloadTexture(playerTex);
        UnloadTexture(house);
        UnloadTextures(bg_textures);

}

/**
 * DrawBackground
 * --------------
 * 
 * Draws the images and handles the
 * animation of the background to generate
 * a 2d parallax.
 * 
 * @param bg_textures - array of 2d textures used in the background
 * @param player - used to provide new positions for the background scrolling
 * @param camera - used to provide a stationary position for background images that shouldn't move
 * 
 * @return none - returns nothing
 */
void DrawBackground(Texture2D *textures, Entity player, Camera2D camera) {
 
    // these are the rates that each layer will move
    float scrollingBack  = 0.05f,
          scrollingMid   = 0.1f,
          scrollingFront = 0.5f;
    
    // Draw the sky
    DrawTextureEx(textures[0], (Vector2){0, 0}, 0.0f, 6.0f, WHITE);

    // Draw the farthest mountain
    DrawTextureEx(textures[1], (Vector2){scrollingBack * -player.hitBox.x, 125}, 0.0f, 4.0f, WHITE);
    DrawTextureEx(textures[1], (Vector2){textures[1].width * 2 + scrollingBack * -player.hitBox.x + 20, 125}, 0.0f, 4.0f, WHITE);

    // Draw the closets mountains
    DrawTextureEx(textures[2], (Vector2){scrollingMid * -player.hitBox.x, 125}, 0.0f, 4.0f, WHITE);
    DrawTextureEx(textures[2], (Vector2){textures[2].width * 2 + scrollingMid * -player.hitBox.x, 125}, 0.0f, 4.0f, WHITE);


    // Draw the farthest trees
    DrawTextureEx(textures[3], (Vector2){scrollingFront * -player.hitBox.x, -50}, 0.0f, 5.0f, WHITE);
    DrawTextureEx(textures[3], (Vector2){textures[3].width * 2 + scrollingFront * -player.hitBox.x, -50}, 0.0f, 5.0f, WHITE);

    // Draw the foreground trees, these move with the map itself so they don't change at a separate rate
    DrawTextureEx(textures[4], (Vector2){0, -SCREEN_HEIGHT/4}, 0.0f, 6.0f, WHITE);
    DrawTextureEx(textures[4], (Vector2){textures[4].width * 4 , -SCREEN_HEIGHT/2}, 0.0f, 6.0f, WHITE);
    DrawTextureEx(textures[4], (Vector2){textures[4].width * 8 , -SCREEN_HEIGHT/2}, 0.0f, 6.0f, WHITE);

}
