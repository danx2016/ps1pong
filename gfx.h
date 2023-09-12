#ifndef _GFX_H_
#define _GFX_H_

#include <stdint.h>

extern uint16_t gfx_screen_width;
extern uint16_t gfx_screen_height;

extern void gfx_init();
extern void gfx_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
extern void gfx_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
extern void gfx_draw_text(uint8_t* text);
extern void gfx_swap_buffers();

#endif /* _GFX_H_ */