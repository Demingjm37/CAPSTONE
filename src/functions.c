/**
 * functions.c
 */

#include "../inc/functions.h"

/**
 * This file holds all of the functions for initializing the
 * player entity and camera. As well as functions for collision detection,
 * and eventually drawing textures.
 * 
 * @author Joseph Deming
 * @author Hunter Craig
 * 
 * @version 0.0.1-alpha
 */

static int SPEEDMULT = 0;

/**
 * UpdatePlayer
 * ------------
 * 
 * Updates the players position in relation to environment items.
 * Collision detection is performed here, and player stats are modified here
 * as well when collision occurs with a powerup item or obstacle
 * 
 * @param player - pointer to the entity being updated
 * @param envItems - array of environment items used for collision 
 * @param envItemsLength - length of the array of environment items
 * @param deltaTime - change in time between each frame update
 * 
 * @return none - returns nothing
 */

void UpdatePlayer(Entity *player, EnvItem *envItems, int envItemsLength, float deltaTime) {

    Vector2 contact_point, contact_normal;
    float contact_time = 0;

    Vector2 mouse = (Vector2) {GetMouseX(), GetMouseY()};

    Ray2 ray;
    ray.position = (Vector2) {20.0f,20.0f};
    ray.direction = Vector2Subtract(mouse, ray.position);

    Rectangle rtest = {500,500,50,50};
    DrawRectangleRec(rtest, RED);


    DrawLineV(ray.position, ray.direction, GREEN);

    for (int i = 0; i < envItemsLength; i++) {
        if (CheckCollisionRayRec(ray, rtest, &contact_point, &contact_normal, &contact_time)) {
            if (contact_time >= 0.0f && contact_time < 1.0f) DrawCircle(contact_point.x, contact_point.y, 5, BLUE);
                DrawText(TextFormat("contact points x %d y %d", contact_point.x, contact_point.y), 500,500, 20, BLACK);
        } 
    }
    

    // float horizontal = IsKeyDown(KEY_D) -  IsKeyDown(KEY_A);
    // int initJumpVelocity = sqrtf(2 * GRAVITY * player->jumpHeight);

    // player->speed = (IsKeyDown(KEY_LEFT_SHIFT) ? DFLT_SPRNT_SPD : DFLT_SPD) * SPEEDMULT;

    // player->velocity.x += horizontal * player->speed * deltaTime;
    // player->velocity.y += GRAVITY * deltaTime;

    // float velocity = sqrtf(powf(player->velocity.x, 2) + powf(player->velocity.y, 2));

    // if (velocity > MAX_VELOCITY) {
    //     Vector2 temp = player->velocity;
    //     player->velocity = Vector2Scale(temp, (MAX_VELOCITY / velocity));
    // }

    // player->velocity.x /= (1 * FRICTION * deltaTime);
    // player->velocity.y /= (1 * FRICTION * deltaTime);

    // Vector2 contact_normal, contact_point;
    // float contact_time = 0;

    // for (int i = 0; i < envItemsLength; i++) {
    //     if (!envItems[i].blocking) continue;
    //     if (CheckDynamicCollisionRec(*player, envItems[i], &contact_point, &contact_normal, &contact_time, deltaTime)) {
    //         player->hitBox.y = envItems[i].hitBox.y - player->hitBox.height;
    //         player->velocity.y = 0;
    //         player->canJump = true;
    //         break;
    //     }
    // }

    // if (player->canJump && IsKeyDown(KEY_W)) { player->velocity.y = -initJumpVelocity; player->canJump = false; }

    // if (isnan(player->velocity.x)) player->velocity.x = 0;
    // if (isnan(player->velocity.y)) player->velocity.y = 0;

    // player->hitBox.x += player->velocity.x;
    // player->hitBox.y += player->velocity.y;

    for (int i = 0; i < envItemsLength; i++) {
        if (envItems[i].id == 0) continue;
        if (!envItems[i].used && CheckCollisionRecs(player->hitBox, envItems[i].hitBox)) 
            switch(envItems[i].id) {
                case 4:
                    continue;
                case 5:
                    envItems[i].used = true;
                    player->jumpHeight = DFLT_JMP_HT;
                    SPEEDMULT = 2; //double the players speed
                    continue;
                case 6:
                    envItems[i].used = true;
                    SPEEDMULT = 1;
                    player->jumpHeight = MAX_JMP_HT;
                    continue;
                case 7:
                    continue;
                case 8:
                    envItems[i].used = true;
                    player->coins++;
                    continue;
                case 9:
                    continue;
                case 10:
                    ResetGame(player, envItems, envItemsLength);
                    continue;
                default:
                    break;
            };
    }

    // TODO: replace hard coded numbers with #defines for world borders


    // check if player is at the world border
    if (player->hitBox.x < 0) { player->hitBox.x = 0; player->velocity.x = 0; }
    if (player->hitBox.x > 1550) { player->hitBox.x = 1550; player->velocity.x = 0; }

    //Check if player has fallen through pit/world, reset game
    if (player->hitBox.y > 1300) { ResetGame(player, envItems, envItemsLength); };
    if (player->hitBox.y <= 0) player->hitBox.y = 0;
}

