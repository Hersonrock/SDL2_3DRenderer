#ifndef LOAD_H
#define LOAD_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "triangle.h"
#include "vector.h"
#include "array.h"

#define MAX_LINE_SIZE 1024

FILE *open_file(char* filename);
bool read_file(FILE* obj_file_descriptor, vec3_t** out_vertices, face_t** out_faces);

#endif //LOAD_H