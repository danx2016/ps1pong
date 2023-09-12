#ifndef _PADDLE_H_
#define _PADDLE_H_

#include <stdint.h>
#include <stdbool.h>

#include "vec2.h"

#define PADDLE_WIDTH 8
#define PADDLE_HEIGHT 32

#define PADDLE_MAX_VERTICAL_SPEED 10.0
#define PADDLE_INITIAL_VERTICAL_SPEED 3.0
#define PADDLE_VERTICAL_SPEED_INCREASE_RATE 1.002

typedef struct Paddle Paddle;

struct Paddle
{
    uint16_t width;
    uint16_t height;
    Vec2 position; // center of box
    Vec2 velocity;
    float vertical_speed; 
    uint8_t controller_id;
    bool is_cpu;
    uint8_t walls_count;
};

typedef struct Ball Ball;

extern Paddle paddle_init(uint16_t width, uint16_t height, float px, float py, uint8_t controller_id, bool isCpu);
extern void paddle_fixed_update(Paddle *paddle, Ball *ball);

#include "ball.h"

#endif /* _PADDLE_H_ */