#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "cube3D.h"

#include <stdio.h>
#include <memory.h>
#include <math.h>


/* 
    to set the delta (that is where the player is looking) 
    we need sine and cosine.
*/
void set_player(t_image_mlx	*img)
{
	img->player.angle = 0; 
	img->player.x = img->map_input->player_x * img->blk_size + img->blk_size / 2; 
	img->player.y = img->map_input->player_y * img->blk_size + img->blk_size / 2;
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
