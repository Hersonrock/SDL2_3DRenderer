#ifndef MESH_H
#define MESH_H

#include <stdint.h>
#include <stdlib.h>
#include "vector.h"

typedef enum {
	OBJ,
	STL,
	IEMF
} filetype_t;

typedef struct {
	int a;
	int b;
	int c;
}face_t;

typedef struct {
	vec3_t* vertices;
	face_t* faces;
	vec3_t rotation;
	size_t n_triangles;
	filetype_t file_type;
}mesh_t;

extern mesh_t* meshes;

void free_meshes(uint32_t object_count);

#endif // MESH_H