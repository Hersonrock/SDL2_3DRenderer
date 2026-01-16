#ifndef  TRIANGLE_H
#define TRIANGLE_H
#define EPSILON        1e-8f

#include "vector.h"

#define  TRI  3 

typedef struct {
	vec2_t points[TRI];
}triangle_t;

void sort_triangle_vertices_on_y(triangle_t* triangle);
vec2_t triangle_get_m(triangle_t* triangle);

#endif // TRIANGLE_H