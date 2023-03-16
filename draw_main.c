/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 12:42:01 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/16 18:29:11 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"
#include <math.h>
#define PI 3.1415926535

static void	st_draw_background(t_image_mlx *img)
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

/* 
    to set the delta (that is where the player is looking) 
    we need sine and cosine.
*/
static void	st_set_player(t_image_mlx *img)
{
	t_input	*p;

	p = img->map_input;
	// //printf("hello %c/n", p->map_points[p->player_y][p->player_x]);
	// if (p->map_points[p->player_y][p->player_x] == 'N')
	// 	img->player.angle = 3 * PI / 2;
	// else if (p->map_points[p->player_y][p->player_x] == 'S')
	// 	img->player.angle = PI;
	// else if (p->map_points[p->player_y][p->player_x] == 'W')
	// 	img->player.angle = PI / 2;
	// else
	img->player.angle = p->a_player;
	printf ("%f\n ", img->player.angle);
	p->map_points[p->player_y][p->player_x] = '0';
	img->player.x = p->player_x * img->blk_size + img->blk_size / 2;
	img->player.y = p->player_y * img->blk_size + img->blk_size / 2;
	img->player.delta_x = cos(img->player.angle) * 5;
	img->player.delta_y = sin(img->player.angle) * 5;
}

static void	st_draw_player(t_image_mlx *img)
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

void	draw_fixed_element(t_image_mlx *img)
{
	st_draw_background(img);
	draw_map(img);
	mlx_image_to_window(img->mlx, img->map, 0, 0);
	st_set_player(img);
}

void	draw_cube(t_image_mlx *img)
{
	mlx_delete_image(img->mlx, img->player.img);
	img->player.img = mlx_new_image(img->mlx, HEIGHT_WIDTH, HEIGHT_WIDTH);
	st_draw_player(img);
	draw_rays_view(img);
	draw_player_direction(img);
	mlx_image_to_window(img->mlx, img->player.img, 0, 0);
}
