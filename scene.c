#include "cube3D.h"
#include <math.h>
#include <stdio.h>

/*
    to dray the scene we use vertical line
    line_h is the leght of the line that give the illusion of the distance
    line offset is just a padding of the line to have them 
    at the center of the scree.
    To avoid fisheye effect (that happen because different lenft of the ray) 
    we need to moltiply the distance of the ray with the cosine of the 
    distance of the player angle and the ray angle
*/
void scene3d(t_ray_end *rays, int ray, double angle, t_player *player )
{
	double line_h;
	double line_offset;
	t_print_info info;

	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	rays->dist = rays->dist * cos(angle);
	line_h = (8 * 8 * 320) / rays->dist;
	if (line_h > 320)
		line_h = 320;
	line_offset = 160 - line_h / 2;
	info.start_x = ray*8+530;
	info.end_x = ray*8+530;
	info.start_y = line_offset;
	info.end_y = line_h+line_offset;
	info.img = player->img;
	if (rays->pos)
		info.color = 0x911ef6FF;
	else
		info.color = 0x85b6c1FF;
	draw3d(&info);

}