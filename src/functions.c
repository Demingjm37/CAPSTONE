#include "../inc/functions.h"



float speedMult = 1.0f;

void UpdatePlayer(Entity *player, EnvItem *envItems, int envItemsLength, float deltaTime) {

    float horizontal = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    int initJumpVelocity = sqrtf(2 * GRAVITY * player->jumpHeight);

    player->speed = ((IsKeyDown(KEY_LEFT_SHIFT)) ?  DFLT_SPRNT_SPD : DFLT_SPD) * speedMult;

    //Change players velocity in respect to keys pressed, gravity, and change in time
    player->velocity.x += horizontal * player->speed * deltaTime;
    player->velocity.y += GRAVITY * deltaTime;

    // velocity = sqrt(vx^2 + vy^2)
    float velocity = sqrtf(powf(player->velocity.x, 2) + powf(player->velocity.y, 2));

    // check if new velocity exceeds max velocity
    if (velocity > MAX_VELOCITY) {
        Vector2 temp = player->velocity;
        player->velocity = Vector2Scale(temp, (MAX_VELOCITY / velocity));
    }

    // Collision detection below
    // Check if the players current position
    // is colliding with any environment item
    // before updating the players hitbox
    // and redrawing.

    bool hitPlatform = false;
    short platformNumber = 0;

    for (int i = 0; i < envItemsLength; i++) {
        // Check of current item is passable and check if player hitbox is hitting item hitbox
        if (envItems[i].blocking && CheckCollisionRecs(envItems[i].hitBox, player->hitBox)) {
            hitPlatform = YES;
            platformNumber = i;
        }
    }

    // collision has occured, adjust players position accordingly
    if (hitPlatform) {
        player->velocity.y = 0;                                                         // standing on a platform. set velocity y to 0
        player->hitBox.y = envItems[platformNumber].hitBox.y - player->hitBox.height;   // set the players y position to the platform height + the size of the player
        player->canJump = true;                                                         // player is on the ground so they should be allowed to jump
    } else {
        player->velocity.y = player->velocity.y / (1 + FRICTION * deltaTime);           // player is not colliding, v_new = v_old / ( 1 friction_const * dt)
        player->hitBox.y += player->velocity.y;                                         // increase players y position with the players new y velocity
        player->canJump = false;                                       
    }

    // determine if jumping
    if (player->canJump && (IsKeyDown(KEY_W))) player->velocity.y = -initJumpVelocity; // player is trying to jump, change their velocity.

    // now update the players x position
    // TODO: replace hard coded numbers with #defines for world borders

    // check if player is at the world border
    if (player->hitBox.x < 0) { player->hitBox.x = 0; player->velocity.x = 0; }
    if (player->hitBox.x > 3700) { player->hitBox.x = 3700; player->velocity.x = 0; }

    // now update the players hitbox
    player->velocity.x = player->velocity.x / ( 1 + FRICTION * deltaTime);
    player->hitBox.x += player->velocity.x;
}

void UpdateCameraCenter(Camera2D *camera, Entity *player, EnvItem *envItems, int width, int height) {
    // reset camera position
    camera->target = (Vector2){player->hitBox.x, player->hitBox.y};
    camera->offset = (Vector2){width / 2, height / 2};

    float minX = 0, minY = 150, maxX = 3700, maxY = 5000;

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

void CreatePlayer(Entity *player) {
    player->hitBox = (Rectangle) {10, SCREEN_HEIGHT - 350, PLYR_SZ, PLYR_SZ};
    player->velocity = (Vector2) {0,0};
    player->color = GREEN;
    player->speed = DFLT_SPD;
    player->jumpHeight = DFLT_JMP_HT;
    player->canJump = YES;
}

void CreateCamera(Camera2D *camera, Entity *player, int width, int height) {
    camera->target = (Vector2){player->hitBox.x, player->hitBox.y};
    camera->offset = (Vector2){width / 2, height / 2};
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
}