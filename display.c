#include "display.h"


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

void generate_3Dcube_points(uint32_t size, vec3_t* points) {
	uint32_t point_count = 0;
	float step = 2.0f / (size - 1);

	for (float x = -1; x <= 1; x += step) {
		for (float y = -1; y <= 1; y += step) {
			for (float z = -1; z <= 1; z += step) {
				vec3_t p = {
					.x = x,
					.y = y,
					.z = z
				};
				points[point_count++] = p;
			}
		}
	}
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

void destroy_window(void) {

	SDL_DestroyTexture(color_buffer_texture);
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}