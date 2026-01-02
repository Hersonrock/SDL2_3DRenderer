#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"
#include "array.h"
#include "triangle.h"
#include "viewport.h"

extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;


bool initialize_renderer(SDL_Window* window);
bool renderer_init(SDL_Window* window);
bool color_buffer_texture_init(void);
bool color_buffer_init(void);


void draw_pixel(uint32_t x, uint32_t y, uint32_t color);
void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);
void draw_grid_line(uint32_t step, uint32_t color);
void draw_grid_points(uint32_t step, uint32_t color);
void draw_rectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
void draw_triangle(triangle_t triangle, uint32_t color);
void draw_objects(triangle_t** triangles_to_render, uint32_t object_count);

void color_buffer_clear(uint32_t color);
void color_buffer_render(void);

void renderer_shutdown(void);

#endif // !RENDERER_H
