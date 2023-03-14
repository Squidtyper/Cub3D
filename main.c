#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "cube3D.h"

#include <stdio.h>
#include <memory.h>
#include <math.h>
#define PI 3.1415926535

/* 
    to set the delta (that is where the player is looking) 
    we need sine and cosine.
*/
void	set_player(t_image_mlx	*img)
{
	t_input	*p;

	p = img->map_input;
	if (p->map_points[p->player_y][p->player_x] == 'N')
		img->player.angle = 3 * PI / 2;
	else if (p->map_points[p->player_y][p->player_x] == 'S')
		img->player.angle = PI / 2;
	else if (p->map_points[p->player_y][p->player_x] == 'W')
		img->player.angle = PI;
	else
		img->player.angle = 0;
	p->map_points[p->player_y][p->player_x] = '0';
	img->player.x = p->player_x * img->blk_size + img->blk_size / 2;
	img->player.y = p->player_y * img->blk_size + img->blk_size / 2;
	img->player.delta_x = cos(img->player.angle) * 5;
	img->player.delta_y = sin(img->player.angle) * 5;
}

int32_t	main(int ac, char **av)
{
	t_image_mlx	img;

	img.map_input = parse(ac, av);
	img.mlx = mlx_init(HEIGHT_WIDTH, HEIGHT_WIDTH, "Cube3D", true);
	if (!img.mlx)
		exit(EXIT_FAILURE);
	img.map = mlx_new_image(img.mlx, HEIGHT_WIDTH, HEIGHT_WIDTH);
	draw_background(&img);
	draw_map(&img);
	mlx_image_to_window(img.mlx, img.map, 0, 0);
	set_player(&img);
	img.player.img = mlx_new_image(img.mlx, HEIGHT_WIDTH, HEIGHT_WIDTH);
	draw_cube3d(&img);
	mlx_loop_hook(img.mlx, &hook, &img);
	mlx_loop(img.mlx);
	mlx_delete_image(img.mlx, img.map);
	mlx_delete_image(img.mlx, img.player.img);
	mlx_terminate(img.mlx);
	return (EXIT_SUCCESS);
}
