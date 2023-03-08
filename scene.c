#include "cube3D.h"
#include <math.h>
#include <stdio.h>

void scene3d(double dist, int r, double cos_a, t_player *player)
{
	double line_h;
	double line_offset;

	//if (player)
		//line_h = r;
	if (cos_a < 0)
		cos_a += 2 * PI;
	if (cos_a > 2 * PI)
		cos_a -= 2 * PI;
	dist = dist * cos(cos_a);
	line_h = (8 * 8 * 320) / dist;
	if (line_h > 320)
		line_h = 320;
	line_offset = 160 - line_h / 2;
	
	draw3d(player, r*8+530, line_offset, r*8+530, line_h+line_offset);

}