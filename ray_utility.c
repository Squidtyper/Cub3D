#include "cube3D.h"
#include <math.h>
#define VERTICAL 0

void set_print(t_print_info *info, t_image_mlx *img, t_ray_end *ray)
{
	info->img = img->player.img;
	info->start_x = img->player.x;
	info->start_y = img->player.y;
	if (ray->pos == VERTICAL)
	{
		info->end_x = ray->ver_x;
		info->end_y = ray->ver_y;
		info->color = 0x85b6c1FF;
	}
	else
	{
		info->end_x = ray->hor_x;
		info->end_y =  ray->hor_y;
		info->color = 0x911ef6FF;
	}
}

/*
	you cannot a see a verical wall if you look up/down
	and you cannot see a horizontal wall if you look left/right
*/
void	set_no_wall(t_rays *rays, t_player *player)
{
		rays->y = player->y;
		rays->x = player->x;
		rays->dof = 8;
}

/*
    find hypotenuse with pitagora theorem
    this function finds the length of the ray
*/
double	dist_pg_rayend(double ax, double ay, double bx, double by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}