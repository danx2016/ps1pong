#include <libetc.h>
#include <libgpu.h>

#include "gfx.h"

uint16_t gfx_screen_width;
uint16_t gfx_screen_height;

static DISPENV disp[2];
static DRAWENV draw[2];
static uint8_t db = 0;

void gfx_init()
{
    gfx_screen_width = 320;
    gfx_screen_height = 240;

    ResetGraph(0);
    SetDefDispEnv(&disp[0], 0, 0, gfx_screen_width, gfx_screen_height);
    SetDefDispEnv(&disp[1], 0, 240, gfx_screen_width, gfx_screen_height);
    SetDefDrawEnv(&draw[0], 0, 240, gfx_screen_width, gfx_screen_height);
    SetDefDrawEnv(&draw[1], 0, 0, gfx_screen_width, gfx_screen_height);
    draw[0].isbg = 1;
    draw[1].isbg = 1;
    setRGB0(&draw[0], 32, 32, 32);
    setRGB0(&draw[1], 32, 32, 32);
    PutDispEnv(&disp[db]);
    PutDrawEnv(&draw[db]);
    FntLoad(320, 0);
    FntOpen(0, 0, gfx_screen_width, gfx_screen_height, 0, FNT_MAX_SPRT);
    SetDispMask(1);
}

void gfx_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    LINE_F2 line;
    setLineF2(&line);
    setXY2(&line, x0, y0, x1, y1);
    setRGB0(&line, 255, 255, 255);
    DrawPrim(&line);
    DrawSync(0);
}

void gfx_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    TILE tile;
    setTile(&tile);
    setXY0(&tile, x, y);
    setWH(&tile, w, h);
    setRGB0(&tile, 255, 255, 255);
    DrawPrim(&tile);
    DrawSync(0);
}

void gfx_draw_text(uint8_t* text)
{
    FntPrint(text);
}

void gfx_swap_buffers()
{
    FntFlush(-1);
    VSync(0);
    db ^= 1;
    PutDispEnv(&disp[db]);
    PutDrawEnv(&draw[db]);
}