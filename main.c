#include "display.h"
#include "test.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

bool is_running = false;
int32_t previous_frame_time = 0;


vec2_t projected_points[N_CUBE_POINTS];
float fov_factor = 128.0f;


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
			step_grid += 1;
		}
		if (event.key.keysym.sym == SDLK_KP_MINUS && step_grid > 1) {
			step_grid -= 1;
		}

		break;
	default:
		break;
	}

}
vec2_t project(vec3_t point) {
	vec2_t projected_point = {
		.x = (point.x * fov_factor),
		.y = (point.y * fov_factor)
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
		projected_points[i] = project(cube_points[i]);
	}

}



void render(void) {
	SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
	SDL_RenderClear(renderer);

	for (size_t i = 0; i < N_CUBE_POINTS; i++) {
		draw_rectangle(
			projected_points[i].x + (window_width / 2),
			projected_points[i].y + (window_height / 2),
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