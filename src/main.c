/**
 * main.c
 */

#include "../inc/functions.h"

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



    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Walk Home");

    SetTargetFPS(30);
    
    // Calculate length of items array 


    // Main game loop
    // Loop runs as long as the window
    // isn't set to close.
    while(!WindowShouldClose()) {
        // StartMenu()

        /**
         * This function contains the loop for the game
         * it handles all player updates and texture rendering 
         * for each level.
         * when this function returns the game is complete
         * and the following function CreditMenu() will
         * be called to draw the credit screen
         */
        PlayGame();

        // CreditMenu()
    }

    CloseWindow(); // close window and opengl

    return 0;
}