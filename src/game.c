/**
 * Game.c
 */

#include "../inc/functions.h"

/**
 * game.c holds the game functions for each level.
 * Each function will contain the textures and function calls necessary to 
 * load, play, and complete each level.
 * 
 * @author Joseph Deming
 * @version 0.1.0
 */




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

int PlayGame() {
    bool game_state = true; // change to false when game has complete

    //Initialize everything

    Texture2D bg_textures [] = {
        LoadTexture("assets/background/parallax-mountain-bg.png"),
        LoadTexture("assets/background/parallax-mountain-montain-far.png"),
        LoadTexture("assets/background/parallax-mountain-mountains.png"),
        LoadTexture("assets/background/parallax-mountain-trees.png"),
        LoadTexture("assets/background/parallax-mountain-foreground-trees.png")
    };

    Texture2D map_textures [] = {
        LoadTexture("assets/map/grass.png"),
        LoadTexture("assets/map/house.png"),
        LoadTexture("assets/map/grass_top.png")
    };

    Texture2D playerSprite = LoadTexture("assets/player/player-sprite.png");

    Entity player = { 0 };
    CreatePlayer(&player, playerSprite);

    Camera2D camera = { 0 };
    CreateCamera(&camera, &player, SCREEN_WIDTH, SCREEN_HEIGHT);

    int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);
    int bg_length = sizeof(bg_textures) / sizeof(bg_textures[0]);
    int map_textures_length = sizeof(map_textures) / sizeof(map_textures[0]);

    float deltaTime = 0;
    bool escaped = false;

    while(game_state)  {

        if (IsKeyPressed(KEY_ESCAPE)) {escaped = true; game_state = false;}
        if (IsKeyPressed(KEY_R)) ResetGame(&player, envItems, envItemsLength);
        
        // update delta time, player, and camera
        deltaTime = GetFrameTime();
        UpdateCameraCenter(&camera, &player, envItems, SCREEN_WIDTH, SCREEN_HEIGHT);

        // begin drawing the window
        BeginDrawing(); {

            // reset the window and set background to white
            ClearBackground(WHITE);

            DrawBackground(bg_textures, player, camera); // draw this outside of the camera to prevent issues with how the image is drawn

            // used to initialize 2d mode with the camera 
            BeginMode2D(camera); {

                DrawMap(map_textures, envItems, envItemsLength);
                UpdatePlayer(&player, envItems, envItemsLength, deltaTime, &game_state);
                DrawPlayer(&player, deltaTime);

            } EndMode2D();

            //This is simply for debugging
            //Todo: replace with helper function for debug uses
            if (DEBUG) Debug(&player);
            
        } EndDrawing();
    }

        UnloadTexture(playerSprite);
        UnloadTextures(bg_textures, bg_length);
        UnloadTextures(map_textures, map_textures_length);

        if (escaped) 
            return 1;
        
        return 0;
}

int PlayGame2() {
    bool game_state = true; // change to false when game has complete

    //Initialize everything

    Texture2D bg_textures [] = {
        LoadTexture("assets/background/parallax-mountain-bg.png"),
        LoadTexture("assets/background/parallax-mountain-montain-far.png"),
        LoadTexture("assets/background/parallax-mountain-mountains.png"),
        LoadTexture("assets/background/parallax-mountain-trees.png"),
        LoadTexture("assets/background/parallax-mountain-foreground-trees.png")
    };

    Texture2D map_textures [] = {
        LoadTexture("assets/map/grass.png"),
        LoadTexture("assets/map/house.png"),
        LoadTexture("assets/map/grass_top.png")
    };

    Texture2D playerSprite = LoadTexture("assets/player/player-sprite.png");

    Entity player = { 0 };
    CreatePlayer(&player, playerSprite);

    Camera2D camera = { 0 };
    CreateCamera(&camera, &player, SCREEN_WIDTH, SCREEN_HEIGHT);

    int envItemsLength = sizeof(level2) / sizeof(level2[0]);
    int bg_length = sizeof(bg_textures) / sizeof(bg_textures[0]);
    int map_textures_length = sizeof(map_textures) / sizeof(map_textures[0]);

    float deltaTime = 0;
    bool escaped = false;

    while(game_state)  {

        if (IsKeyPressed(KEY_ESCAPE)) {escaped = true; game_state = false;}
        if (IsKeyPressed(KEY_R)) ResetGame(&player, level2, envItemsLength);
        
        // update delta time, player, and camera
        deltaTime = GetFrameTime();
        UpdateCameraCenter(&camera, &player, level2, SCREEN_WIDTH, SCREEN_HEIGHT);

        // begin drawing the window
        BeginDrawing(); {

            // reset the window and set background to white
            ClearBackground(WHITE);

            DrawBackground(bg_textures, player, camera); // draw this outside of the camera to prevent issues with how the image is drawn

            // used to initialize 2d mode with the camera 
            BeginMode2D(camera); {

                DrawMap(map_textures, level2, envItemsLength);
                UpdatePlayer(&player, level2, envItemsLength, deltaTime, &game_state);
                DrawPlayer(&player, deltaTime);

            } EndMode2D();

            //This is simply for debugging
            //Todo: replace with helper function for debug uses
            if (DEBUG) Debug(&player);
            
        } EndDrawing();
    }

        UnloadTexture(playerSprite);
        UnloadTextures(bg_textures, bg_length);
        UnloadTextures(map_textures, map_textures_length);

        if (escaped) 
            return 1;
        
        return 0;
}