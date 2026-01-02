#include "display.h"

SDL_DisplayMode display_mode;
SDL_Window* window = NULL;

bool initialize_window() {

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf_s(stderr, "Failed to initialize SDL.\n");
		return false;
	}

	if (SDL_GetCurrentDisplayMode(0, &display_mode)) {
		fprintf_s(stderr, "Failed to get current display mode.\n");
		return false;
	}

#ifdef FULL_SCREEN
	viewport.w = (int)display_mode.w;
	viewport.h = (int)display_mode.h;

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		viewport.w,
		viewport.h,
		SDL_WINDOW_BORDERLESS
	);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

#else
	viewport.w = (int)display_mode.w * 0.8;
	viewport.h = (int)display_mode.h * 0.8;

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		viewport.w,
		viewport.h,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	SDL_SetWindowFullscreen(window, 0);
	SDL_SetWindowBordered(window, SDL_TRUE);
#endif // FULL_SCREEN
	return true;
}

void destroy_window(void) {

	if (window) {
		SDL_DestroyWindow(window);
		window = NULL;
	}
	
	SDL_Quit();
}

