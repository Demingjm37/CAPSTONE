/**
 * Textures.c
 */

#include "../inc/functions.h"

/**
 * textures.c contains the functions for drawing textures to the screen
 * there are also helper routines in this file to assist with loading
 * and unloading the textures used
 * 
 * @author Joseph Deming
 * @version 0.0.2
 */



/**
 * UnloadTextures
 * --------------
 * 
 * Used for unloading arrays of textures
 * 
 * @param textures - array of textures
 * @param length   - length of the array
 * 
 * @return none
 */
void UnloadTextures(Texture2D *textures, int length) {
    for (int i = 0; i < length; i++) {
        UnloadTexture(textures[i]);
    }
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
          scrollingFront = 0.3f;
    
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

/**
 * DrawMap
 * -------
 * 
 * Draws all of the textures to their corresponding 
 * envItem
 * 
 * @param textures - array of textures that will be drawn
 * @param envItems - array of envItems that are rendered
 * 
 * @return none
 */
void DrawMap(Texture2D *textures, EnvItem *envItems, int envItemsLength) {

    /**
     * Textures:
     *  0 - Grass platform block
     *  1 - House Goal Point
     */

    DrawTextureEx(textures[1], (Vector2){1350,SCREEN_HEIGHT-textures[1].height*5}, 0.0f,5.0f,WHITE);
    for (int i = 0; i < envItemsLength; i ++) {
        switch (envItems[i].id) {
            case 0:
                DrawTextureEx(textures[0], (Vector2){envItems[i].hitBox.x, envItems[i].hitBox.y}, 0.0f, 1.0f, WHITE);
                break;
            default:
                if (DEBUG && !envItems[i].used) DrawRectangleRec(envItems[i].hitBox, envItems[i].color);
                break;
        }
    }
    DrawTextureEx(textures[2], (Vector2){envItems[1].hitBox.x+envItems[0].hitBox.width, envItems[0].hitBox.y-textures[2].height*3}, 0.0f, 3.0f, WHITE);
}

/**
 * DrawPlayer
 * ----------
 * 
 * Draws the players texture
 * 
 * Later this will be reworked to
 * handle sprites and changing sprite frames
 * based on players velocity.
 */
void DrawPlayer(Entity *player) {
    if (DEBUG) DrawRectangleRec(player->hitBox, player->color);
    //DrawTextureEx(texture, (Vector2){player.hitBox.x, player.hitBox.y}, 0.0f,4.0f, WHITE);

    //todo implement player sprite
}