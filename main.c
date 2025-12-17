#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)
#define PI 3.14159265358979323846

bool is_running = false;

SDL_DisplayMode display_mode;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;

uint32_t window_width = 0;
uint32_t window_height = 0;

int32_t previous_frame_time = 0;

uint32_t* color_buffer = NULL;
uint32_t step_grid = 1;

bool initialize_window(void) {

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "Failed to initialize SDL.\n");
		return false;
	}

	if (SDL_GetCurrentDisplayMode(0, &display_mode)) {
		fprintf(stderr, "Failed to get current display mode.\n");
		return false;
	}

#ifdef FULL_SCREEN
	window_width = (int)display_mode.w;
	window_height = (int)display_mode.h;

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS
	);
#else
	window_width = (int)display_mode.w * 0.8;
	window_height = (int)display_mode.h * 0.8;

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
#endif // FULL_SCREEN

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Failed to initialize renderer\n");
		return false;
	}

#ifdef FULL_SCREEN

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
#else

	SDL_SetWindowFullscreen(window, 0);
	SDL_SetWindowBordered(window, SDL_TRUE);
#endif // FULL_SCREEN

	return true;
}

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

void draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
	color_buffer[(window_width * y) + x] = color;
}

void draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color) {

	int32_t dx = abs(x1 - x2);
	int32_t dy = abs(y1 - y2);

	int32_t sx = (x1 < x2) ? 1 : -1;
	int32_t sy = (y1 < y2) ? 1 : -1;

	int32_t err = dx - dy;

	while (1) {
		draw_pixel(x1, y1, color);

		if (x1 == x2 && y1 == y2) break;

		int32_t e2 = err << 1;

		if (e2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
}

void draw_grid_line(uint32_t step, uint32_t color) {

	uint32_t w_h = window_height - 2;
	uint32_t w_w = window_width - 2;
	uint32_t i = 0;
	uint32_t j = 0;

	while (1) {
		if (i > w_w) {
			draw_line(w_w, 0, w_w, w_h, color);
			break;
		}
		draw_line(i, 0, i, w_h, color);
		i += step;
	}

	while (1) {
		if (j > w_h) {
			draw_line(0, w_h, w_w, w_h, color);
			break;
		}
		draw_line(0, j, w_w, j, color);
		j += step;
	}

}

void draw_grid_points(uint32_t step, uint32_t color) {

	uint32_t w_h = window_height - 2;
	uint32_t w_w = window_width - 2;

	for (size_t j = 0; j <= w_h; j++) {
		for (size_t i = 0; i <= w_w; i++) {
			if (j % step == 0 && i % step == 0) {
				color_buffer[(window_width * j) + i] = color;
			}
		}
	}
}

void draw_rectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color) {
	
	for (size_t j = y; j <= y + height; j++) {
		for (size_t i = x; i <= x + width; i++) {		
			color_buffer[(window_width * j) + i] = color;
		}
	}
}

int circle_line_test(void) {

	uint32_t cx = window_width / 2;
	uint32_t cy = window_height / 2;
	uint32_t r = (window_height - window_height * 0.1) / 2;
	uint32_t white = 0xFFFFFFFF;

	//There should be 16 lines, starting at the center of the screen and ending at the edge of a circle. Let see
	draw_line(cx, cy, cx, cy - r, white);
	draw_line(cx, cy, cx, cy + r, white);
	draw_line(cx, cy, cx + r, cy, white);
	draw_line(cx, cy, cx - r, cy, white);

	draw_line(cx, cy, cx + r * cos(PI / 4), cy - r * sin(PI / 4), white);
	draw_line(cx, cy, cx + r * cos(PI / 4), cy + r * sin(PI / 4), white);
	draw_line(cx, cy, cx - r * cos(PI / 4), cy + r * sin(PI / 4), white);
	draw_line(cx, cy, cx - r * cos(PI / 4), cy - r * sin(PI / 4), white);

	draw_line(cx, cy, cx + r * cos(PI / 3), cy - r * sin(PI / 3), white);
	draw_line(cx, cy, cx + r * cos(PI / 6), cy + r * sin(PI / 6), white);
	draw_line(cx, cy, cx - r * cos(PI / 6), cy + r * sin(PI / 6), white);
	draw_line(cx, cy, cx - r * cos(PI / 3), cy - r * sin(PI / 3), white);

	draw_line(cx, cy, cx + r * cos(PI / 6), cy - r * sin(PI / 6), white);
	draw_line(cx, cy, cx + r * cos(PI / 3), cy + r * sin(PI / 3), white);
	draw_line(cx, cy, cx - r * cos(PI / 3), cy + r * sin(PI / 3), white);
	draw_line(cx, cy, cx - r * cos(PI / 6), cy - r * sin(PI / 6), white);

	return 0;
}

void color_buffer_clear(uint32_t color) {
	for (size_t y = 0; y < window_height; y++) {
		for (size_t x = 0; x < window_width; x++) {
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

void color_buffer_render(void) {

	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(window_width * sizeof(uint32_t)));

	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);

}

void render(void) {
	SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
	SDL_RenderClear(renderer);

	draw_rectangle(300, 200, 300, 150, 0xFFFFFFFF);

	color_buffer_render();
	color_buffer_clear(0xFF000000);

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