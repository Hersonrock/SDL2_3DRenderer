#include "triangle.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


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

void sort_triangles(triangle_t* triangles, size_t n_triangles) {
	triangle_t* temp = (triangle_t*)malloc(sizeof(triangle_t) * n_triangles);

	mergesort_triangle_list(triangles, temp, n_triangles);

	free(temp);
}

void mergesort_triangle_list(triangle_t* triangles, triangle_t* temp, size_t n_triangles) {
	if (n_triangles <= 1) return;

	size_t mid = n_triangles / 2;

	mergesort_triangle_list(triangles, temp, mid);
	mergesort_triangle_list(triangles + mid, temp, n_triangles - mid);

	merge_triangle_list(triangles, temp, mid, n_triangles);
}


void merge_triangle_list(triangle_t* triangles, triangle_t* temp, size_t mid, size_t end) {

	size_t i = 0;
	size_t j = mid;
	size_t k = 0;
	if (0 >= end) return;

	while (i < mid && j < end) {

		if (triangles[i].avg_depth + EPSILON >= triangles[j].avg_depth){
			temp[k] = triangles[i];
			i++;
			k++;
		}
		else {
			temp[k] = triangles[j];
			j++;
			k++;
		}
	}
	for (size_t a = i; a < mid; a++) {
		temp[k] = triangles[a];
		k++;
	}
	for (size_t b = j; b < end; b++) {
		temp[k] = triangles[b];
		k++;
	}
	
	for (size_t c = 0; c < end; c++) {
		triangles[c] = temp[c];
	}
}