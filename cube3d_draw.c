/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cube3d_draw.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 12:42:01 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/13 18:39:39 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"
#include <math.h>

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
			mlx_put_pixel(img->player.img, round(img->player.x - size / 2) + x,
				round(img->player.y - size / 2) + y, 0xFF5733FF);
			x++;
		}
		y++;
	}
}

void	draw_cube3d(t_image_mlx *img)
{
	mlx_delete_image(img->mlx, img->player.img);
	img->player.img = mlx_new_image(img->mlx, img->blk_size * img->map_input->map_width, img->blk_size * img->map_input->map_height);
	draw_player(img);
	draw_rays_2D(img);
	draw_player_direction(img);
	//mlx_image_to_window(img->mlx, img->cube, 0, 0);
	mlx_image_to_window(img->mlx, img->player.img, img->pad_x, img->pad_y);
}
