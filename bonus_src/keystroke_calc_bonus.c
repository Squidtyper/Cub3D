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

void	door_closing(t_exe_info *info, t_obj_seen *door)
{
	if (info->player.delta.x < 0)
		door->offset.x = -info->size;
	else
		door->offset.x = info->size;
	if (info->player.delta.y < 0)
		door->offset.y = -info->size;
	else
		door->offset.y = info->size;
	door->ipx = info->player.pos.x / info->size;
	door->ipx_add_xo = (info->player.pos.x + door->offset.x) / info->size;
	door->ipx_add_yo = (info->player.pos.x + door->offset.y) / info->size;
	door->ipx_sub_xo = (info->player.pos.x - door->offset.x) / info->size;
	door->ipx_sub_yo = (info->player.pos.x - door->offset.y) / info->size;
	door->ipy = info->player.pos.y / info->size;
	door->ipy_add_yo = (info->player.pos.y + door->offset.y) / info->size;
	door->ipy_sub_yo = (info->player.pos.y - door->offset.y) / info->size;
	door->ipy_add_xo = (info->player.pos.y + door->offset.x) / info->size;
	door->ipy_sub_xo = (info->player.pos.y - door->offset.x) / info->size;
}

void	wall_collision(t_exe_info *info, t_obj_seen *wall)
{
	if (info->player.delta.x < 0)
		wall->offset.x = -(info->size / 3);
	else
		wall->offset.x = (info->size / 3);
	if (info->player.delta.y < 0)
		wall->offset.y = -(info->size / 3);
	else
		wall->offset.y = (info->size / 3);
	wall->ipx = info->player.pos.x / info->size;
	wall->ipx_add_xo = (info->player.pos.x + wall->offset.x) / info->size;
	wall->ipx_add_yo = (info->player.pos.x + wall->offset.y) / info->size;
	wall->ipx_sub_xo = (info->player.pos.x - wall->offset.x) / info->size;
	wall->ipx_sub_yo = (info->player.pos.x - wall->offset.y) / info->size;
	wall->ipy = info->player.pos.y / info->size;
	wall->ipy_add_yo = (info->player.pos.y + wall->offset.y) / info->size;
	wall->ipy_sub_yo = (info->player.pos.y - wall->offset.y) / info->size;
	wall->ipy_add_xo = (info->player.pos.y + wall->offset.x) / info->size;
	wall->ipy_sub_xo = (info->player.pos.y - wall->offset.x) / info->size;
}

void	keystroke(t_exe_info *info, t_obj_seen *wall, t_obj_seen *door)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
		key_w(info, wall, door);
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		key_s(info, wall, door);
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		key_a(info, wall, door);
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		key_d(info, wall, door);
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		st_key_left(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		st_key_right(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_SPACE))
		key_space(info);
}
