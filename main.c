#include "display.h"
#include "matrix.h"
#include "mesh.h"
#include "test.h"
#include "array.h"
#include "objects.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

bool is_running = false;
int32_t previous_frame_time = 0;

vec3_t world_space_points[TRI];
vec3_t view_space_points[TRI];
vec2_t screen_space_points[TRI];

vec3_t camera_position = { .x = 0, .y = 0, .z = -5 };
float fov_factor = 640.0f;

float rotation_delta = 0.05;

static void setup(void) {
	color_buffer = (uint32_t*)malloc(window_width * window_height * sizeof(uint32_t));

	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);

	array_push(filenames, "./assets/cube1.obj");

	object_count = (size_t)array_length(filenames);

	triangles_to_render = calloc(object_count, sizeof(triangle_t*));
	meshes = calloc(object_count, sizeof(mesh_t));

	for (size_t i = 0; i < object_count; i++) {
		load_obj_file_data(filenames[i], &meshes[i]);
	}

}

static void process_input(void) {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {

	case SDL_QUIT:
		is_running = false;
		break;

	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			is_running = false;
		}

		break;
	default:
		break;
	}

}

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
		.x = ((point.x * fov_factor) / point.z) + window_width/2,
		.y = ((point.y * fov_factor) / point.z) + window_height/2
	};
	return transformed_point;
}

static void update(void) {

	int32_t time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

	if (time_to_wait > 0) {
		SDL_Delay(time_to_wait);
	}
	previous_frame_time = SDL_GetTicks();

	for (size_t w = 0; w < object_count; w++) {

		for (size_t i = 0; i < (size_t)array_length(meshes[w].faces); i++) {
			vec3_t face_vertices[TRI];
			face_vertices[0] = meshes[w].vertices[meshes[w].faces[i].a - 1];
			face_vertices[1] = meshes[w].vertices[meshes[w].faces[i].b - 1];
			face_vertices[2] = meshes[w].vertices[meshes[w].faces[i].c - 1];

			triangle_t transformed_triangle; 
			
			for (size_t j = 0; j < TRI; j++) {
				world_space_points[j] = world_transform(face_vertices[j], meshes[w]); // World Space transform
				view_space_points[j] = view_transform(world_space_points[j]); // View Space transform
				// No clip space or NDC (Normalized device coordinates)

				// Perspective_project + FOV Scaling + Translation
				screen_space_points[j] = screen_transform(view_space_points[j]);
				transformed_triangle.points[j] = screen_space_points[j];
			}
			array_push(triangles_to_render[w], transformed_triangle);
		}
		meshes[w].rotation = (vec3_t){
			.x = meshes[w].rotation.x + rotation_delta,
			.y = meshes[w].rotation.y + rotation_delta,
			.z = meshes[w].rotation.z + rotation_delta
			};
	}
}

static void render(void) {
	SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
	SDL_RenderClear(renderer);

	for (size_t w = 0; w < object_count; w++) {

		size_t num_triangles = array_length(triangles_to_render[w]);
		for (size_t i = 0; i < num_triangles; i++) {
			draw_triangle(triangles_to_render[w][i], 0xFFFFFFFF);
		}
		array_free(triangles_to_render[w]);
		triangles_to_render[w] = NULL;
	}

	color_buffer_render();
	color_buffer_clear(0xFF000000);

	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {

	(void)argc;
	(void)argv;
	is_running = initialize_window();

	setup();

	while (is_running) {
		process_input();
		update();
		render();
	}

	destroy_window();
	free_resources();

	return 0;
}