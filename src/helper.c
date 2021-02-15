#include "../inc/functions.h"

/**
 * CheckCollisionRayRec
 * --------------------
 * 
 * Determines if collision has occured between the direction of the given ray
 * and the hitbox being checked.
 * 
 * @param ray - 2D ray being used to check collision
 * @param hitBox - hitbox of the item being that's being checked
 * @param contact_point  - this is the point where collision occured between the ray and hitbox
 * @param contact_normal - this is the vector perpindicular to the point of collision
 * @param time - time to the point of contact
 * 
 * @return true if collision has occured
 */
bool CheckCollisionRayRec(Ray2 ray, Rectangle hitBox, Vector2 *contact_point, Vector2 *contact_normal, float *time) {
    
    Vector2 t_near = Vector2Divide(Vector2Subtract((Vector2) {hitBox.x, hitBox.y}, ray.position), ray.direction);                                   //calculate the vector between t_near_x and t_near_y for collision
    Vector2 t_far  = Vector2Divide(Vector2Subtract((Vector2) {hitBox.x + hitBox.width, hitBox.y + hitBox.height}, ray.position), ray.direction);    //calculate the vector between t_far_x and t_far_y for collision

    if (t_near.x > t_far.x) swap(&t_near.x, &t_far.x); // if near_x is greater than far_x then swap positions 
    if (t_near.y > t_far.y) swap(&t_near.y, &t_far.y); // do the same

    if (t_near.x > t_far.y || t_near.y > t_far.x) return false; // if near_x or near_y exceed eachother then collision is impossible/hasn't occurred

    float t_hit_near = fmaxf(t_near.x, t_near.y); // get the max distance t between near_x and near_y
    float t_hit_far  = fminf(t_far.x, t_far.y);   // get the min distance t between far_x and far_y

    if (t_hit_far < 0) return false; // if the hit is less than 0 then collision hasn't occurred

    *contact_point = Vector2Add(ray.position, Vector2Scale(ray.direction, t_hit_near)); // set the contact point. This is vector point where collision between the ray and hitbox has occurred
    
    if (t_near.x > t_near.y) {                                          // set the normal vector. 
        if (ray.direction.x < 0) *contact_normal = (Vector2) {1,0};     // This is the vector perpindicular to the point of collision, 
        else *contact_normal = (Vector2) {-1,0};                            // this will be used for collision resolution
    } else if (t_near.x < t_near.y) {
        if (ray.direction.y < 0) *contact_normal = (Vector2) {0,1};
        else *contact_normal = (Vector2) {0,-1};
    }
    
    return true; // if the process has made it this far then collision has occurred
}

bool CheckDynamicCollisionRec(Entity player, EnvItem target, Vector2 *contact_point, Vector2 *contact_normal, float *contact_time, float deltaTime) {
    if (!player.velocity.x && !player.velocity.y) return false;

    // expand the environment items hitbox to use later for collision resolution
    Rectangle expanded_target;
    expanded_target.x = target.hitBox.x - player.hitBox.width / 2;
    expanded_target.y = target.hitBox.y - player.hitBox.height / 2;
    expanded_target.width = target.hitBox.width + player.hitBox.width;
    expanded_target.height = target.hitBox.height + player.hitBox.height;


    Ray2 playerRay;
    playerRay.position  = (Vector2) {player.hitBox.x + player.hitBox.width / 2, player.hitBox.y + player.hitBox.height / 2};
    playerRay.direction = Vector2Scale(player.velocity, deltaTime);

    if (DEBUG) DrawLineV(playerRay.position, playerRay.direction, GREEN);

    if (CheckCollisionRayRec(playerRay, expanded_target, contact_point, contact_normal, contact_time))
        return (*contact_time >= 0.0f && *contact_time < 1.0f);
    
    return false;
}

//NOT FINISHED DONT USE
bool ResolveDynamicCollisionRec(Entity *player, EnvItem target, float deltaTime) {
/*     Vector2 contact_point, contact_normal;
    float contact_time = 0.0f;


    if (contact_normal.x < 0) { player->hitBox.x = target.hitBox.x - player->hitBox.width;player->velocity.x = 0; }
    if (contact_normal.x > 0) { player->hitBox.x = target.hitBox.x + target.hitBox.width; player->velocity.x = 0; }
    if (contact_normal.y < 0) { player->hitBox.y = target.hitBox.y - player->hitBox.height; player->canJump = true; player->velocity.y = 0;}
    if (contact_normal.y > 0) { player->hitBox.y = target.hitBox.y + target.hitBox.height; player->velocity.y = 0;}

    player->canJump = true; */

    return false;
}

void swap(float *x, float *y) {
    float temp = *x;
    *x = *y;
    *y = temp;
}

Vector2 Vector2Abs(Vector2 v) {
    Vector2 temp = (Vector2) {abs(v.x), abs(v.y) };
    return temp;
}
