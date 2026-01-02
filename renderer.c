#include <assert.h>
#include "renderer.h"
#include "viewport.h"
#include "array.h"

SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

bool initialize_renderer(SDL_Window* window) {

	bool renderer = renderer_init(window);
	bool color_buffer = color_buffer_init();
	bool texture = color_buffer_texture_init();

	return renderer && color_buffer && texture;

}

bool renderer_init(SDL_Window* window) {
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf_s(stderr, "Failed to initialize renderer\n");
		return false;
	}
	return true;
}

bool color_buffer_init(void) {
	color_buffer = (uint32_t*)malloc(viewport.w * viewport.h * sizeof(uint32_t));
	if (color_buffer == NULL) {
		fprintf_s(stderr, "Failed to initialize color buffer\n");
		return false;
	}

	return true;
}

bool color_buffer_texture_init(void) {
	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, viewport.w, viewport.h);
	if (!color_buffer_texture) {
		fprintf_s(stderr, "Failed to create color_buffer_texture\n");
		return false;
	}
	return true;
}

void draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
	if (x < viewport.w && y < viewport.h) {
		color_buffer[(viewport.w * y) + x] = color;
	}
	else
	{
		printf("Pixel Bound Error (%dx%d)(%d,%d)\n", viewport.w, viewport.h, x, y);
	}
}

void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color) {

	assert(x1 >= 0 && y1 >= 0);
	assert(x2 >= 0 && y2 >= 0);

	int32_t dx = abs(x1 - x2);
	int32_t dy = abs(y1 - y2);

	int32_t sx = (x1 < x2) ? 1 : -1;
	int32_t sy = (y1 < y2) ? 1 : -1;

	int32_t err = dx - dy;

	while (1) {
		draw_pixel(x1, y1, color);

		if (x1 == x2 && y1 == y2) break;

		int32_t e2 = err * 1;

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

	uint32_t w_h = viewport.h - 2;
	uint32_t w_w = viewport.w - 2;
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

	uint32_t w_h = viewport.h - 2;
	uint32_t w_w = viewport.w - 2;

	for (size_t j = 0; j <= w_h; j++) {
		for (size_t i = 0; i <= w_w; i++) {
			if (j % step == 0 && i % step == 0) {
				color_buffer[(viewport.w * j) + i] = color;
			}
		}
	}
}

void draw_rectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color) {

	for (size_t j = y; j <= y + height; j++) {
		for (size_t i = x; i <= x + width; i++) {
			draw_pixel(i, j, color);
		}
	}
}

void draw_triangle(triangle_t triangle, uint32_t color) {
	for (size_t i = 0; i < TRI; i++) {
		//draw_rectangle(triangle.points[i].x, triangle.points[i].y, size, size, color);

		if (i > 0) {
			draw_line(triangle.points[i - 1].x, triangle.points[i - 1].y, triangle.points[i].x, triangle.points[i].y, color);
		}
		if (i == 2) {
			draw_line(triangle.points[i].x, triangle.points[i].y, triangle.points[0].x, triangle.points[0].y, color);
		}
	}
}

void draw_objects(triangle_t** triangles_to_render, uint32_t object_count) {
	for (size_t w = 0; w < object_count; w++) {

		size_t num_triangles = array_length(triangles_to_render[w]);
		for (size_t i = 0; i < num_triangles; i++) {
			draw_triangle(triangles_to_render[w][i], 0xFFFFFFFF);
		}
		array_free(triangles_to_render[w]);
		triangles_to_render[w] = NULL;
	}
}


void color_buffer_clear(uint32_t color) {
	for (size_t y = 0; y < viewport.h; y++) {
		for (size_t x = 0; x < viewport.w; x++) {
			color_buffer[(viewport.w * y) + x] = color;
		}
	}
}

void color_buffer_render(void) {

	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(viewport.w * sizeof(uint32_t)));
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);

}

void renderer_shutdown(void) {
	if (color_buffer) {
		free(color_buffer);
		color_buffer = NULL;
	}
	if (color_buffer_texture) {
		SDL_DestroyTexture(color_buffer_texture);
		color_buffer_texture = NULL;
	}
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
}