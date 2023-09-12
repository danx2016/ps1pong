#include <stdint.h>
#include <string.h>
#include <libetc.h>

#include "gfx.h"
#include "music_player.h"
#include "sfx.h"
#include "controller.h"
#include "pong.h"

GAME_STATE game_state;

// win paddle: 1 or 2
uint8_t win_paddle;

static Ball ball;
static Paddle paddle_left;
static Paddle paddle_right;

static uint32_t wait_frames_count;

void pong_init()
{
    gfx_init();
    controller_init();
    pong_start_game(true, true);
    game_state = TITLE;
    win_paddle = 0;
    // init audio
    music_play_init();
    VSyncCallback(music_play_next_sample);
    sfx_init();    
}

void pong_start_game(bool is_left_cpu, bool is_right_cpu)
{
    ball = ball_init(BALL_DIAMETER, gfx_screen_width / 2, gfx_screen_height / 2);
    paddle_left = paddle_init(PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_WIDTH * 2, gfx_screen_height / 2, 0, is_left_cpu);
    paddle_right = paddle_init(PADDLE_WIDTH, PADDLE_HEIGHT, gfx_screen_width - PADDLE_WIDTH * 2 - 1, gfx_screen_height / 2, 1, is_right_cpu);
    game_state = PLAYING;
}

static void check_game_over()
{
    // check game over
    if (ball.position.x < -BALL_DIAMETER)
    {
        wait_frames_count = 60;
        game_state = GAME_OVER;
        win_paddle = 2;
        music_play_pause();
    }
    if (ball.position.x > gfx_screen_width + BALL_DIAMETER)
    {
        wait_frames_count = 60;
        game_state = GAME_OVER;
        win_paddle = 1;
        music_play_pause();
    }
}

void pong_fixed_update()
{
    if (wait_frames_count > 0)
    {
        wait_frames_count--;
        return;
    }

    switch (game_state)
    {
        case TITLE:
            if (controller_is_action_pressed(0, ANY))
            {
                pong_start_game(false, true);
            }
            break;

        case PLAYING:
            paddle_fixed_update(&paddle_left, &ball);
            paddle_fixed_update(&paddle_right, &ball);
            ball_fixed_update(&ball, &paddle_left, &paddle_right);
            check_game_over();
            break;

        case GAME_OVER:
            if (controller_is_action_pressed(0, ANY))
            {
                pong_start_game(true, true);
                wait_frames_count = 60;
                game_state = TITLE;
                win_paddle = 0;
                music_play_resume();
            }
            break;
    }
}

static void pong_draw_paddles()
{
    uint16_t plx = paddle_left.position.x - paddle_left.width / 2;
    uint16_t ply = paddle_left.position.y - paddle_left.height / 2;
    uint16_t plw = paddle_left.width;
    uint16_t plh = paddle_left.height;
    gfx_fill_rect(plx, ply, plw, plh);

    for (int i = 0; i < paddle_left.walls_count; i++)
    {
        uint16_t lx = plx - 12 + 2 * i;
        gfx_draw_line(lx, 0, lx, gfx_screen_height);
    }

    uint16_t prx = paddle_right.position.x - paddle_right.width / 2;
    uint16_t pry = paddle_right.position.y - paddle_right.height / 2;
    uint16_t prw = paddle_right.width;
    uint16_t prh = paddle_right.height;
    gfx_fill_rect(prx, pry, prw, prh);

    for (int i = 0; i < paddle_right.walls_count; i++)
    {
        uint16_t lx = prx + prw - 1 + 12 - 2 * i;
        gfx_draw_line(lx, 0, lx, gfx_screen_height);
    }

}

static void pong_draw_ball()
{
    uint16_t bx = (uint16_t) ball.position.x - ball.diameter / 2;
    uint16_t by = (uint16_t) ball.position.y - ball.diameter / 2;
    uint16_t bw = (uint16_t) ball.diameter;
    uint16_t bh = (uint16_t) ball.diameter;
    gfx_fill_rect(bx, by, bw, bh);
}

static void pong_draw_playing() 
{
    pong_draw_paddles();
    pong_draw_ball();
}

void pong_draw()
{
    uint16_t lx = gfx_screen_width / 2;
    gfx_draw_line(lx, 0, lx, gfx_screen_height);

    switch (game_state)
    {
        case TITLE:
            gfx_draw_text("\n\n\n\n\n\n\n\n\n\n\n\n\n              PONG 6 WALLS\n\n\n      PRESS BUTTON TO START VS CPU\n");
            pong_draw_paddles();
            break;

        case PLAYING:
            pong_draw_playing();
            break;

        case GAME_OVER:
            uint8_t win_message_0[] = "\n\n\n\n\n\n\n\n\n\n\n\n\n                ";
            uint8_t win_message_1[] = "\n";
            uint8_t win_message[128];
            strcpy(win_message, win_message_0);
            strcat(win_message, win_paddle == 1 ? "YOU WIN!" : "YOU LOSE!");
            strcat(win_message, win_message_1);
            gfx_draw_text(win_message);
            pong_draw_paddles();
            break;
    }

}

void pong_main()
{
    pong_init();

    // game loop
    while (true)
    {
        pong_fixed_update();
        pong_draw();
        gfx_swap_buffers();
    }
}