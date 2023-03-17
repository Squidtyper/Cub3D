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

#include "cube3D.h"
#include <math.h>
#define PI 3.1415926535

/*
    degree start from 0 and reach 360
    we automatically know that after 360 it's just 0 again (not 361),
    and vice versa less than 0 it's 360 (not -1)
    so when we look left and right we have to keep this in consideration,
    we multiply by 5 because the values are very small
*/
static void	st_key_left(t_image_mlx *img)
{
	img->player.angle -= 0.05;
	if (img->player.angle < 0)
		img->player.angle += 2 * PI;
	img->player.delta_y = sin(img->player.angle) * 3;
	img->player.delta_x = cos(img->player.angle) * 3;
}

static void	st_key_right(t_image_mlx *img)
{
	img->player.angle += 0.05;
	if (img->player.angle > 2 * PI)
		img->player.angle -= 2 * PI;
	img->player.delta_y = sin(img->player.angle) * 3;
	img->player.delta_x = cos(img->player.angle) * 3;
}

static void	st_wall_collision(t_image_mlx	*img, t_wall_coll *set)
{
	if (img->player.delta_x < 0)
		set->x_offset = -(img->blk_size / 2);
	else
		set->x_offset = (img->blk_size / 2);
	if (img->player.delta_y < 0)
		set->y_offset = -(img->blk_size / 2);
	else
		set->y_offset = (img->blk_size / 2);
	set->ipx = img->player.x / img->blk_size;
	set->ipx_add_xo = (img->player.x + set->x_offset) / img->blk_size;
	set->ipx_add_yo = (img->player.x + set->y_offset) / img->blk_size;
	set->ipx_sub_xo = (img->player.x - set->x_offset) / img->blk_size;
	set->ipx_sub_yo = (img->player.x - set->y_offset) / img->blk_size;
	set->ipy = img->player.y / img->blk_size;
	set->ipy_add_yo = (img->player.y + set->y_offset) / img->blk_size;
	set->ipy_sub_yo = (img->player.y - set->y_offset) / img->blk_size;
	set->ipy_add_xo = (img->player.y + set->x_offset) / img->blk_size;
	set->ipy_sub_xo = (img->player.y - set->x_offset) / img->blk_size;
}

void	hook(void *param)
{
	t_image_mlx	*img;
	t_wall_coll	set;

	img = param;
	st_wall_collision(img, &set);
	if (mlx_is_key_down(img->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(img->mlx);
	if (mlx_is_key_down(img->mlx, MLX_KEY_W))
		key_w(img, &set);
	if (mlx_is_key_down(img->mlx, MLX_KEY_S))
		key_s(img, &set);
	if (mlx_is_key_down(img->mlx, MLX_KEY_A))
		key_a(img, &set);
	if (mlx_is_key_down(img->mlx, MLX_KEY_D))
		key_d(img, &set);
	if (mlx_is_key_down(img->mlx, MLX_KEY_LEFT))
		st_key_left(img);
	if (mlx_is_key_down(img->mlx, MLX_KEY_RIGHT))
		st_key_right(img);
	draw_cube(img);
}
