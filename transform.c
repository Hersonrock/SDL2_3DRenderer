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

	/*Screen space transform
	Fov change, is more of a conceptual zoom all points change at the same rate.
	Translation is also a screen space transform as it is done after the points are moved into 2D.
	 I'm pilling up many tranformations here as screen transformations and they really are not,
	 such as the scaling times fov_factor is more of a Clip Space transform.
	 In the same place the perspective divide / point.z is more of a NDC
	*/

	vec2_t transformed_point = {
		.x = point.x + viewport.w * 0.5f,
		.y = point.y + viewport.h * 0.5f
	};
	return transformed_point;
}

vec3_t clip_transform(vec3_t point) {

	float projection_factor = point.z;
	vec3_t transformed_point = {
		.x = (point.x * fov_factor) / projection_factor,
		.y = (point.y * fov_factor) / projection_factor,
		.z = (point.z * fov_factor) / projection_factor
	};
	return transformed_point;
}

bool backface_culling(vec3_t* vertices) {

	vec3_t a = vect3_sub(vertices[0], vertices[1]);
	vec3_t b = vect3_sub(vertices[2], vertices[1]);
	vec3_t normal = vect3_cross(a, b);

	//Early return for degenerated triangles.
	if (vect3_dot(normal, normal) < EPSILON * EPSILON) return true;

	//Camera is assumed to be at 0 because the view transform should put camera at 0
	return vect3_dot(vertices[1], normal) <= EPSILON;
}