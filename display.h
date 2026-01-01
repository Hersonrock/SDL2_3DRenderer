#ifndef DISPLAY
#define DISPLAY

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>
#include <assert.h>
#include "triangle.h"
#include "array.h"
#include "mesh.h"
#include "viewport.h"

// n x n x n Cube////////////////////////////////////////////////
#define CUBE_POINTS 9                                          //
#define N_CUBE_POINTS  CUBE_POINTS * CUBE_POINTS * CUBE_POINTS //
extern vec3_t cube_points[N_CUBE_POINTS];                             //
/////////////////////////////////////////////////////////////////

extern SDL_DisplayMode display_mode;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* color_buffer_texture;

extern uint32_t* color_buffer;
extern triangle_t** triangles_to_render;

bool initialize_window(void);

void draw_pixel(uint32_t x, uint32_t y, uint32_t color);
void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);
void draw_grid_line(uint32_t step, uint32_t color);
void draw_grid_points(uint32_t step, uint32_t color);
void draw_rectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
void draw_triangle(triangle_t triangle, uint32_t color);
void draw_objects(triangle_t** triangles_to_render, uint32_t object_count);

void color_buffer_clear(uint32_t color);
void color_buffer_render(void);

void destroy_window(void);
void free_resources(uint32_t object_count, char** filenames);

#endif // DISPLAY
