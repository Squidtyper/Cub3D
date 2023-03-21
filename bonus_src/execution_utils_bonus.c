#include "execution_bonus.h"
#include <stdio.h>

bool	is_wall(char c)
{
	return (c == '1' || c == 'D');
}

static bool	st_is_door(t_exe_info *img, t_wall_pos *w_pos)
{
	size_t	x;
	size_t	y;
	double rx;
	double ry;

	if (w_pos->side == VERTICAL_LEFT || w_pos->side == VERTICAL_RIGHT)
	{
		rx = w_pos->ver_x;
		ry = w_pos->ver_y;
	}
	else
	{
		rx = w_pos->hor_x;
		ry = w_pos->hor_y;
	}
	x = (int)(rx) / img->blk_size;
	y = (int)(ry) / img->blk_size;
	if (x >= img->map_input->map_width)
		return (false);
	if (y >= img->map_input->map_height)
		return (false);
	if(img->map_input->map_points[y][x] == 'D')
		return (true);
	return (false);
}

t_drc	set_wall_side(t_exe_info * info, t_wall_pos *wall)
{
	if (st_is_door(info, wall))
	{
		if (wall->side == HORIZONTAL_DOWN || wall->side == VERTICAL_RIGHT)
			return (OPPOSITE_DOOR);
		else 
			return (FRONT_DOOR);
	}
	return (wall->side);
}
