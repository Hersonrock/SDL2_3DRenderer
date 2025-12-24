#ifndef  TRIANGLE_H
#define TRIANGLE_H
#include "vector.h"

#define  TRI  3 


typedef struct {
	int a;
	int b;
	int c;
} face_t;

typedef struct {
	vec2_t points[TRI];
}triangle_t;

#endif // TRIANGLE_H