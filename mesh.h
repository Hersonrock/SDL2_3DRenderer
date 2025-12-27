#ifndef MESH_H
#define MESH_H
#include "vector.h"
#include "triangle.h"
#include "array.h"
#include "load.h"

typedef struct {
	vec3_t* vertices;
	face_t* faces;
	vec3_t rotation;
}mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);
void load_obj_file_data(char* filename);

#endif // MESH_H