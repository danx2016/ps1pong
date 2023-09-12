#include <libmath.h>
#include <rand.h>

#include "vec2.h"
#include "gfx.h"
#include "sfx.h"
#include "ball.h"

Ball ball_init(uint16_t radius, float px, float py)
{
    Ball ball;
    ball.radius = radius;
    ball.position = vec2_init(px, py);
    ball.velocity = vec2_init(-1, 0);
    ball.speed = BALL_INITIAL_SPEED;
    return ball;
}

static bool handle_collision_ball_paddle(Ball* ball, Paddle* paddle) {
    Vec2 ball_old = ball->position;
    Vec2 ball_new = vec2_add(&ball->position, &ball->velocity);

    uint16_t w = paddle->width;
    uint16_t h = paddle->height;
    float x = paddle->position.x - w / 2;
    float y = paddle->position.y - h / 2;
    
    Vec2 dif = vec2_sub(&ball_new, &ball_old);
    if (dif.x > 0) {
        float minkowski_x = x - ball->radius / 2.0;
        float penetration = ball_new.x - minkowski_x;
        float ratio = penetration / dif.x;
        float collisionY = ball_new.y - ratio * dif.y;
        if (penetration > 0 && ball_old.x <= minkowski_x && collisionY >= y - ball->radius / 2 && collisionY <= y + h + ball->radius / 2) {
            ball->position.x = minkowski_x - 1; 
            ball->position.y = collisionY;
            ball->velocity.x = -fabs(ball->velocity.x);
            return true;
        }
    }
    if (dif.x < 0) {
        float minkowski_x = x + w + ball->radius / 2.0;
        float penetration = minkowski_x - ball_new.x;
        float ratio = penetration / dif.x;
        float collisionY = ball_new.y + ratio * dif.y;
        if (penetration > 0 && ball_old.x >= minkowski_x && collisionY >= y - ball->radius / 2 && collisionY <= y + h + ball->radius / 2) 
        {
            ball->position.x = minkowski_x + 1; 
            ball->position.y = collisionY;
            ball->velocity.x = fabs(ball->velocity.x);
            return true;
        }        
    }
    if (dif.y > 0) {
        float minkowski_y = y - ball->radius / 2.0;
        float penetration = ball_new.y - minkowski_y;
        float ratio = penetration / dif.y;
        float collisionX = ball_new.x - ratio * dif.x;
        if (penetration > 0 && ball_old.y <= minkowski_y && collisionX >= x - ball->radius / 2 && collisionX <= x + w + ball->radius / 2) 
        {
            ball->position.x = collisionX; 
            ball->position.y = minkowski_y - 1;
            ball->velocity.y = -fabs(ball->velocity.y);
            return true;
        }
    }
    if (dif.y < 0) {
        float minkowski_y = y + h + ball->radius / 2.0;
        float penetration = minkowski_y - ball_new.y;
        float ratio = penetration / dif.y;
        float collisionX = ball_new.x + ratio * dif.x;
        if (penetration > 0 && ball_old.y >= minkowski_y && collisionX >= x - ball->radius / 2 && collisionX <= x + w + ball->radius / 2) 
        {
            ball->position.x = collisionX; 
            ball->position.y = minkowski_y + 1;
            ball->velocity.y = fabs(ball->velocity.y);
            return true;
        }                
    }   
    return false;
}

static void change_ball_direction_little_randomly(Ball *ball)
{
    float vx = fabs(ball->velocity.x);
    float vy = fabs(ball->velocity.y);
    float vy_sign = ball->velocity.y >= 0 ? 1 : -1;
    float r = rand() / 32768.0;
    ball->velocity.y = ball->velocity.y + vx * (r - 0.5);
    if (fabs(ball->velocity.y) > vx)
    {
        ball->velocity.y = vy_sign * vx;
    }
}

void ball_fixed_update(Ball *ball, Paddle *paddle_left, Paddle *paddle_right)
{
    if (handle_collision_ball_paddle(ball, paddle_left))
    {
        sfx_play(SOUND_PADDLE_HIT);
        change_ball_direction_little_randomly(ball);
    }

    if (handle_collision_ball_paddle(ball, paddle_right))
    {
        sfx_play(SOUND_PADDLE_HIT);
        change_ball_direction_little_randomly(ball);
    }
   
    float wall_left_x = paddle_left->position.x - PADDLE_WIDTH / 2 - 2 + BALL_RADIUS / 2 - (10 - 2 * paddle_left->walls_count);
    if (ball->position.x <= wall_left_x && ball->velocity.x < 0 && paddle_left->walls_count > 0) 
    {
        paddle_left->walls_count--;
        ball->velocity.x = fabs(ball->velocity.x);
        sfx_play(SOUND_PADDLE_WALL);
    }

    float wall_right_x = paddle_right->position.x + PADDLE_WIDTH / 2 + 2 - BALL_RADIUS / 2 + (12 - 2 * paddle_right->walls_count);
    if (ball->position.x >= wall_right_x && ball->velocity.x > 0 && paddle_right->walls_count > 0) 
    {
        paddle_right->walls_count--;
        ball->velocity.x = -(ball->velocity.x);
        sfx_play(SOUND_PADDLE_WALL);
    }

    ball->position = vec2_add(&ball->position, &ball->velocity);

    if (ball->position.y < 0) 
    {
        ball->velocity.y = fabs(ball->velocity.y);
        sfx_play(SOUND_VERTICAL);
    }
    if (ball->position.y >= gfx_screen_height) 
    {
        ball->velocity.y = -fabs(ball->velocity.y);
        sfx_play(SOUND_VERTICAL);
    }

    ball->speed *= BALL_SPEED_INCREASE_RATE;
    if (ball->speed > BALL_SPEED_MAX)
    {
        ball->speed = BALL_SPEED_MAX;
    }
    ball->velocity = vec2_normalize(&ball->velocity);
    ball->velocity = vec2_scale(ball->speed, &ball->velocity);
}
