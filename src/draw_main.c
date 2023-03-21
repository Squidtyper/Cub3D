/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 12:42:01 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/17 15:50:17 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <math.h>
#define PI 3.1415926535

static void	st_draw_background(t_exe_info *info)
{
	int		y;
	int		x;
	int32_t	color;

	y = 0;
	color = info->map_input->c_color;
	while (y < HEIGHT_WIDTH)
	{
		if (y > HEIGHT_WIDTH / 2)
			color = info->map_input->f_color;
		x = 0;
		while (x < HEIGHT_WIDTH)
		{
			mlx_put_pixel(info->background, x, y, color);
			x++;
		}
		y++;
	}
}

static void	st_draw_player(t_exe_info *info)
{
	size_t	y;
	size_t	x;
	size_t	size;

	y = 0;
	if (info->pad_x == HEIGHT_WIDTH)
		return ;
	size = info->blk_size / 8;
	if (info->blk_size / 8 < 2)
		size = 2;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_put_pixel(info->scene, round(info->player.x - size / 2)
				+ x + info->pad_x, round(info->player.y - size / 2) + y
				+ info->pad_y, 0xFF5733FF);
			x++;
		}
		y++;
	}
}

void	draw_background(t_exe_info *info)
{
	st_draw_background(info);
	mlx_image_to_window(info->mlx, info->background, 0, 0);
}

int	draw_cube(t_exe_info *info)
{
	mlx_delete_image(info->mlx, info->scene);
	info->scene = mlx_new_image(info->mlx, HEIGHT_WIDTH, HEIGHT_WIDTH);
	if (!info->scene)
		return (EXIT_FAILURE);
	draw_map(info);
	draw_ray_scene(info);
	st_draw_player(info);
	draw_player_direction(info);
	mlx_image_to_window(info->mlx, info->scene, 0, 0);
	return (MLX_SUCCESS);
}
