#include "display.h"
#include "matrix.h"
#include "test.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

bool is_running = false;
int32_t previous_frame_time = 0;

vec3_t world_space_points[N_CUBE_POINTS];
vec3_t view_space_points[N_CUBE_POINTS];
vec2_t screen_space_points[N_CUBE_POINTS];

vec3_t camera_position = { .x = 0, .y = 0, .z = -5 };
float fov_factor = 640.0f;

vec3_t rotation = {0, 0, 0};
float rotation_delta = 0.05;

static void setup(void) {
	color_buffer = (uint32_t*)malloc(window_width * window_height * sizeof(uint32_t));

	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);

	generate_3Dcube_points(CUBE_POINTS, cube_points);
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

vec3_t world_transform(vec3_t point) {
	/*	These are here to clarify behavior, since I'm rendering a single objec
		world transforms really carry no meaning since there is no reference point.
		but in case they do, they are here.
	*/
	vec3_t transformed_point = {
		.x = point.x,
		.y = point.y,
		.z = point.z,
	};

	mat3_t rotation_mat3_z = make_rotation_mat3_z(rotation.z);
	mat3_t rotation_mat3_x = make_rotation_mat3_x(rotation.x);
	mat3_t rotation_mat3_y = make_rotation_mat3_y(rotation.y);

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
		.x = ((point.x * fov_factor) / point.z) + (window_width / 2),
		.y = ((point.y * fov_factor) / point.z) + (window_height / 2)
	};
	return transformed_point;
}

static void update(void) {

	int32_t time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

	if (time_to_wait > 0) {
		SDL_Delay(time_to_wait);
	}

	previous_frame_time = SDL_GetTicks();

	for (int32_t i = 0; i < N_CUBE_POINTS; i++) {
		world_space_points[i] = world_transform(cube_points[i]); // World Space transform
		view_space_points[i] = view_transform(world_space_points[i]); // View Space transform
		// No clip space or NDC (Normalized device coordinates)
		screen_space_points[i] = screen_transform(view_space_points[i]);    // Perspective_project + FOV Scaling + Translation
	}

	rotation = (vec3_t){
		.x = rotation.x + rotation_delta,
		.y = rotation.y + rotation_delta,
		.z = rotation.z + rotation_delta
	};

}

static void render(void) {
	SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
	SDL_RenderClear(renderer);


	for (size_t i = 0; i < N_CUBE_POINTS; i++) {
		draw_rectangle(
			screen_space_points[i].x,
			screen_space_points[i].y,
			4,
			4,
			0xFFFFFFFF
		);
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

	return 0;
}