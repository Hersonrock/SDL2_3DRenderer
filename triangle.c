#include "triangle.h"
#include <stdbool.h>
#include <math.h>

vec2_t triangle_get_m(triangle_t* triangle) {

	vec2_t m = { 0 };
	m.y = triangle->points[1].y;

	float y0 = triangle->points[0].y;
	float x0 = triangle->points[0].x;

	float y1 = triangle->points[2].y;
	float x1 = triangle->points[2].x;

	float dy = y1 - y0;

	if (fabs(dy) > EPSILON) {
		float t = (m.y - y0) / dy;
		m.x = x0 + t * (x1 - x0);
	}
	else {
		m.x = x0;
	}

	return m;
}

void sort_triangle_vertices_on_y(triangle_t* triangle) {
	bool swap;
	while (true) {
		swap = false;
		if (triangle->points[1].y < triangle->points[0].y) {
			vect2_swap(&triangle->points[1], &triangle->points[0]);
			swap = true;
		}

		if (triangle->points[2].y < triangle->points[1].y) {
			vect2_swap(&triangle->points[1], &triangle->points[2]);
			swap = true;
		}
		if (!swap) {
			break;
		}
	}
}