#ifndef LOAD_H
#define LOAD_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "mesh.h"
#include "vector.h"

#define MAX_LINE_SIZE 1024
#define FACTOR 20;

FILE* open_file(char* filename, char* mode);
bool read_file(FILE* obj_file_descriptor, vec3_t** out_vertices, face_t** out_faces);
bool read_file_stl(FILE* obj_file_descriptor, vec3_t** out_vertices);
void load_obj_file_data(char* filename, mesh_t* in_mesh);

#endif //LOAD_H