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



bool initialize_window();

void destroy_window(void);
void free_resources(uint32_t object_count, char** filenames);

#endif // DISPLAY
