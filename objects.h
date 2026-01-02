#ifndef OBJECTS_H
#define OBJECTS_H
#include "mesh.h"
#include "triangle.h"
#include "transform.h"
#include "viewport.h"
#include "vector.h"

extern char**  filenames;
extern size_t object_count;
extern triangle_t** triangles_to_render;

void perform_transforms(mesh_t* mesh, triangle_t** triangles_on_mesh);
void free_objects();

#endif //OBJECTS_H