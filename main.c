#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

bool is_running = false;

SDL_DisplayMode display_mode;

uint32_t window_width = 0;
uint32_t window_height = 0;

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



	return true;
}

int main(int argc, char* argv[]) {
	
	is_running = initialize_window();

	return 0;
}