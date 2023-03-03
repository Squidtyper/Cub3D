#include "cube3D.h"

void	key_w(t_image_mlx	*img)
{
	img->player.y += img->player.delta_y;
	img->player.x += img->player.delta_x;
}

void	key_s(t_image_mlx	*img)
{
	img->player.y -= img->player.delta_y;
	img->player.x -= img->player.delta_x;
}

void	key_a(t_image_mlx	*img)
{
	img->player.y += img->player.delta_x;
	img->player.x += img->player.delta_y;
}

void	key_d(t_image_mlx	*img)
{
	img->player.y -= img->player.delta_x;
	img->player.x -= img->player.delta_y;
}


