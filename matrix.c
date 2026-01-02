#include "matrix.h"
#include <math.h>
#include <stdint.h>

mat3_t mat3_identity(void) {
/*
 ┌─   ─┐
 │1 0 0│
 │0 1 0│
 │0 0 1│
 └─   ─┘
*/
	mat3_t result = {{{0}}};

	for (size_t i = 0; i < 3; i++) {
		result.m[i][i] = 1.0f;
	}

	return result;
}

//roll
mat3_t make_rotation_mat3_z(float a) {
	mat3_t result = mat3_identity();
	result.m[0][0] = cos(a);
	result.m[0][1] = -sin(a);
	result.m[1][0] = sin(a);
	result.m[1][1] = cos(a);

	return result;
}
//pitch
mat3_t make_rotation_mat3_x(float a) { 
	mat3_t result = mat3_identity();
	result.m[1][1] = cos(a);
	result.m[1][2] = -sin(a);
	result.m[2][1] = sin(a);
	result.m[2][2] = cos(a);

	return result;
}

//yaw
mat3_t make_rotation_mat3_y(float a) { 
	mat3_t result = mat3_identity();
	result.m[0][0] = cos(a);
	result.m[0][2] = sin(a);
	result.m[2][0] = -sin(a);
	result.m[2][2] = cos(a);

	return result;
}


vec3_t mat3_mult_vec3(mat3_t m, vec3_t v) {
/*
 ┌─   ─┐ ┌─┐ ┌─          ─┐
 │a b c│ │x│ │ax + by + cz│
 │d e f│*│y│=│dx + ey + fz│
 │g h i│ │z│ │gx + hy + iz│
 └─   ─┘ └─┘ └─          ─┘
*/

 vec3_t result = {
	.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z,
	.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z,
	.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z,
};

return result;

}