#include "cube3D.h"
#include <math.h>

/*
    degree start from 0 and raech 360
    we automatically know that after 360 it's just 0 again (not 361),
    and vice versa lass than 0 it's 360 (not -1)
    so when we look left and right we have to keep this in consideration,
    we multiplly by 5 because the valeu are very small
*/

void	key_left(t_image_mlx *img)
{
	img->player.angle -= 0.1;
	if (img->player.angle < 0)
		img->player.angle += 2 * PI;
	img->player.delta_y = sin(img->player.angle) * 5;
	img->player.delta_x = cos(img->player.angle) * 5;
}

void	key_right(t_image_mlx *img)
{
	img->player.angle += 0.1;
	if (img->player.angle > 2 * PI)
		img->player.angle -= 2 * PI;
	img->player.delta_y = sin(img->player.angle) * 5;
	img->player.delta_x = cos(img->player.angle) * 5;
}


void	wall_collision(t_image_mlx	*img, t_wall_coll *set)
{

	if (img->player.delta_x < 0)
		set->x_offset = -20;
	else
		set->x_offset = 20;
	if (img->player.delta_y < 0)
		set->y_offset = -20;
	else
		set->y_offset = 20;
	set->ipx = img->player.x /64.0;
	set->ipx_add_xo= (img->player.x + set->x_offset) /64.0;
	set->ipx_sub_xo = (img->player.x - set->x_offset) /64.0;
	set->ipy = img->player.y /64.0;
	set->ipy_add_yo= (img->player.y + set->y_offset) /64.0;
	set->ipy_sub_yo = (img->player.y - set->y_offset) /64.0;
}

void hook(void* param)
{
	t_image_mlx	*img;
	t_wall_coll set;

	img = param;
	wall_collision(img, &set);
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
		key_left(img);
	if (mlx_is_key_down(img->mlx, MLX_KEY_RIGHT))
		key_right(img);
	draw_player(img);
}
