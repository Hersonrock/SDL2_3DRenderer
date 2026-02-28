#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <stdint.h>

typedef struct {
	float m[3][3];
}mat3_t;

typedef struct {
	float m[4][4];
}mat4_t;

mat3_t mat3_identity(void);
vec3_t mat3_mult_vec3(mat3_t m, vec3_t v);

mat3_t make_rotation_mat3_z(float a);
mat3_t make_rotation_mat3_x(float a);
mat3_t make_rotation_mat3_y(float a);


mat4_t mat4_identity(void);
vec4_t mat4_mult_vec4(mat4_t m, vec4_t v);

mat4_t mat4_make_scale(float sx, float sy, float sz);
mat4_t mat4_make_translation(float tx, float ty, float tz);
mat4_t make_rotation_mat4_x(float a);
mat4_t make_rotation_mat4_y(float a);
mat4_t make_rotation_mat4_z(float a);
mat4_t mat4_mult_mat4(mat4_t m1, mat4_t m2);
float mat3_determinant(mat3_t m);
float mat4_determinant(mat4_t m);
mat4_t mat4_transpose(mat4_t m);
mat4_t mat4_inverse(mat4_t m);
mat4_t mat4_div_float(mat4_t m, float f);
mat3_t mat4_minor(mat4_t m, int row, int col);
mat4_t mat4_make_perspective(uint32_t screen_width, uint32_t screen_height, float fov_angle, float znear, float zfar);

#endif //MATRIX_H