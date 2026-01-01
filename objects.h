#ifndef OBJECTS_H
#define OBJECTS_H
#include "mesh.h"
#include "triangle.h"
#include "transform.h"
#include "viewport.h"
#include "vector.h"

extern char**  filenames;
extern size_t object_count;

void perform_transforms(mesh_t* mesh, triangle_t** triangles_on_mesh);

#endif //OBJECTS_H