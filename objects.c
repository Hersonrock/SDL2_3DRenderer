#include "objects.h"

char** filenames = NULL;
size_t object_count = 0;

void draw_objects(triangle_t** triangles_to_render) {
	for (size_t w = 0; w < object_count; w++) {

		size_t num_triangles = array_length(triangles_to_render[w]);
		for (size_t i = 0; i < num_triangles; i++) {
			draw_triangle(triangles_to_render[w][i], 0xFFFFFFFF);
		}
		array_free(triangles_to_render[w]);
		triangles_to_render[w] = NULL;
	}
}

void perform_transforms(mesh_t* mesh, triangle_t** triangles_on_mesh) {
	vec3_t world_space_points[TRI];
	vec3_t view_space_points[TRI];
	vec3_t clip_space_points[TRI];
	vec2_t screen_space_points[TRI];

	for (size_t i = 0; i < (size_t)array_length(mesh->faces); i++) {
		vec3_t face_vertices[TRI];
		face_vertices[0] = mesh->vertices[mesh->faces[i].a - 1];
		face_vertices[1] = mesh->vertices[mesh->faces[i].b - 1];
		face_vertices[2] = mesh->vertices[mesh->faces[i].c - 1];


		for (size_t j = 0; j < TRI; j++) {
			world_space_points[j] = world_transform(face_vertices[j], mesh->rotation); // World Space transform
			view_space_points[j] = view_transform(world_space_points[j]); // View Space transform
			clip_space_points[j] = clip_transform(view_space_points[j]);
			// Not a real clip space or NDC (Normalized device coordinates) transform
		}

		if (backface_culling(view_space_points)) continue;

		triangle_t transformed_triangle;
		for (size_t j = 0; j < TRI; j++) {
			//  Translation 
			screen_space_points[j] = screen_transform(clip_space_points[j]);
			transformed_triangle.points[j] = screen_space_points[j];
		}
		array_push(*triangles_on_mesh, transformed_triangle);
	}

}

