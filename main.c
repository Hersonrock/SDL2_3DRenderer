#include "display.h"
#include "matrix.h"
#include "mesh.h"
#include "load.h"
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
	file_t* file_metadata = NULL;

	file_t file1 = {.filename = "./assets/f22.obj" , .filetype = OBJ };
	//file_t file2 = {.filename = "./assets/pikachu.STL" , .filetype = STL};
	
	array_push(file_metadata, file1)
	//array_push(file_metadata, file2);
	
	object_count = (size_t)array_length(file_metadata);

	triangles_to_render = calloc(object_count, sizeof(triangle_t*));
	meshes = calloc(object_count, sizeof(mesh_t));

	for (size_t i = 0; i < object_count; i++) {
		meshes[i].file_type = file_metadata[i].filetype;
		load_obj_file_data(file_metadata[i].filename, &meshes[i]);
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

	for (size_t n = 0; n < object_count; n++) {


		perform_transforms(&meshes[n], &triangles_to_render[n]);
		
		meshes[n].rotation = (vec3_t){
			.x = meshes[n].rotation.x + rotation_delta,
			.y = meshes[n].rotation.y + rotation_delta,
			.z = meshes[n].rotation.z + rotation_delta
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
	free_meshes(object_count);
	free_objects();

	return 0;
}