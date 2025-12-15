#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

bool is_running = false;

bool initialize_window(void) {

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "Failed to initialize SDL.\n");
		return false;
	}
	return true;
}

int main(int argc, char* argv[]) {
	
	is_running = initialize_window();

	return 0;
}