#ifndef  TRANSFORM_H
#define TRANSFORM_H
#define EPSILON        1e-8f

#include <stdbool.h>
#include <stdint.h>
#include "vector.h"
#include "matrix.h"

extern vec3_t camera_position;
extern float fov_factor;

mat4_t world_transform(float sx, float sy, float sz, float tx, float ty, float tz, float pitch, float yaw, float roll);
vec3_t view_transform(vec3_t point);

vec2_t screen_transform(vec3_t point);
vec3_t clip_transform(vec3_t point);
bool backface_culling(vec3_t* vertices);

#endif // ! TRANSFORM_H
