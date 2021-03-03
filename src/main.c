/**
 * main.c
 */

#include "../inc/functions.h"

/**
 * main.c contains the main method for the game.
 * This file initializes the screen and pushes
 * all necessary functions on to the state manager
 * stack and destroys as needed
 * 
 * @author Joseph Deming
 * @author Hunter Craig
 * 
 * @version 0.1.4
 */


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

    SetTargetFPS(60);

    // Main game loop
    // Loop runs as long as the window
    // isn't set to close.
    while(!WindowShouldClose()) {
        //Todo: implement state manager stack
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
        PlayGame2();

        // CreditMenu()
    }

    CloseWindow(); // tell opengl to close the window

    return 0;
}