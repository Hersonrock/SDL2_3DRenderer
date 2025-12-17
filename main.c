#include "display.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)
#define PI 3.14159265358979323846

bool is_running = false;
int32_t previous_frame_time = 0;
uint32_t step_grid = 1;

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

void render(void) {
	SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
	SDL_RenderClear(renderer);

	draw_rectangle(300, 200, 300, 150, 0xFFFFFFFF);

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