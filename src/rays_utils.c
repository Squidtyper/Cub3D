/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 16:31:10 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/17 14:54:11 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <math.h>
#define PI 3.1415926535

void	set_print(t_exe_info *img, t_print_info *info, t_wall_pos *w_pos)
{
	info->img = img->scene;
	info->start_point.x = img->player.pos.x;
	info->start_point.y = img->player.pos.y;
	if (w_pos->side == VERTICAL_LEFT || w_pos->side == VERTICAL_RIGHT)
	{
		info->end_point.x = w_pos->ver.x;
		info->end_point.y = w_pos->ver.y;
		info->color = 0x85b6c1FF;
	}
	else
	{
		info->end_point.x = w_pos->hor.x;
		info->end_point.y = w_pos->hor.y;
		info->color = 0x911ef6FF;
	}
}

/*
    find hypotenuse with pitagora theorem
    this function finds the length of the ray
*/
double	dist_pg_rayend(t_axis a, t_axis b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

t_drc	set_direction(t_drc pos, double angle)
{
	if (pos == HORIZONTAL)
	{
		if (angle < PI)
			return (HORIZONTAL_UP);
		else
			return (HORIZONTAL_DOWN);
	}
	if (angle < PI / 2 || angle > 3 * PI / 2)
		return (VERTICAL_RIGHT);
	return (VERTICAL_LEFT);
}

int	calc_max_wall_dist(t_exe_info *img)
{
	if (img->map_input->map_height > img->map_input->map_width)
		return (img->map_input->map_height);
	return (img->map_input->map_width);
}

/*
	this function set the angle to the right degree:
    the angle cannot be lees than 0 or more then 360°, 
    so we know that 361° is equal to 1° 
	and -2° is equal 358°
   
*/
void	angle_normalizer(double *angle)
{
	if (*angle < 0)
			*angle += 2.0 * PI;
	if (*angle > 2.0 * PI)
			*angle -= 2.0 * PI;
}
