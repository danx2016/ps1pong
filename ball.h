#ifndef _BALL_H_
#define _BALL_H_

#include <stdint.h>
#include "vec2.h"

#define BALL_DIAMETER 16
#define BALL_SPEED_MAX 10.0
#define BALL_INITIAL_SPEED 3.0
#define BALL_SPEED_INCREASE_RATE 1.001

typedef struct Ball Ball;

struct Ball
{
    uint16_t diameter;
    Vec2 position;
    Vec2 velocity;
    float speed;
};

typedef struct Paddle Paddle;

extern Ball ball_init(uint16_t diamater, float px, float py);
extern void ball_fixed_update(Ball *ball, Paddle *paddle_left, Paddle *paddle_right);

#include "paddle.h"

#endif /* _BALL_H_ */