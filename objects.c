#include "objects.h"
#include "array.h"
#include "transform.h"
#include "vector.h"

char** filenames = NULL;
triangle_t** triangles_to_render = NULL;
size_t object_count = 0;

void perform_transforms(mesh_t* mesh, triangle_t** triangles_on_mesh) {
	vec3_t world_space_points[TRI];
	vec3_t view_space_points[TRI];
	vec3_t clip_space_points[TRI];
	vec2_t screen_space_points[TRI];

	for (size_t i = 0; i < mesh->n_triangles; i++) {
		vec3_t face_vertices[TRI];
		switch (mesh->file_type) {
		case OBJ:
			face_vertices[0] = mesh->vertices[mesh->faces[i].a - 1];
			face_vertices[1] = mesh->vertices[mesh->faces[i].b - 1];
			face_vertices[2] = mesh->vertices[mesh->faces[i].c - 1];
			break;
		case STL:
			face_vertices[0] = mesh->vertices[(i * 3) + 0];
			face_vertices[1] = mesh->vertices[(i * 3) + 1];
			face_vertices[2] = mesh->vertices[(i * 3) + 2];
			break;
		}
		
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

void free_objects() {
	// Free triangle lists (per frame buffers)
	if (triangles_to_render) {
		for (size_t i = 0; i < object_count; i++) {
			array_free(triangles_to_render[i]);
			triangles_to_render[i] = NULL;
		}
		free(triangles_to_render);
		triangles_to_render = NULL;
	}

	// Filenames (if owned)
	array_free(filenames);
	filenames = NULL;
}