/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook_loop_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 11:43:11 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/04/24 15:55:10 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"
#include <math.h>

static void	st_mouse_left(t_exe_info *info, int x)
{
	info->player.angle -= ((HEIGHT_WIDTH / 2) - x) * 0.00005;
	angle_normalizer(&(info->player.angle));
	info->player.delta.y = sin(info->player.angle) * (info->size / 30);
	info->player.delta.x = cos(info->player.angle) * (info->size / 30);
}

static void	st_mouse_right(t_exe_info *info, int x)
{
	info->player.angle += (x - (HEIGHT_WIDTH / 2)) * 0.00005;
	angle_normalizer(&(info->player.angle));
	info->player.delta.y = sin(info->player.angle) * (info->size / 30);
	info->player.delta.x = cos(info->player.angle) * (info->size / 30);
}

static void	st_mouse(t_exe_info *info)
{	
	int32_t	x;
	int32_t	y;

	mlx_get_mouse_pos(info->mlx, &x, &y);
	if (x > HEIGHT_WIDTH / 2 + info->size * 2
		|| x < HEIGHT_WIDTH / 2 - info->size * 2)
	{
		if (x > HEIGHT_WIDTH / 2)
			st_mouse_right(info, x);
		else
			st_mouse_left(info, x);
	}
}

void	hook(void *param)
{
	t_exe_info	*info;
	t_obj_seen	wall;
	t_obj_seen	door;

	info = param;
	wall_collision(info, &wall);
	door_closing(info, &door);
	keystroke(info, &wall, &door);
	st_mouse(info);
	if (draw_cube(info) == EXIT_FAILURE)
		mlx_close_window(info->mlx);
}
