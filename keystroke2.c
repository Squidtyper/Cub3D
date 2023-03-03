#include "cube3D.h"
#include <math.h>

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
