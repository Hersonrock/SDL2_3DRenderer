#include "mesh.h"
mesh_t* meshes = NULL;

void load_obj_file_data(char* filename, mesh_t* in_mesh) {
	FILE* fd = open_file(filename);
	in_mesh->vertices = NULL;
	in_mesh->faces = NULL;
	read_file(fd, &in_mesh->vertices, &in_mesh->faces);
}