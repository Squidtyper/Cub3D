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


#include "execution.h"
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
	angle_normalizer(&(info->player.angle));
	info->player.delta.y = sin(info->player.angle) * (info->size / 30);
	info->player.delta.x = cos(info->player.angle) * (info->size / 30);
}

static void	st_key_right(t_exe_info *info)
{
	info->player.angle += 0.01;
	angle_normalizer(&(info->player.angle));
	info->player.delta.y = sin(info->player.angle) * (info->size / 30);
	info->player.delta.x = cos(info->player.angle) * (info->size / 30);
}

static void	st_object_seenision(t_exe_info	*info, t_object_seen *set)
{
	if (info->player.delta.x < 0)
		set->offset.x = -(info->size / 3);
	else
		set->offset.x = (info->size / 3);
	if (info->player.delta.y < 0)
		set->offset.y = -(info->size / 3);
	else
		set->offset.y = (info->size / 3);
	set->ipx = info->player.pos.x / info->size;
	set->ipx_add_xo = (info->player.pos.x + set->offset.x) / info->size;
	set->ipx_add_yo = (info->player.pos.x + set->offset.y) / info->size;
	set->ipx_sub_xo = (info->player.pos.x - set->offset.x) / info->size;
	set->ipx_sub_yo = (info->player.pos.x - set->offset.y) / info->size;
	set->ipy = info->player.pos.y / info->size;
	set->ipy_add_yo = (info->player.pos.y + set->offset.y) / info->size;
	set->ipy_sub_yo = (info->player.pos.y - set->offset.y) / info->size;
	set->ipy_add_xo = (info->player.pos.y + set->offset.x) / info->size;
	set->ipy_sub_xo = (info->player.pos.y - set->offset.x) / info->size;
}

void	hook(void *param)
{
	t_exe_info	*info;
	t_object_seen	set;

	info = param;
	st_object_seenision(info, &set);
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
	if (draw_cube(info) == EXIT_FAILURE)
		mlx_close_window(info->mlx);
}
