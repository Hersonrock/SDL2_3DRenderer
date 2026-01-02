#include "mesh.h"
mesh_t* meshes = NULL;

void free_meshes(uint32_t object_count) {
	// Free per-mesh dynamic data
	if (meshes) {
		for (size_t i = 0; i < object_count; i++) {
			array_free(meshes[i].vertices);
			array_free(meshes[i].faces);
			meshes[i].vertices = NULL;
			meshes[i].faces = NULL;
		}
		free(meshes);
		meshes = NULL;
	}
}