/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keystroke_calc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 16:17:27 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/17 18:30:00 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"
#include <math.h>
#define PI 3.1415926535

/*
    degree start from 0 and reach 360
    we automatically know that after 360 it's just 0 again (not 361),
    and vice versa less than 0 it's 360 (not -1)
    so when we look left and right we have to keep this in consideration,
    we multiply by 5 because the values are very small
*/
static void	st_key_left(t_exe_info *info)
{
	info->player.angle -= 0.01;
	if (info->player.angle < 0)
		info->player.angle += 2 * PI;
	info->player.delta_y = sin(info->player.angle) * (info->blk_size / 30);
	info->player.delta_x = cos(info->player.angle) * (info->blk_size / 30);
}

static void	st_key_right(t_exe_info *info)
{
	info->player.angle += 0.01;
	if (info->player.angle > 2 * PI)
		info->player.angle -= 2 * PI;
	info->player.delta_y = sin(info->player.angle) * (info->blk_size / 30);
	info->player.delta_x = cos(info->player.angle) * (info->blk_size / 30);
}

static void	st_wall_collision(t_exe_info	*info, t_wall_coll *set)
{
	if (info->player.delta_x < 0)
		set->x_offset = -(info->blk_size / 3);
	else
		set->x_offset = (info->blk_size / 3);
	if (info->player.delta_y < 0)
		set->y_offset = -(info->blk_size / 3);
	else
		set->y_offset = (info->blk_size / 3);
	set->ipx = info->player.x / info->blk_size;
	set->ipx_add_xo = (info->player.x + set->x_offset) / info->blk_size;
	set->ipx_add_yo = (info->player.x + set->y_offset) / info->blk_size;
	set->ipx_sub_xo = (info->player.x - set->x_offset) / info->blk_size;
	set->ipx_sub_yo = (info->player.x - set->y_offset) / info->blk_size;
	set->ipy = info->player.y / info->blk_size;
	set->ipy_add_yo = (info->player.y + set->y_offset) / info->blk_size;
	set->ipy_sub_yo = (info->player.y - set->y_offset) / info->blk_size;
	set->ipy_add_xo = (info->player.y + set->x_offset) / info->blk_size;
	set->ipy_sub_xo = (info->player.y - set->x_offset) / info->blk_size;
}

void	hook(void *param)
{
	t_exe_info	*info;
	t_wall_coll	set;

	info = param;
	st_wall_collision(info, &set);
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
		key_w(info, &set);
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		key_s(info, &set);
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		key_a(info, &set);
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		key_d(info, &set);
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		st_key_left(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		st_key_right(info);
  if (mlx_is_key_down(info->mlx, MLX_KEY_SPACE)
      key_space(info);
	if (draw_cube(info) == EXIT_FAILURE)
		mlx_close_window(info->mlx);
}
