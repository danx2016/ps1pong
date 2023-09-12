#include <libmath.h>
#include <limits.h>

#include "vec2.h"

Vec2 vec2_init(float x, float y)
{
    Vec2 vr = { x, y };
    return vr;
}

Vec2 vec2_add(Vec2 *va, Vec2 *vb)
{
    Vec2 vr;
    vr.x = va->x + vb->x;
    vr.y = va->y + vb->y;
    return vr;
}

Vec2 vec2_sub(Vec2 *va, Vec2 *vb)
{
    Vec2 vr;
    vr.x = va->x - vb->x;
    vr.y = va->y - vb->y;
    return vr;
}

Vec2 vec2_scale(float s, Vec2 *v)
{
    Vec2 vr;
    vr.x = s * v->x;
    vr.y = s * v->y;
    return vr;
}

float vec2_length(Vec2 *v)
{
    return sqrt(v->x * v->x + v->y * v->y);
}

Vec2 vec2_normalize(Vec2 *v)
{
    Vec2 vr = { 0.0, 0.0 };
    float length = vec2_length(v);
    if (length != 0.0)
    {
        vr.x = v->x / length;
        vr.y = v->y / length;
    }
    return vr;
}

float vec2_dot(Vec2 *va, Vec2 *vb)
{
    return va->x * vb->x + vb->y * vb->y;
}

float vec2_cross(Vec2 *va, Vec2 *vb)
{
    return va->x * vb->y - vb->x * va->y;
}

float vec2_get_angle(Vec2* v) {
    return atan2(v->y, v->x);
}

Vec2 vec2_rotate(float angle, Vec2 *v)
{
    Vec2 vr;
    float s = sin(angle);
    float c = cos(angle);
    float nx = v->x * c - v->y * s;
    float ny = v->x * s + v->y * c;
    vr.x = nx;
    vr.y = ny;
    return vr;
}