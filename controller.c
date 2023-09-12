#include <libetc.h>

#include "controller.h"

void controller_init()
{
    PadInit(0);
}

bool controller_is_action_pressed(uint8_t controller_id, ACTION action)
{
    uint32_t pad_info = PadRead(0);
    switch (action)
    {
        case MOVE_UP:
            return pad_info & _PAD(controller_id, PADLup);
        case MOVE_DOWN:
            return pad_info & _PAD(controller_id, PADLdown);
        case ANY:
            return pad_info;
    }
    return false;
}
