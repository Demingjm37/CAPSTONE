/**
 * Helper.c
 */

#include "../inc/functions.h"

/**
 * helper.c contains the helper routines for checking
 * and resolving collision detection, as well as other
 * various routines for performing repetitive calculations
 * 
 * @author Joseph Deming
 * @version 0.0.2
 */



/**
 * CalculateCollisionDistance
 * --------------------------
 * 
 * Given that the players hitbox, and the environment items hitbox
 * are both axis aligned and colliding.
 * This function will calculate and return a vector2 containing
 * the distance between their x and y
 * 
 * @param player - player entity that is colliding
 * @param target - environment item that the player is colliding with
 * 
 * @return Vector2 containing the distance between the player and targets x and y
 */
Vector2 CalculateCollisionDistance(Entity player, EnvItem target) {
    Vector2 distance = {0};

    if (player.hitBox.x < target.hitBox.x)      distance.x = target.hitBox.x - (player.hitBox.x + player.hitBox.width);
    else if (player.hitBox.x > target.hitBox.x) distance.x = player.hitBox.x - (target.hitBox.x + target.hitBox.width);
    
    if (player.hitBox.y < target.hitBox.y)      distance.y = target.hitBox.y - (player.hitBox.y + player.hitBox.height);
    else if (player.hitBox.y > target.hitBox.y) distance.y = player.hitBox.y - (target.hitBox.y + target.hitBox.height);
    
    return distance;
}

/**
 * ResolveCollision
 * ----------------
 * 
 * As the name says, this functions purpose
 * is for resolveing collision.
 * 
 * It determines which axis the player was colliding with first
 * to help with adjusting the players position and velocity.
 * 
 * @param player - the player entity that needs correction
 * @param target - the envItem that the player was colliding with
 * 
 * @return none - returns nothing
 */
void ResolveCollision(Entity *player, EnvItem target, float deltaTime) {

    Vector2 playerCenter = GetRectCenter(player->hitBox);
    Vector2 targetCenter = GetRectCenter(target.hitBox);
    Vector2 distance = Vector2Subtract(targetCenter, playerCenter);

    if (DEBUG) DrawLineV(playerCenter, targetCenter, GREEN);

    // check if the y position is greater than the x position
    if (powf(distance.y, 2) > powf(distance.x, 2)) {
        
        if (distance.y > 0) {
            // vector is pointing down
            player->canJump = true;
            player->hitBox.y = target.hitBox.y - player->hitBox.height;
            player->velocity.y = 0;

            if (DEBUG) DrawText("distance.y > 0", 500,500,20,BLACK);
        } else {
            // vector is pointing up
            if (DEBUG) DrawText("distance.y < 0", 500,500,20,BLACK);

        }
    } else {
        if (distance.x > 0) {
            // vector is pointing right
            player->hitBox.x = target.hitBox.x - player->hitBox.width - 1;
            player->velocity.x = 0;
            if (DEBUG) DrawText("distance.y > 0", 500,500,20,BLACK);
        } else {
            // vector is pointing left
            player->hitBox.x = target.hitBox.x + target.hitBox.width;
            player->velocity.x = 0;
                if (DEBUG) DrawText("distance.x > 0", 500,500,20,BLACK);
        }
    }
}

/**
 * GetRectCenter
 * -------------
 * 
 * Taking a rectangle as input,
 * this function returns a vector 
 * containing the x and y  of the center point
 * of that rectangle.
 * 
 * @param rec - the rectangle that you want the center of
 * 
 * @return returns a Vector2 containing the center 
 *          points of the rectangle
 */
Vector2 GetRectCenter(Rectangle rec) {
    Vector2 temp;
    temp.x = rec.x + rec.width  / 2;
    temp.y = rec.y + rec.height / 2;

    return temp;
}

/**
 * Vector2Abs
 * ----------
 * 
 * Returns the absolute value of 
 * the vector.
 * 
 * @param v - input vector to be converted
 * 
 * @return Returns the absolute value of the vectors x and y
 */
Vector2 Vector2Abs(Vector2 v) {
    Vector2 temp;
    temp.x = abs(v.x);
    temp.y = abs(v.y);

    return temp;
}

/**
 * PredictCollision
 * ----------------
 * 
 * Using the players velocity, collision is predicted
 * by determining where calculating the players 'next' position
 * in the frame. This still uses basic AABB collision detection
 * 
 * @param player - the player 
 * @param target - the envItem that the player may be colliding with
 * 
 * @return true or false depending on if collision 'will' occurr
 */
bool PredictCollision(Entity player, EnvItem target) {
    Rectangle futureHitBox = (Rectangle) {player.hitBox.x + player.velocity.x, player.hitBox.y + player.velocity.y, player.hitBox.width, player.hitBox.height};
    return CheckCollisionRecs(futureHitBox, target.hitBox);
}