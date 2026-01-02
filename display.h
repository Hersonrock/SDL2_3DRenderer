#ifndef DISPLAY
#define DISPLAY

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

extern SDL_DisplayMode display_mode;
extern SDL_Window* window;

bool initialize_window();

void destroy_window(void);
void free_resources(uint32_t object_count, char** filenames);

#endif // DISPLAY
