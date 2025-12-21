#include "display.h"
#include "test.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

bool is_running = false;
int32_t previous_frame_time = 0;


vec2_t projected_points[N_CUBE_POINTS];
vec3_t world_space_points[N_CUBE_POINTS];
float scale_factor = 128.0f;


void setup(void) {
	color_buffer = (uint32_t*)malloc(window_width * window_height * sizeof(uint32_t));

	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);

	generate_3Dcube_points(CUBE_POINTS, cube_points);
}

void process_input(void) {
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
		if (event.key.keysym.sym == SDLK_KP_PLUS) {
			//step_grid += 1;
			scale_factor += 1;
		}
		if (event.key.keysym.sym == SDLK_KP_MINUS && step_grid > 1) {
			//step_grid -= 1;
			scale_factor -= 1;
		}

		break;
	default:
		break;
	}

}

vec3_t world_transform(vec3_t point) {
	vec3_t transformed_point = {
		.x = (point.x * scale_factor) + window_width / 2,
		.y = (point.y * scale_factor) + window_height / 2,
		.z = (point.z * scale_factor),
	};
	return transformed_point;
}

vec2_t orthographic_project(vec3_t point) {
	vec2_t projected_point = {
		.x = point.x,
		.y = point.y
	};
	return projected_point;
}

void update(void) {

	int32_t time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

	if (time_to_wait > 0) {
		SDL_Delay(time_to_wait);
	}

	previous_frame_time = SDL_GetTicks();
	
	for (int32_t i = 0; i < N_CUBE_POINTS; i++) {
		world_space_points[i] = world_transform(cube_points[i]); // World Space transform
		// Camera transform is an Identity transform
		// No clip space or NDC (no homogeneous coordinates or perspective)
		projected_points[i] = orthographic_project(world_space_points[i]);    // Screen Space transform(Naive Orthogonal)
	}

}

void render(void) {
	SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
	SDL_RenderClear(renderer);

	for (size_t i = 0; i < N_CUBE_POINTS; i++) {
		draw_rectangle(
			projected_points[i].x,
			projected_points[i].y,
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