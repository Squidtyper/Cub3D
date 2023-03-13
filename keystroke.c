#include "cube3D.h"


void	key_w(t_image_mlx *img, t_wall_coll *set)
{
	//if(img->map_input->map_points[set->ipy][set->ipx_add_xo] == 0)
	img->player.x += img->player.delta_x;
	//if(img->map_input->map_points[set->ipy_add_yo][set->ipx] == 0)
	img->player.y += img->player.delta_y;
	if(set)
		return ;
}

void	key_s(t_image_mlx *img, t_wall_coll *set)
{
	//if(img->map_input->map_points[set->ipy][set->ipx_sub_xo] == 0)
	img->player.x -= img->player.delta_x;
	//if(img->map_input->map_points[set->ipy_sub_yo][set->ipx] == 0)
	img->player.y -= img->player.delta_y;
	if(set)
		return ;
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
