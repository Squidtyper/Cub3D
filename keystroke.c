#include "cube3D.h"


void	key_w(t_image_mlx *img, t_wall_coll *set)
{
	if(mappa[set->ipy*map_x +set->ipx_add_xo] == 0)
		img->player.x += img->player.delta_x;
	if(mappa[set->ipy_add_yo*map_x +set->ipx] == 0)
		img->player.y += img->player.delta_y;
}

void	key_s(t_image_mlx *img, t_wall_coll *set)
{
	if(mappa[set->ipy*map_x +set->ipx_sub_xo] == 0)
		img->player.x -= img->player.delta_x;
	if(mappa[set->ipy_sub_yo*map_x +set->ipx] == 0)
		img->player.y -= img->player.delta_y;
}

void	key_a(t_image_mlx *img, t_wall_coll *set)
{
	img->player.y -= img->player.delta_x;
	img->player.x += img->player.delta_y;
	if(set)
		return ;
}

void	key_d(t_image_mlx *img, t_wall_coll *set)
{
	img->player.y += img->player.delta_x;
	img->player.x -= img->player.delta_y;
	if(set)
	return ;
}
