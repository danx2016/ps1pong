#include <libmath.h>
#include <rand.h>

#include "gfx.h"
#include "controller.h"
#include "paddle.h"

Paddle paddle_init(uint16_t width, uint16_t height, float px, float py, uint8_t controller_id, bool is_cpu)
{
    Paddle paddle;
    paddle.width = width;
    paddle.height = height;
    paddle.position = vec2_init(px, py);
    paddle.velocity = vec2_init(0, 0);
    paddle.vertical_speed = PADDLE_INITIAL_VERTICAL_SPEED;
    paddle.controller_id = controller_id;
    paddle.is_cpu = is_cpu;
    paddle.walls_count = 6;
    return paddle;
}

static bool separate_ball_paddle(Ball* ball, Paddle* paddle)
{
    bool ch;
    bool cv;
    do
    {
        Vec2 dir = vec2_sub(&ball->position, &paddle->position);
        ch = fabs(dir.x) < PADDLE_WIDTH / 2 + BALL_RADIUS / 2;
        cv = fabs(dir.y) < PADDLE_HEIGHT / 2 + BALL_RADIUS / 2;
        if (ch && cv)
        {
            dir = vec2_normalize(&dir);
            dir = vec2_scale(vec2_length(&ball->velocity), &dir);
            ball->position = vec2_add(&ball->position, &dir);
        }
    } 
    while (ch && cv);
    
}

static void move_paddle(Paddle *paddle)
{
    paddle->position = vec2_add(&paddle->position, &paddle->velocity);
    
    // constraint keep paddle inside screen area
    if (paddle->position.y < PADDLE_HEIGHT / 2)
    { 
        paddle->position.y = PADDLE_HEIGHT / 2;
    }
    if (paddle->position.y > gfx_screen_height - PADDLE_HEIGHT / 2)
    {
        paddle->position.y = gfx_screen_height - PADDLE_HEIGHT / 2;
    }
}

static void fixed_update_cpu(Paddle *paddle, Ball *ball)
{
    float dy = ball->position.y - paddle->position.y;
    float r = rand() / 32768.0;
    float sy = r * paddle->vertical_speed;
    if (fabs(dy) < sy)
    {
        sy = fabs(dy);
    }
    paddle->velocity.y = 0;
    if (dy > 0)
    {
        paddle->velocity.y = sy;
    }
    else if (dy < 0)
    {
        paddle->velocity.y = -sy;
    }
    move_paddle(paddle);
}

static void fixed_update_player(Paddle *paddle)
{
    paddle->velocity.y = 0;
    if (controller_is_action_pressed(paddle->controller_id, MOVE_UP))
    {
        paddle->velocity.y = -paddle->vertical_speed;
    }
    if (controller_is_action_pressed(paddle->controller_id, MOVE_DOWN))
    {
        paddle->velocity.y = paddle->vertical_speed;
    }
    move_paddle(paddle);
}

void paddle_fixed_update(Paddle *paddle, Ball *ball)
{
    if (paddle->is_cpu)
    {
        fixed_update_cpu(paddle, ball);
    }
    else
    {
        fixed_update_player(paddle);
    }
    separate_ball_paddle(ball, paddle);
    paddle->vertical_speed *= PADDLE_VERTICAL_SPEED_INCREASE_RATE;
    if (paddle->vertical_speed > PADDLE_MAX_VERTICAL_SPEED)
    {
        paddle->vertical_speed = PADDLE_MAX_VERTICAL_SPEED;
    }
}