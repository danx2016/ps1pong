#ifndef _VEC2_H_
#define _VEC2_H_

typedef struct 
{
    float x;
    float y;
} Vec2;

extern Vec2 vec2_init(float x, float y);
extern Vec2 vec2_add(Vec2 *va, Vec2 *vb);
extern Vec2 vec2_sub(Vec2 *va, Vec2 *vb);
extern Vec2 vec2_scale(float s, Vec2 *v);
extern float vec2_length(Vec2 *v);
extern Vec2 vec2_normalize(Vec2 *v);
extern float vec2_dot(Vec2 *va, Vec2 *vb);
extern float vec2_cross(Vec2 *va, Vec2 *vb);
extern float vec2_get_angle(Vec2* v);
extern Vec2 vec2_rotate(float angle, Vec2 *v);

#endif /* _VEC2_H_ */