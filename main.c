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
SDL_Texture* color_buffer_texture = NULL;

uint32_t window_width = 0;
uint32_t window_height = 0;

int32_t previous_frame_time = 0;

uint32_t* color_buffer = NULL;


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
	color_buffer = (uint32_t*) malloc(window_width * window_height * sizeof(uint32_t));

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

void color_buffer_clear(uint32_t color){
	for (size_t y = 0; y < window_height; y++) {
		for (size_t x = 0; x < window_width; x++) {
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

void color_buffer_render(void) {
	
	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(window_width * sizeof(uint32_t)));

	SDL_RenderCopy(renderer,color_buffer_texture, NULL, NULL);

}

void render(void) {
	SDL_SetRenderDrawColor(renderer,0,100,100,255);
	SDL_RenderClear(renderer);

	color_buffer_render();
	color_buffer_clear(0xFF550000);

	SDL_RenderPresent(renderer);
}

void destroy_window(void) {

	SDL_DestroyTexture(color_buffer_texture);
	free(color_buffer);
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