#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum { ANY, MOVE_UP, MOVE_DOWN } ACTION;

extern void controller_init();

// controller_id -> 0 or 1
extern bool controller_is_action_pressed(uint8_t controller_id, ACTION action);

#endif /* _CONTROLLER_H_ */