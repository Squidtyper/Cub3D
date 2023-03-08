#include "cube3D.h"
#include <math.h>
#include <stdio.h>
#include "libft/libft.h"
#define RAY_NUM 1

static void find_wall_map(t_rays *rays)
{
	while (rays->dof < 8)
	{
		rays->map_x = (int)(rays->x) >> 6;
		rays->map_y = (int)(rays->y) >> 6;
		rays->map_pos = rays->map_y * 8 + rays->map_x;
		if (rays->map_pos > 0 && rays->map_pos < 8 * 8 && mappa[rays->map_pos] == 1) //hit wall
			rays->dof = 8;
		else
		{
			rays->y += rays->y_offset;
			rays->x += rays->x_offset;
			rays->dof++;
		}
	}
}

static void	find_horizontal_wall(t_player *player, t_ray_end_point *rays)
{
	t_rays ray;

	ray.dof = 0;
	ray.angle = player->angle;
	ray.a_tan = -1/tan (ray.angle);
	if (ray.angle > PI) // looking up
	{	
		ray.y = (((int)player->y >> 6) << 6) - 0.0001;
		ray.x = (player->y - ray.y) * ray.a_tan + player->x;
		ray.y_offset = -64;
		ray.x_offset = -ray.y_offset * ray.a_tan;
	}
	if (ray.angle < PI) // looking down
	{	
		ray.y = (((int)player->y >> 6) << 6) + 64;
		ray.x = (player->y - ray.y) * ray.a_tan + player->x;
		ray.y_offset = 64;
		ray.x_offset = -ray.y_offset * ray.a_tan;
	}
	if (ray.angle == 0 || ray.angle == PI) // looking stright left right
	{	
		ray.y = player->y;
		ray.x =  player->x;
		ray.dof = 8;
	}
	find_wall_map(&ray);
	rays->hor_x = ray.x;
	rays->hor_y = ray.y;
}

static void	find_vertical_wall(t_player *player, t_ray_end_point *rays)
{
	t_rays ray;

	ray.angle = player->angle;
	ray.a_tan = -tan(ray.angle);
	ray.dof = 0;
	if (ray.angle > P2 && ray.angle < P3)// looking left
	{
		ray.x = (((int)player->x >> 6) << 6) - 0.0001;
		ray.y = (player->x - ray.x) * ray.a_tan + player->y;
		ray.x_offset = -64;
		ray.y_offset = -ray.x_offset * ray.a_tan;
	}
	if (ray.angle < P2 || ray.angle > P3) // looking right
	{	
		ray.x = (((int)player->x >> 6) << 6) + 64;
		ray.y = (player->x - ray.x) *ray.a_tan + player->y;
		ray.x_offset = 64;
		ray.y_offset = -ray.x_offset * ray.a_tan;
	}
	if (ray.angle == 0 || ray.angle == PI) // looking straight up or down
	{	
		ray.y = player->y;
		ray.x =  player->x;
		ray.dof = 8;
	}
	find_wall_map(&ray);
	rays->ver_x = ray.x;
	rays->ver_y = ray.y;
}

//find ipotenuse with pitagora teorem
//this function find the lenght of the ray
double	dist_pg_rayend(double ax, double ay, double bx, double by)
{
	return (sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)));
}

void	draw_rays_2D (t_player *player) 
{
	t_ray_end_point rays;
	int i;

	i = 0;
	while (i < RAY_NUM)
	{
		find_horizontal_wall(player, &rays);
		find_vertical_wall(player, &rays);
		if (dist_pg_rayend(player->x, player->y, rays.ver_x, rays.ver_y)
		< dist_pg_rayend(player->x, player->y, rays.hor_x, rays.hor_y))
			draw_lineray(player, rays.ver_x, rays.ver_y);
		else
			draw_lineray(player, rays.hor_x, rays.hor_y);
		i++;
	}
}
