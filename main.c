#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "cube3D.h"
#include <stdio.h>
#include <memory.h>
#include <math.h>

#define HEIGHT 1024
#define WIDTH 512


uint32_t	mappa [] =
{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

size_t map_x=8;
size_t map_y=8;



void draw_square(mlx_image_t *map, uint32_t x_start, uint32_t x_end,  uint32_t y_start,  uint32_t y_end,  uint32_t color)
{
	uint32_t	x_i;
	x_i = x_start + 1;

	while (y_start + 1 < y_end - 1)
	{
		while (x_i < x_end -1)
		{
			mlx_put_pixel(map, x_i, y_start + 1, color);
			x_i++;
		}
		x_i = x_start + 1;
		y_start++;
	}

}

void	draw_map(mlx_image_t	*map)
{
	uint32_t y = 0;
	uint32_t x = 0;
	uint32_t cubeSize = 64;

	//ft_printf("%u %u %u %u\n", y, x, map_y, map_x);
	while (y < map_y)
	{
		while (x < map_x)
		{
			if(mappa[y * map_x + x] == 1)
				draw_square(map, x * cubeSize, (x+1) * cubeSize, y * cubeSize, (y+1) *cubeSize, 0xFFFFFFFF);
			else
				draw_square(map, x * cubeSize, (x+1) * cubeSize, y * cubeSize, (y+1) * cubeSize, 0x000000FF);
			x++;
		}
		x = 0;
		y++;
	}
}

void set_player(t_image_mlx	*img)
{
	img->player.angle = 0;
	img->player.x = 300;
	img->player.y = 300;
	img->player.delta_x = cos(img->player.angle) * 5;
	img->player.delta_y = sin(img->player.angle) * 5;
	
}


void draw_player(t_player *player)
{
	int y = 0;
	int x = 0;


	while (y < 8)
	{
		while (x < 8)
		{
			mlx_put_pixel(player->img, round(player->x) + x, round(player->y) + y, 0xFF5733FF);
			x++;
		}
		x = 0;
		y++;
	}
	x = player->delta_x;
	draw_line(player);
	draw_rays_2D(player);
}


void hook(void* param)
{
	t_image_mlx	*img;
	img = param;

	if (mlx_is_key_down(img->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(img->mlx);
	if (mlx_is_key_down(img->mlx, MLX_KEY_W))
		key_w(img);
	if (mlx_is_key_down(img->mlx, MLX_KEY_S))
		key_s(img);
	if (mlx_is_key_down(img->mlx, MLX_KEY_A))
		key_a(img);
	if (mlx_is_key_down(img->mlx, MLX_KEY_D))
		key_d(img);
	if (mlx_is_key_down(img->mlx, MLX_KEY_LEFT))
		key_left(img);
	if (mlx_is_key_down(img->mlx, MLX_KEY_RIGHT))
		key_right(img);
	draw_player(&(img->player));
}

int32_t	main( void )
{
	t_image_mlx	img;

	img.mlx = mlx_init(HEIGHT, WIDTH, "Cube3D", true);
	if (!img.mlx)
		exit(EXIT_FAILURE);
	img.map = mlx_new_image(img.mlx, HEIGHT, WIDTH);
	draw_map(img.map);
	img.player.img = mlx_new_image(img.mlx, HEIGHT, WIDTH);
	mlx_image_to_window(img.mlx, img.map, 0, 0);
	set_player(&img);
	draw_player(&(img.player));
	mlx_image_to_window(img.mlx, img.player.img, 0, 0);
	mlx_loop_hook(img.mlx, &hook, &img);
	mlx_loop(img.mlx);
	mlx_delete_image(img.mlx, img.map);
	mlx_delete_image(img.mlx, img.player.img);
	mlx_terminate(img.mlx);
	return (EXIT_SUCCESS);
}
