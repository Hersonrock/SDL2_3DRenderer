#include "mesh.h"

vec3_t* obj_vertices = NULL;
face_t* obj_faces = NULL;
  
void load_obj_file_data(char* filename) {
	FILE* fd = open_file(filename);
	read_file(fd, &mesh.vertices, &mesh.faces);
}