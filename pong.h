#ifndef _PONG_H_
#define _PONG_H_

#include <stdbool.h>

#include "ball.h"
#include "paddle.h"

// mod music data
extern const uint8_t _binary_music_hit_start[];
extern const uint8_t _binary_music_hit_end[];
extern const uint8_t _binary_music_hit_size[];

typedef enum { TITLE, PLAYING, GAME_OVER } GAME_STATE;
extern GAME_STATE game_state;
extern uint8_t win_paddle;

extern void pong_init();
extern void pong_start_game(bool is_left_cpu, bool is_right_cpu);
extern void pong_fixed_update();
extern void pong_draw();

extern void pong_main();

#endif /* _PONG_H_ */