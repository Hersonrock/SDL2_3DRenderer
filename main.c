#include "display.h"
#include "matrix.h"
#include "mesh.h"
#include "test.h"
#include "array.h"
#include "objects.h"
#include "transform.h"
#include "renderer.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)
#define EPSILON        1e-8f
bool is_running = false;
int32_t previous_frame_time = 0;

float rotation_delta = 0.05;

void setup(void) {

	array_push(filenames, "./assets/cube.obj");

	object_count = (size_t)array_length(filenames);

	triangles_to_render = calloc(object_count, sizeof(triangle_t*));
	meshes = calloc(object_count, sizeof(mesh_t));

	for (size_t i = 0; i < object_count; i++) {
		load_obj_file_data(filenames[i], &meshes[i]);
	}

}

static void process_input(void) {
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

static void update(void) {

	int32_t time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

	if (time_to_wait > 0) {
		SDL_Delay(time_to_wait);
	}
	previous_frame_time = SDL_GetTicks();

	for (size_t w = 0; w < object_count; w++) {

		perform_transforms(&meshes[w], &triangles_to_render[w]);

		meshes[w].rotation = (vec3_t){
			.x = meshes[w].rotation.x + rotation_delta,
			.y = meshes[w].rotation.y + rotation_delta,
			.z = meshes[w].rotation.z + rotation_delta
			};
	}
}

static void render(void) {
	SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
	SDL_RenderClear(renderer);

	draw_objects(triangles_to_render, object_count);
	color_buffer_render();
	color_buffer_clear(0xFF000000);

	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {

	(void)argc;
	(void)argv;
	is_running = initialize_window() && initialize_renderer(window);

	setup();

	while (is_running) {
		process_input();
		update();
		render();
	}

	destroy_window();
	renderer_shutdown();
	free_resources(object_count, filenames);

	return 0;
}