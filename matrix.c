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
mat4_t mat4_identity(void) {
	/*
	 ┌─		─┐
	 │1 0 0	0│
	 │0 1 0	0│
	 │0 0 1	0│
	 │0 0 0	1│
	 └─		─┘
	*/
	mat4_t result = { {{0}} };

	for (size_t i = 0; i < 4; i++) {
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


//roll
mat4_t make_rotation_mat4_z(float a) {
	mat4_t result = mat4_identity();
	result.m[0][0] = cos(a);
	result.m[0][1] = -sin(a);
	result.m[1][0] = sin(a);
	result.m[1][1] = cos(a);

	return result;
}
//pitch
mat4_t make_rotation_mat4_x(float a) {
	mat4_t result = mat4_identity();
	result.m[1][1] = cos(a);
	result.m[1][2] = -sin(a);
	result.m[2][1] = sin(a);
	result.m[2][2] = cos(a);

	return result;
}

//yaw
mat4_t make_rotation_mat4_y(float a) {
	mat4_t result = mat4_identity();
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

vec4_t mat4_mult_vec4(mat4_t m, vec4_t v) {
	/*
	 ┌─		─┐ ┌─┐ ┌─               ─┐
	 │a b c	d│ │x│ │ax + by + cz + dw│
	 │e f g	h│*│y│=│ex + fy + gz + hw│
	 │i j k	l│ │z│ │ix + jy + kz + lw│
	 │m n o	p│ │w│ │mx + ny + oz + pw│
	 └─		─┘ └─┘ └─               ─┘
	*/

	vec4_t result = {
	   .x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w,
	   .y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w,
	   .z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w,
	   .w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w,
	};

	return result;
}

mat4_t mat4_make_scale(float sx, float sy, float sz) {
	/*
	 ┌─		 ─┐
	 │sx 0 0 0│
	 │0 sy 0 0│
	 │0 0 sz 0│
	 │0 0 0	 1│
	 └─		 ─┘
	*/
	mat4_t m = mat4_identity();

	m.m[0][0] = sx;
	m.m[1][1] = sy;
	m.m[2][2] = sz;

	return m;
}

mat4_t mat4_make_translation(float tx, float ty, float tz) {
	/*
	 ┌─		 ─┐
	 │1 0 0 tx│
	 │0 1 0 ty│
	 │0 0 1 tz│
	 │0 0 0	 1│
	 └─		 ─┘
	*/
	mat4_t m = mat4_identity();

	m.m[0][3] = tx;
	m.m[1][3] = ty;
	m.m[2][3] = tz;

	return m;
}

mat4_t mat4_mult_mat4(mat4_t m1, mat4_t m2) {
	/*
	 ┌─		─┐ ┌─	  ─┐ ┌─																			    ─┐
	 │a b c	d│ │α β ψ δ│ │aα + bε + cι + dμ	   aβ + bφ + cξ + dν	aψ + bγ + cκ + dο	aδ + bη + cλ + dπ│
	 │e f g	h│*│ε φ γ η│=│eα + fε + gι + hμ	   eβ + fφ + gξ + hν	eψ + fγ + gκ + hο	eδ + fη + gλ + hπ│
	 │i j k	l│ │ι ξ κ λ│ │iα + jε + kι + lμ	   iβ + jφ + kξ + lν	iψ + jγ + kκ + lο	iδ + jη + kλ + lπ│
	 │m n o	p│ │μ ν ο π│ │mα + nε + oι + pμ    mβ + nφ + oξ + pν	mψ + nγ + oκ + pο	mδ + nη + oλ + pπ│
	 └─		─┘ └─	  ─┘ └─																				─┘
	*/

	mat4_t result;

	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return result;
}