#include "cube3D.h"
#include <stdio.h>

bool	is_wall(char c)
{
	return (c == '1' || c == 'D');
}

void	set_is_door(t_image_mlx *img, t_wall_pos *w_pos, double rx, double ry)
{
	size_t	x;
	size_t	y;

	x = (int)(rx) / img->blk_size;
	y = (int)(ry) / img->blk_size;
	if (x >= img->map_input->map_width)
		return ;
	if (y >= img->map_input->map_height)
		return ;
	if(img->map_input->map_points[y][x] == 'D')
		w_pos->is_door = true;
}

t_wall_type	set_wall_type(t_wall_pos *wall)
{
	if (wall->is_door)
		return (DOOR_CLOSE);
	return (WALL);
}