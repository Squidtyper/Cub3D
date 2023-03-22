#include "execution.h"
#include <math.h>

void	key_w(t_exe_info *img, t_wall_coll *set)
{
	if (!is_wall(img->map_input->map_points[set->ipy][set->ipx_add_xo]))
		img->player.x += img->player.delta_x;
	if (!is_wall(img->map_input->map_points[set->ipy_add_yo][set->ipx]))
		img->player.y += img->player.delta_y;
}

void	key_s(t_exe_info *img, t_wall_coll *set)
{
	if (!is_wall(img->map_input->map_points[set->ipy][set->ipx_sub_xo]))
		img->player.x -= img->player.delta_x;
	if (!is_wall(img->map_input->map_points[set->ipy_sub_yo][set->ipx]))
		img->player.y -=  img->player.delta_y;
}

void	key_a(t_exe_info *img, t_wall_coll *set)
{
	if (!is_wall(img->map_input->map_points[set->ipy][set->ipx_add_yo]))
		img->player.x += img->player.delta_y;
	if (!is_wall(img->map_input->map_points[set->ipy_sub_xo][set->ipx]))
		img->player.y -= img->player.delta_x;
}

void	key_d(t_exe_info *img, t_wall_coll *set)
{
	if (!is_wall(img->map_input->map_points[set->ipy][set->ipx_sub_yo]))
		img->player.x -=  img->player.delta_y;
	if (!is_wall(img->map_input->map_points[set->ipy_add_xo][set->ipx]))
		img->player.y += img->player.delta_x;
}

void	key_space(t_exe_info *img)
{
	t_wall_coll	set;

	set.x_offset = 0;
	set.y_offset = 0;

	if (img->player.delta_x < 0)
		set.x_offset = -(img->blk_size / 2.5);
	else
		set.x_offset = (img->blk_size / 2.5);
	if (img->player.delta_y < 0)
		set.y_offset = -(img->blk_size / 2.5);
	else
		set.y_offset = (img->blk_size / 2.5);
	set.ipx_add_xo = (img->player.x + set.x_offset) / img->blk_size;
	set.ipy_add_yo = (img->player.y + set.y_offset) / img->blk_size;
	if (img->map_input->map_points[set.ipy_add_yo][set.ipx_add_xo] == 'D')
		img->map_input->map_points[set.ipy_add_yo][set.ipx_add_xo] = 'O';
}