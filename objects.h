#ifndef OBJECTS_H
#define OBJECTS_H
#include "mesh.h"
#include "triangle.h"
#include "display.h"
#include "transform.h"

extern char**  filenames;
extern size_t object_count;

void draw_objects(triangle_t** triangles_to_render);
void perform_transforms(mesh_t* mesh, triangle_t** triangles_on_mesh);

#endif //OBJECTS_H