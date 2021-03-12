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

    Texture2D buttonTexture = LoadTexture("assets/menu/start_sheet.png");

    Texture2D textures [] = {
        LoadTexture("assets/background/parallax-mountain-bg.png"),
        LoadTexture("assets/background/parallax-mountain-montain-far.png"),
        LoadTexture("assets/background/parallax-mountain-mountains.png"),
        LoadTexture("assets/background/parallax-mountain-trees.png"),
        LoadTexture("assets/background/parallax-mountain-foreground-trees.png"),
        LoadTexture("assets/map/grass.png")
    };

    ScrollState sc_state = {0};
    Vector2 mousePoint = (Vector2){0,0};
    Rectangle buttonhitBox = (Rectangle){SCREEN_WIDTH/2 - buttonTexture.width*2,SCREEN_HEIGHT/2 + buttonTexture.height*2,200,100};
    bool button_state = false;
    bool start_state = false;
    bool escaped = false;
    
    int texturesLength = LENGTH(textures);

    while (!start_state) { // while the game isn't supposed to start
        if (IsKeyPressed(KEY_X)) { escaped = true; break; }
        mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, buttonhitBox)) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) 
                button_state = true;
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                start_state = true;
        }

        BeginDrawing();
        {
            ClearBackground(WHITE);
            DrawStartScreen(textures, texturesLength, &sc_state);
            DrawStartButton(buttonTexture, buttonhitBox, button_state);
            
        } EndDrawing();
    }

    UnloadTextures(textures, texturesLength);
    UnloadTexture(buttonTexture);
    return escaped;
}