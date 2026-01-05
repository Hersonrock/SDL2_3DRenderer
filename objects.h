#ifndef OBJECTS_H
#define OBJECTS_H
#include "mesh.h"
#include "triangle.h"

typedef struct {
	char* filename;
	filetype_t filetype;
}file_t;

extern char**  filenames;
extern size_t object_count;
extern triangle_t** triangles_to_render;

void perform_transforms(mesh_t* mesh, triangle_t** triangles_on_mesh);
void free_objects();

#endif //OBJECTS_H