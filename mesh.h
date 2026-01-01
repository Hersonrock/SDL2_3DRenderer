#ifndef MESH_H
#define MESH_H
#include "triangle.h"
#include "array.h"
#include "vector.h"
#include "load.h"

typedef struct {
	vec3_t* vertices;
	face_t* faces;
	vec3_t rotation;
}mesh_t;

extern mesh_t* meshes;

void load_obj_file_data(char* filename, mesh_t* in_mesh);

#endif // MESH_H