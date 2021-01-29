#include "../inc/functions.h"



float speedMult = 1.0f;

void UpdatePlayer(Entity *player, EnvItem *envItems, int envItemsLength, float deltaTime) {

    bool isGrounded = false;

    float horizontal = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    int initJumpVelocity = sqrtf(2 * GRAVITY * player->jumpHeight);

    player->speed = ((IsKeyDown(KEY_LEFT_SHIFT)) ?  DFLT_SPRNT_SPD : DFLT_SPD) * speedMult;

    //Change players velocity in respect to keys pressed, gravity, and change in time
    player->velocity.x += horizontal * player->speed * deltaTime;
    player->velocity.y += GRAVITY * deltaTime;

    //Determine if player can jump
    if (isGrounded) {               // Player is currently on the ground
        player->velocity.y = 0;     // Velocity is 0 so player doesn't move up or down
        player->canJump = true;     // and is allowed to jump
    } else {                        
        player->canJump = false;    // Player is not on the ground, set to false
                                    // so they can't jump while mid air
    }

    // velocity = sqrt(vx^2 + vy^2)
    float velocity = sqrtf(powf(player->velocity.x, 2) + powf(player->velocity.y, 2));

    // check of new velocity exceeds max velocity
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
        player->hitBox.y += player->velocity.y;                                         // increase players y with the players new y velocity
    }

    // determine if jumping
    if (player->canJump && (IsKeyDown(KEY_W))) player->velocity.y = -initJumpVelocity; // player is trying to jump, change their velocity.

    // now update the players x position
    // TODO: replace hard coded numbers with #defines for world borders

    // check if player is at the world border
    if (player->hitBox.x < 0) { player->hitBox.x = 0; player->velocity.x = 0; }
    if (player->hitBox.x > 3770) { player->hitBox.x = 3770; player->velocity.x = 0; }

    // now update the players hitbox
    player->velocity.x = player->velocity.x / ( 1 + FRICTION * deltaTime);
    player->hitBox.x += player->velocity.x;
}

void CreatePlayer(Entity *player) {
    //todo: move to create player function
    player->hitBox = (Rectangle) {10, SCREEN_HEIGHT - 350, PLYR_SZ, PLYR_SZ};
    player->velocity = (Vector2) {0,0};
    player->color = GREEN;
    player->speed = DFLT_SPD;
    player->jumpHeight = DFLT_JMP_HT;
    player->canJump = YES;
}