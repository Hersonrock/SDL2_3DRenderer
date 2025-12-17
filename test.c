#include "test.h"
#include "display.h"

int circle_line_test(void) {

	uint32_t cx = window_width / 2;
	uint32_t cy = window_height / 2;
	uint32_t r = (window_height - window_height * 0.1) / 2;
	uint32_t white = 0xFFFFFFFF;

	//There should be 16 lines, starting at the center of the screen and ending at the edge of a circle. Let see
	draw_line(cx, cy, cx, cy - r, white);
	draw_line(cx, cy, cx, cy + r, white);
	draw_line(cx, cy, cx + r, cy, white);
	draw_line(cx, cy, cx - r, cy, white);

	draw_line(cx, cy, cx + r * cos(PI / 4), cy - r * sin(PI / 4), white);
	draw_line(cx, cy, cx + r * cos(PI / 4), cy + r * sin(PI / 4), white);
	draw_line(cx, cy, cx - r * cos(PI / 4), cy + r * sin(PI / 4), white);
	draw_line(cx, cy, cx - r * cos(PI / 4), cy - r * sin(PI / 4), white);

	draw_line(cx, cy, cx + r * cos(PI / 3), cy - r * sin(PI / 3), white);
	draw_line(cx, cy, cx + r * cos(PI / 6), cy + r * sin(PI / 6), white);
	draw_line(cx, cy, cx - r * cos(PI / 6), cy + r * sin(PI / 6), white);
	draw_line(cx, cy, cx - r * cos(PI / 3), cy - r * sin(PI / 3), white);

	draw_line(cx, cy, cx + r * cos(PI / 6), cy - r * sin(PI / 6), white);
	draw_line(cx, cy, cx + r * cos(PI / 3), cy + r * sin(PI / 3), white);
	draw_line(cx, cy, cx - r * cos(PI / 3), cy + r * sin(PI / 3), white);
	draw_line(cx, cy, cx - r * cos(PI / 6), cy - r * sin(PI / 6), white);

	return 0;
}