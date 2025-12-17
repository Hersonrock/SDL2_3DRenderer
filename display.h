#ifndef DISPLAY
#define DISPLAY

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

SDL_DisplayMode display_mode;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* color_buffer_texture;

uint32_t window_width;
uint32_t window_height;

uint32_t* color_buffer;

bool initialize_window(void);

void draw_pixel(uint32_t x, uint32_t y, uint32_t color);
void draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
void draw_grid_line(uint32_t step, uint32_t color);
void draw_grid_points(uint32_t step, uint32_t color);
void draw_rectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);

void color_buffer_clear(uint32_t color);
void color_buffer_render(void);

void destroy_window(void);

#endif // DISPLAY
