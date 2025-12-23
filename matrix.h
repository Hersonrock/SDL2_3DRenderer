#ifndef MATRIX_H
#define MATRIX_H


#include <math.h>
#include <stdint.h>
#include "vector.h"

typedef struct {
	float m[3][3];
}mat3_t;


mat3_t mat3_identity(void);
vec3_t mat3_mult_vec3(mat3_t m, vec3_t v);

mat3_t make_rotation_mat3_z(float a);
mat3_t make_rotation_mat3_x(float a);
mat3_t make_rotation_mat3_y(float a);

#endif //MATRIX_H