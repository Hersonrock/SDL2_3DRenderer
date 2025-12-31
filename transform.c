#include "transform.h"

vec3_t camera_position = { .x = 0, .y = 0, .z = -5 };
float fov_factor = 640.0f;

vec3_t world_transform(vec3_t point, mesh_t in_mesh) {
	/*	These are here to clarify behavior, since I'm rendering a single objec
		world transforms really carry no meaning since there is no reference point.
		but in case they do, they are here.
	*/
	vec3_t transformed_point = {
		.x = point.x,
		.y = point.y,
		.z = point.z,
	};

	mat3_t rotation_mat3_z = make_rotation_mat3_z(in_mesh.rotation.z);
	mat3_t rotation_mat3_x = make_rotation_mat3_x(in_mesh.rotation.x);
	mat3_t rotation_mat3_y = make_rotation_mat3_y(in_mesh.rotation.y);

	transformed_point = mat3_mult_vec3(rotation_mat3_z, transformed_point); // roll
	transformed_point = mat3_mult_vec3(rotation_mat3_x, transformed_point); // pitch
	transformed_point = mat3_mult_vec3(rotation_mat3_y, transformed_point); // yaw

	return transformed_point;
}

vec3_t view_transform(vec3_t point) {
	/*	Dolly , the actual camera moves. Objects closer change aparent size faster than those far away.
	*/
	vec3_t transformed_point = {
		.x = point.x,
		.y = point.y,
		.z = point.z - camera_position.z
	};
	return transformed_point;
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
		.x = point.x + window_width * 0.5,
		.y = point.y + window_height * 0.5
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

bool backface_culling(vec3_t* points) {

	vec3_t a = vect3_sub(points[1], points[0]);
	vec3_t b = vect3_sub(points[2], points[0]);

	vec3_t normal = vect3_cross(b, a);
	if (vect3_dot(normal, normal) < EPSILON) //Check for degenerate Triangles.
		return true;

	vec3_t face_to_camera = points[0];

	return vect3_dot(normal, face_to_camera) <= 0;
}