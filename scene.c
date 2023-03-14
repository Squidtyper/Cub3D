#include "cube3D.h"
#include <math.h>
#include <stdio.h>


/*
    To draw the scene we use vertical lines
    line_h is the length of the line that gives the illusion of the distance
    line offset is just a padding of the line to have them 
    at the center of the screen.
    To avoid the fisheye effect (that happens because of different length of the ray) 
    we need to myltiply the distance of the ray with the cosine of the 
    distance of the player angle and the ray angle
    all the numeric values are going to be change based on the size of the screen
*/
void scene3d(t_ray_end *rays, int ray, double angle, t_image_mlx *img)
{
	double line_h;
	double line_offset;
	t_print_info info;

	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	rays->dist = rays->dist * cos(angle);
	line_h = (img->map_input->map_width * img->map_input->map_height * 320) / rays->dist;
	//line_h = (8 * 8 * 320) / rays->dist;
	if (line_h > 320)
		line_h = 320;
	line_offset = 160 - line_h / 2;
	info.start_x = ray * img->map_input->map_width + 530;
	info.end_x = ray * img->map_input->map_height + 530;
	info.start_y = line_offset;
	info.end_y = line_h+line_offset;
	info.img = img->player.img;
	if (rays->pos)
		info.color = 0x911ef6FF;
	else
		info.color = 0x85b6c1FF;
	draw3d(&info);
}