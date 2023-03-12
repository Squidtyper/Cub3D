#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "cube3D.h"

#include <stdio.h>
#include <memory.h>
#include <math.h>

// uint32_t	mappa [] =
// {
// 	1,1,1,1,1,1,1,1,
// 	1,0,1,0,0,0,0,1,
// 	1,0,1,0,0,0,0,1,
// 	1,0,1,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,1,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,1,1,1,1,1,1,1,
// };

// size_t map_x=8;
// size_t map_y=8;




/* 
    to set the delta (that is where the player is looking) 
    we need sine and cosine.
*/
void set_player(t_image_mlx	*img)
{
	img->player.angle = 0; //the angle is gonna change base on the map
	img->player.x = img->map_input->player_x; //the player position too
	img->player.y =  img->map_input->player_y;
	img->player.delta_x = cos(img->player.angle) * 5;
	img->player.delta_y = sin(img->player.angle) * 5;
	
}


void draw_player(t_image_mlx *img)
{
	int y = 0;
	int x = 0;

	mlx_delete_image(img->mlx, img->player.img);
	img->player.img = mlx_new_image(img->mlx, HEIGHT, WIDTH);
	while (y < 8)
	{
		while (x < 8)
		{
			mlx_put_pixel(img->player.img, round(img->player.x - 4) + x, round(img->player.y - 4) + y, 0xFF5733FF);
			x++;
		}
		x = 0;
		y++;
	}
	x = img->player.delta_x;
	draw_rays_2D(&(img->player));
	draw_line(&(img->player));
	mlx_image_to_window(img->mlx, img->player.img, 0, 0);
}

// void	key_left(t_image_mlx *img)
// {
// 	img = NULL;
// 	return ;
// }

// void	key_right(t_image_mlx *img)
// {
// 	img = NULL;
// 	return ;
// }



int32_t	main(int ac, char **av)
{
	
	t_image_mlx	img;

	img.map_input = parse(ac, av);
	img.mlx = mlx_init(HEIGHT, WIDTH, "Cube3D", true);
	if (!img.mlx)
		exit(EXIT_FAILURE);
	img.map = mlx_new_image(img.mlx, HEIGHT, WIDTH);
	draw_map(&img);
	img.player.img = mlx_new_image(img.mlx, HEIGHT, WIDTH);
	mlx_image_to_window(img.mlx, img.map, 0, 0);
	set_player(&img);
	draw_player(&img);
	mlx_image_to_window(img.mlx, img.player.img, 0, 0);
	mlx_loop_hook(img.mlx, &hook, &img);
	mlx_loop(img.mlx);
	mlx_delete_image(img.mlx, img.map);
	mlx_delete_image(img.mlx, img.player.img);
	mlx_terminate(img.mlx);
	return (EXIT_SUCCESS);
}
