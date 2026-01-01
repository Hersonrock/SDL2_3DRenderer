#ifndef  TRANSFORM_H
#define TRANSFORM_H
#define EPSILON        1e-8f

#include "stdbool.h"
#include "matrix.h"
#include "vector.h"
#include "mesh.h"
#include "display.h"

extern vec3_t camera_position;
extern float fov_factor;

vec3_t world_transform(vec3_t point, vec3_t rotation);
vec3_t view_transform(vec3_t point);

vec2_t screen_transform(vec3_t point);
vec3_t clip_transform(vec3_t point);
bool backface_culling(vec3_t* points);


#endif // ! TRANSFORM_H
