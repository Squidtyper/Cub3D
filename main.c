#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "cube3D.h"

#include <stdio.h>
#include <memory.h>


int32_t	main(int ac, char **av)
{
	t_image_mlx	img;

	img.map_input = parse(ac, av);
	img.mlx = mlx_init(HEIGHT_WIDTH, HEIGHT_WIDTH, "Cube3D", true);
	if (!img.mlx)
		exit(EXIT_FAILURE);
	img.map = mlx_new_image(img.mlx, HEIGHT_WIDTH, HEIGHT_WIDTH);
	img.player.img = mlx_new_image(img.mlx, HEIGHT_WIDTH, HEIGHT_WIDTH);
	draw_fixed_element(&img);
	draw_cube(&img);
	mlx_loop_hook(img.mlx, &hook, &img);
	mlx_loop(img.mlx);
	mlx_delete_image(img.mlx, img.map);
	mlx_delete_image(img.mlx, img.player.img);
	mlx_terminate(img.mlx);
	return (EXIT_SUCCESS);
}
