#include "objects.h"
#include "array.h"
#include "transform.h"
#include "vector.h"
#include "matrix.h"
#include "display.h"
#include "viewport.h"
#include <stdio.h>

char** filenames = NULL;
triangle_t** triangles_to_render = NULL;
size_t object_count = 0;

void perform_transforms(mesh_t* mesh, triangle_t** triangles_on_mesh) {
	mat4_t world_matrix;
	mat4_t view_matrix;
	mat4_t perspective_matrix;

	vec4_t view_space_points[TRI];

	vec3_t ndc_vertices[TRI];
	vec2_t screen_space_points[TRI];
	world_matrix = world_transform(1, 1, 1, 0, 0, 0, mesh->rotation.x, mesh->rotation.y, mesh->rotation.z);
	view_matrix = view_transform(camera_position.x, camera_position.y, camera_position.z, 0, 0, 0);
	perspective_matrix = mat4_make_perspective(viewport.w, viewport.h, M_PI / 3, 0.1f, 100);

	for (size_t i = 0; i < mesh->n_triangles; i++) {
		vec3_t face_vertices[TRI];
		switch (mesh->file_type) {
			case OBJ:
			case IEMF:
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
			vec4_t homogeneous_vertices = vec4_from_vec3(face_vertices[j]);
			vec4_t world_space_vertex = mat4_mult_vec4(world_matrix, homogeneous_vertices);
			view_space_points[j] = mat4_mult_vec4(view_matrix, world_space_vertex);
		}

		if (backface_culling(view_space_points)) continue;

		//Preparation for Painters algorithm
		float avg_depth = (view_space_points[0].z +
						   view_space_points[1].z +
						   view_space_points[2].z) / 3;

		triangle_t transformed_triangle;
		transformed_triangle.avg_depth = avg_depth;

		for (size_t j = 0; j < TRI; j++) {

			vec4_t projected_vertice = mat4_mult_vec4(perspective_matrix, view_space_points[j]);
			ndc_vertices[j] = vec3_from_homogeneous(projected_vertice);

			screen_space_points[j] = screen_transform(ndc_vertices[j]);
			transformed_triangle.points[j] = screen_space_points[j];
		}
		array_push(*triangles_on_mesh, transformed_triangle);
	}
	sort_triangles(*triangles_on_mesh, array_length(*triangles_on_mesh));
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