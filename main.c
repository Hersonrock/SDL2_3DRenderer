#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

bool is_running = false;

SDL_DisplayMode display_mode;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

uint32_t window_width = 0;
uint32_t window_height = 0;

int32_t previous_frame_time = 0;


bool initialize_window(void) {

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "Failed to initialize SDL.\n");
		return false;
	}

	if (SDL_GetCurrentDisplayMode(0, &display_mode)) {
		fprintf(stderr, "Failed to get current display mode.\n");
		return false;
	}

	window_width = display_mode.w;
	window_height = display_mode.h;

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);
	if (!window) {
		fprintf(stderr, "Failed to initialize window\n");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Failed to initialize renderer\n");
		return false;
	}

	return true;
}

void setup(void) {

}

void process_input(void) {

}

void update(void) {
	
	int32_t time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

	if (time_to_wait > 0) {
		SDL_Delay(time_to_wait);
	}

	previous_frame_time = SDL_GetTicks();
}

void render(void) {

}

void destroy_window(void) {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
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