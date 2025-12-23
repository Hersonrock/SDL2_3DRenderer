#ifndef MATRIX_H
#define MATRIX_H


#include <math.h>
#include "vector.h"

typedef struct {
	float m[3][3];
}mat3_t;


mat3_t mat3_identity(void);
vec3_t mat3_mult_vec3(mat3_t m, vec3_t v);


#endif //MATRIX_H