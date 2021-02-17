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

    return 0;
}