#include "display.h"
#include "test.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

bool is_running = false;
int32_t previous_frame_time = 0;

void setup(void) {
	color_buffer = (uint32_t*)malloc(window_width * window_height * sizeof(uint32_t));

	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
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

void update(void) {

	int32_t time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

	if (time_to_wait > 0) {
		SDL_Delay(time_to_wait);
	}

	previous_frame_time = SDL_GetTicks();
}

void render(void) {
	SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
	SDL_RenderClear(renderer);

	//draw_rectangle(300, 200, 300, 150, 0xFFFFFFFF);
	//circle_line_test();


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