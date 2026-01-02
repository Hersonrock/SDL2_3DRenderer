#ifndef  VIEWPORT_H
#define	 VIEWPORT_H
#include <stdint.h>

typedef struct {
	uint32_t w;
	uint32_t h;
}viewport_t;

extern viewport_t viewport;
#endif // ! VIEWPORT_H
