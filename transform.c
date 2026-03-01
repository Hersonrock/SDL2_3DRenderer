#include "transform.h"
#include "viewport.h"

vec3_t camera_position = { .x = 0, .y = 0, .z = -5 };
float fov_factor = 640.0f;

mat4_t world_transform( float sx, float sy, float sz, float tx, float ty, float tz, float pitch, float yaw, float roll) {
	mat4_t world_matrix = mat4_identity();

	mat4_t scale_matrix = mat4_make_scale(sx, sy, sz);
	mat4_t translation_matrix = mat4_make_translation(tx, ty, tz);

	mat4_t rotation_matrix_x = make_rotation_mat4_x(pitch);
	mat4_t rotation_matrix_y = make_rotation_mat4_y(yaw);
	mat4_t rotation_matrix_z = make_rotation_mat4_z(roll);

	mat4_t rotation_matrix = mat4_identity();
	rotation_matrix = mat4_mult_mat4(rotation_matrix, rotation_matrix_x);
	rotation_matrix = mat4_mult_mat4(rotation_matrix, rotation_matrix_y);
	rotation_matrix = mat4_mult_mat4(rotation_matrix, rotation_matrix_z);
	
	
	world_matrix = mat4_mult_mat4(world_matrix, translation_matrix);
	world_matrix = mat4_mult_mat4(world_matrix, rotation_matrix);
	world_matrix = mat4_mult_mat4(world_matrix, scale_matrix);
	

	return world_matrix;
}

mat4_t view_transform(float tx, float ty, float tz, float pitch, float yaw, float roll) {
	
	mat4_t camera_matrix = mat4_identity();
	mat4_t translation_matrix = mat4_make_translation(tx, ty, tz);

	mat4_t rotation_matrix_x = make_rotation_mat4_x(pitch);
	mat4_t rotation_matrix_y = make_rotation_mat4_y(yaw);
	mat4_t rotation_matrix_z = make_rotation_mat4_z(roll);

	mat4_t rotation_matrix = mat4_identity();
	rotation_matrix = mat4_mult_mat4(rotation_matrix, rotation_matrix_x);
	rotation_matrix = mat4_mult_mat4(rotation_matrix, rotation_matrix_y);
	rotation_matrix = mat4_mult_mat4(rotation_matrix, rotation_matrix_z);

	camera_matrix = mat4_mult_mat4(camera_matrix, rotation_matrix);
	camera_matrix = mat4_mult_mat4(camera_matrix, translation_matrix);

	mat4_t view_matrix = mat4_inverse(camera_matrix);
	return view_matrix;
}

vec2_t screen_transform(vec3_t point) {

	float halfw = (float)viewport.w * 0.5f;
	float halfh = (float)viewport.h * 0.5f;

	vec2_t transformed_point = {
		.x = (point.x * halfw ) + halfw,
		.y = (-point.y * halfh ) + halfh
	};
	return transformed_point;
}

bool backface_culling(vec4_t* vertices) {

	vec3_t a = vec3_from_vec4(vect4_sub(vertices[0], vertices[1]));
	vec3_t b = vec3_from_vec4(vect4_sub(vertices[2], vertices[1]));

	vec3_t normal = vect3_cross(a, b);

	//Early return for degenerated triangles.
	if (vect3_dot(normal, normal) < EPSILON * EPSILON) return true;

	//Camera is assumed to be at 0 because the view transform should put camera at 0
	return vect3_dot(vec3_from_vec4(vertices[1]), normal) <= EPSILON;
}