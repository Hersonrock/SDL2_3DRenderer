#ifndef  VIEWPORT_H
#define	 VIEWPORT_H
#include <stdint.h>

typedef struct {
	uint32_t width;
	uint32_t height;
}viewport_t;

extern viewport_t viewport;
#endif // ! VIEWPORT_H
