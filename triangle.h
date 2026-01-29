#ifndef  TRIANGLE_H
#define TRIANGLE_H
#define EPSILON        1e-8f

#include "vector.h"

#define  TRI  3 

typedef struct {
	vec2_t points[TRI];
	float avg_depth;
}triangle_t;

void sort_triangle_vertices_on_y(triangle_t* triangle);
vec2_t triangle_get_m(triangle_t* triangle);
void sort_triangles(triangle_t* triangles, size_t n_triangles);
void mergesort_triangle_list(triangle_t* triangles, triangle_t* temp, size_t n_triangles);
void merge_triangle_list(triangle_t* triangles, triangle_t* temp, size_t mid, size_t end);

#endif // TRIANGLE_H