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
	info->start_x = img->player.x;
	info->start_y = img->player.y;
	if (w_pos->side == VERTICAL_LEFT || w_pos->side == VERTICAL_RIGHT)
	{
		info->end_x = w_pos->ver_x;
		info->end_y = w_pos->ver_y;
		info->color = 0x85b6c1FF;
	}
	else
	{
		info->end_x = w_pos->hor_x;
		info->end_y = w_pos->hor_y;
		info->color = 0x911ef6FF;
	}
}

/*
	you cannot a see a verical wall if you look up/down
	and you cannot see a horizontal wall if you look left/right
*/
void	set_no_wall(t_player *player, t_ray *ray)
{
		ray->y = player->y;
		ray->x = player->x;
		ray->pg_view = ray->max_pg_view;
}

/*
    find hypotenuse with pitagora theorem
    this function finds the length of the ray
*/
double	dist_pg_rayend(double ax, double ay, double bx, double by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

t_drc	set_direction(t_drc pos, double angle)
{
	if (pos == HORIZONTAL)
	{
		if (angle < PI)
			return (HORIZONTAL_DOWN);
		else
			return (HORIZONTAL_UP);
	}
	if (angle < PI / 2 || angle > 3 * PI / 2)
		return (VERTICAL_LEFT);
	return (VERTICAL_RIGHT);
}

int	calc_max_wall_dist(t_exe_info *img)
{
	if (img->map_input->map_height > img->map_input->map_width)
		return (img->map_input->map_height);
	return (img->map_input->map_width);
}