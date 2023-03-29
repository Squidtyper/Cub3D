#include "execution_bonus.h"
#include <math.h>

#define PI 3.1415926535


static void	st_mouse_left(t_exe_info *info, int x)
{
	info->player.angle -= ((HEIGHT_WIDTH / 2)- x) *0.00005;
	angle_normalizer(&(info->player.angle));
	info->player.delta.y = sin(info->player.angle) * (info->size / 30);
	info->player.delta.x = cos(info->player.angle) * (info->size / 30);
}

static void	st_mouse_right(t_exe_info *info, int x)
{
	info->player.angle += (x - (HEIGHT_WIDTH / 2)) * 0.00005;
	angle_normalizer(&(info->player.angle));
	info->player.delta.y = sin(info->player.angle) * (info->size / 30);
	info->player.delta.x = cos(info->player.angle) * (info->size / 30);
}

static void	st_mouse(t_exe_info *info)
{	
	int32_t	x;
	int32_t	y;

	mlx_get_mouse_pos(info->mlx, &x, &y);
	if (x > HEIGHT_WIDTH / 2 + info->size * 2 || x <  HEIGHT_WIDTH / 2 - info->size * 2)
	{
		if (x > HEIGHT_WIDTH / 2 )
			st_mouse_right(info, x);
		else
			st_mouse_left(info, x);
	}
}

void	hook(void *param)
{
	t_exe_info	*info;
	t_object_seen	wall;
	t_object_seen	door;

	info = param;
	wall_collision(info, &wall);
	door_closing(info, &door);
	keystroke(info, &wall, &door);
	st_mouse(info);
	if (draw_cube(info) == EXIT_FAILURE)
		mlx_close_window(info->mlx);
}