/**
 * UpdateCameraCenter
 * ------------------
 * 
 * Updates the camera position and offset relative to the players position
 * and position of environment items.
 * 
 * Determines max/min between the players position, environment item position, and screen dimensions
 * to calculate the proper offset for the camera.
 * 
 * @param camera - pointer to the 2D camera being updated
 * @param player - pointer to the entity the camera should focus on
 * @param envItems - array of environment items
 * @param envItemsLength - length of the array of environment items
 * @param width  - screen width
 * @param height - screen height
 * 
 * @return none - returns nothing
 */

void UpdateCameraCenter(Camera2D *camera, Entity *player, EnvItem *envItems, int width, int height) {
    // reset camera position
    camera->target = (Vector2){player->hitBox.x, player->hitBox.y};
    camera->offset = (Vector2){width / 2, height / 2};

    float minX = 0, minY = 150, maxX = MAX_CMA_X, maxY = MAX_CMA_Y;

    EnvItem temp = envItems[0]; //first element in the map will be used for setting the bounds of the camera
    // set min and max 
    minX = fminf(temp.hitBox.x, minX); // sets the smaller of the two to minX
    maxX = fmaxf(temp.hitBox.x, maxX); // sets the larger of the two to maxX

    Vector2 max = GetWorldToScreen2D((Vector2){maxX, maxY}, *camera); // sets the maximum position for the camera
    Vector2 min = GetWorldToScreen2D((Vector2){minX, minY}, *camera); // sets the minimum position for the camera

    if (max.x < width) camera->offset.x = width - (max.x - width / 2); // if max.x is less than width set the x offset to w - (max - w/2)
    if (min.x > 0) camera->offset.x = width / 2 - min.x; // if minimum pos exceeds 0 then set offest to (w / 2) - min

    camera->offset.y = height / 2 - min.y; // nothing special for the y-offset. (h / 2) - minY
}

/**
 * CreatePlayer
 * ------------
 * 
 * Initializes the player entity with default stats
 * 
 * @param player - pointer to the entity being initialized as player
 * 
 * @return none - returns nothing
 */

void CreatePlayer(Entity *player) {
    player->hitBox = (Rectangle) {10, SCREEN_HEIGHT - 350, PLYR_SZ, PLYR_SZ};
    player->velocity = (Vector2) {0,0};
    player->color       = PINK;
    player->speed       = DFLT_SPD;
    player->jumpHeight  = DFLT_JMP_HT;
    player->canJump     = YES;
    player->coins       = 0;
    player->grounded    = false;
    player->blocking.right  = false;
    player->blocking.left   = false;
    player->blocking.top    = false;
    player->blocking.bottom = false;
}

/**
 * CreateCamera
 * ------------
 * 
 * Initializes the 2D camera used to
 * track the player as it moves through the
 * game.
 * 
 * @param camera - pointer to 2D camera that is being initialized
 * @param player - pointer to player entity that the camera should focus on
 * @param width  - width of the grame window
 * @param height - height of the game window
 * 
 * @return none - returns nothing
 */

void CreateCamera(Camera2D *camera, Entity *player, int width, int height) {
    camera->target = (Vector2){player->hitBox.x, player->hitBox.y};
    camera->offset = (Vector2){width / 2, height / 2};
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
}

void ResetGame(Entity *player, EnvItem *envItems, int envItemsLength) {
    player->hitBox = (Rectangle) {10, SCREEN_HEIGHT - 50, PLYR_SZ, PLYR_SZ};
    player->velocity = (Vector2) {0,0};
    player->speed = DFLT_SPD;
    SPEEDMULT = 1;
    player->canJump = false;
    player->jumpHeight = DFLT_JMP_HT;
    player->coins = 0;

    for (int i = 0; i < envItemsLength; i++) if (envItems[i].used) envItems[i].used = false;
}

/**
 * Debug
 * -----
 * 
 * Displays general data for debugging purposes
 * 
 * @param player - pointer to the player entity being monitored
 * 
 * @return none - returns nothing
 */
void Debug(Entity *player) {
    DrawText(TextFormat("Player X velocity: %f", player->velocity.x), 0, 0, 20, BLACK);
    DrawText(TextFormat("Player y velocity: %f", player->velocity.y), 0,20, 20, BLACK);
    DrawText(TextFormat("Player Coordinates: X = %0.0f,  Y = %.0f", player->hitBox.x, player->hitBox.y), 0,40, 20, BLACK);
    DrawText(TextFormat("Coins: %d", player->coins), 0, 100, 20, BLACK);
    DrawText(TextFormat("FPS: %d", GetFPS()), 0, 140, 20, LIME);
    DrawText(TextFormat("Players Jump Height: %.0f", player->jumpHeight), 0, 200, 20, BLACK);
    DrawText(TextFormat("Players speed: %.0f", player->speed), 0, 240, 20, BLACK);
}