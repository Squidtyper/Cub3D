#include "execution_bonus.h"
#include <math.h>
#include <stdio.h>
#define PI 3.1415926535

static bool	is_visible(t_exe_info *info, t_axis	temp)
{
	double	dif_angle;
	double	object_angle;

	object_angle = atan2(temp.y, temp.x);
	dif_angle = info->player.angle - object_angle;
	if (dif_angle < -PI)
			dif_angle += 2.0 * PI;
	if (dif_angle >  PI)
			dif_angle -= 2 * PI;
	if (fabs(dif_angle) < FOV  * 0.0174533)
		return (true);
	return (false);
}

double  distance_calc (t_axis a, t_axis b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void	draw_sprite(t_exe_info *info, double *view_depth)
{
	t_axis	temp;
	double	sprite_angle;
	double	dist;
	double	dist_project;
	double	sprite_h;

	temp.x = info->sprite.pos.x - info->player.pos.x;
	temp.y =  info->sprite.pos.y  - info->player.pos.y;
	if (!is_visible(info, temp))
		return ;
	sprite_angle = atan2(temp.y, temp.x) - info->player.angle;
	dist = distance_calc(info->player.pos, info->sprite.pos);
	dist_project =  (info->size / 2) * tan((FOV /2) *  0.0174533);
	sprite_h = (HEIGHT_WIDTH/ dist) * dist_project; 
	temp.y = (int)(HEIGHT_WIDTH / 2) - (int)(sprite_h / 2);
	temp.x = tan(sprite_angle) * HEIGHT_WIDTH / 2;
	
	temp.x = HEIGHT_WIDTH / 2 + temp.x - (temp.y - temp.y + sprite_h ) / 2; 
	temp.y += sprite_h;
	for (int i = 0; i <8; i++)
	{
		for (int j = 0; j < 8; j++)
		{	

			if (temp.x > 0 && temp.x < HEIGHT_WIDTH && dist < view_depth[(int)temp.x + j] && temp.y + i < HEIGHT_WIDTH  &&  temp.y + i > 0)
			{
				mlx_put_pixel(info->scene, round(temp.x) +j, round(temp.y) + i, 0xFFFFFFFF);
			}
	
		}
	}

}

void	look_for_sprite(t_exe_info *info)
{
	info->sprite.pos.x = 2.5 * info->size;
	info->sprite.pos.y = 3.5 * info->size;
	info->sprite.z = info->size / 3;
}
