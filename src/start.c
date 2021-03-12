/**
 * start.c
 */

#include "../inc/functions.h"

/**
 * Start.c runs the start menu loop
 * this loop will draw textures and handle
 * checking the start buttons interaction
 *
 *  @author Joseph Deming
 *  @version 0.0.1
 */

/**
 * StartGame()
 * -----------
 * 
 * This function handles loading and unloading textures
 * Making necessary function calls to draw textures
 * and handle the start button
 * 
 * @param none
 * @return bool - true or false if player is trying to close the game
 */
bool StartGame() {

    
    Texture2D title = LoadTexture("assets/menu/The-Walk-Home-test.png");

    Texture2D textures [] = {
        LoadTexture("assets/background/parallax-mountain-bg.png"),
        LoadTexture("assets/background/parallax-mountain-montain-far.png"),
        LoadTexture("assets/background/parallax-mountain-mountains.png"),
        LoadTexture("assets/background/parallax-mountain-trees.png"),
        LoadTexture("assets/background/parallax-mountain-foreground-trees.png"),
        LoadTexture("assets/map/grass.png")
    };

    ScrollState sc_state  = {0};
    Rectangle titlehitBox = (Rectangle){SCREEN_WIDTH/4,SCREEN_HEIGHT/2 - title.height,title.width, title.height};

    Button start_button = {
        LoadTexture("assets/menu/start_sheet.png"),
        (Rectangle){SCREEN_WIDTH/2 - start_button.texture.width*2,SCREEN_HEIGHT/2 + start_button.texture.height*2,200,100},
        false
    };

    Button quit_button = {
        LoadTexture("assets/menu/quit_sheet.png"),
        (Rectangle){SCREEN_WIDTH/2 - quit_button.texture.width*2, SCREEN_HEIGHT/2 + start_button.texture.height*5, 200,100},
        false
    };

    bool start_state = false;
    bool escaped = false;
    
    int texturesLength = LENGTH(textures);

    while (!start_state) { // while the game isn't supposed to start
        start_state = ButtonHandler(&start_button);
        if (ButtonHandler(&quit_button)) {start_state = true; escaped = true;}

        BeginDrawing();
        {
            ClearBackground(WHITE);
            DrawStartScreen(textures, texturesLength, &sc_state);
            DrawButton(&start_button);
            DrawButton(&quit_button);
            DrawTitle(title, titlehitBox);
            
        } EndDrawing();
    }

    UnloadTextures(textures, texturesLength);
    UnloadTexture(start_button.texture);
    UnloadTexture(title);
    return escaped;
}