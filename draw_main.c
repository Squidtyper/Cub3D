/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 12:42:01 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/15 17:54:46 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"
#include <math.h>

void	draw_background(t_image_mlx *img)
{
	int		y;
	int		x;
	int32_t	color;

	y = 0;
	color = img->map_input->c_color;
	while (y < HEIGHT_WIDTH)
	{
		if (y > HEIGHT_WIDTH / 2)
			color = img->map_input->f_color;
		x = 0;
		while (x < HEIGHT_WIDTH)
		{
			mlx_put_pixel(img->map, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_image_mlx *img)
{
	size_t	y;
	size_t	x;
	size_t	size;

	y = 0;
	if (img->pad_x == HEIGHT_WIDTH)
		return ;
	size = img->blk_size / 8;
	if (img->blk_size / 8 < 2)
		size = 2;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_put_pixel(img->player.img, round(img->player.x - size / 2)
				+ x + img->pad_x, round(img->player.y - size / 2) + y
				+ img->pad_y, 0xFF5733FF);
			x++;
		}
		y++;
	}
}

void	draw_cube3d(t_image_mlx *img)
{
	mlx_delete_image(img->mlx, img->player.img);
	img->player.img = mlx_new_image(img->mlx, HEIGHT_WIDTH, HEIGHT_WIDTH);
	draw_player(img);
	draw_rays_view(img);
	draw_player_direction(img);
	mlx_image_to_window(img->mlx, img->player.img, 0, 0);
}
