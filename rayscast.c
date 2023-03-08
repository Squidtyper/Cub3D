#include "cube3D.h"
#include <math.h>
#include <stdio.h>
#define RAY_NUM 60

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

static void	find_horizontal_wall(t_player *player, t_ray_end_point *rays, double angle)
{
	t_rays ray;

	ray.dof = 0;
	ray.a_tan = -1 / tan (angle);
	if (angle > PI) // looking up
	{	
		ray.y = (((int)player->y >> 6) << 6) - 0.0001;
		ray.x = (player->y - ray.y) * ray.a_tan + player->x;
		ray.y_offset = -64;
		ray.x_offset = -ray.y_offset * ray.a_tan;
	}
	if (angle < PI) // looking down
	{	
		ray.y = (((int)player->y >> 6) << 6) + 64;
		ray.x = (player->y - ray.y) * ray.a_tan + player->x;
		ray.y_offset = 64;
		ray.x_offset = -ray.y_offset * ray.a_tan;
	}
	if (angle == 0 || angle == PI) // looking stright left right
	{	
		ray.y = player->y;
		ray.x = player->x;
		ray.dof = 8;
	}
	find_wall_map(&ray);
	rays->hor_x = ray.x;
	rays->hor_y = ray.y;
}

static void	find_vertical_wall(t_player *player, t_ray_end_point *rays, double angle)
{
	t_rays ray;

	ray.a_tan = -tan(angle);
	ray.dof = 0;
	if (angle > P2 && angle < P3)// looking left
	{
		ray.x = (((int)player->x >> 6) << 6) - 0.0001;
		ray.y = (player->x - ray.x) * ray.a_tan + player->y;
		ray.x_offset = -64;
		ray.y_offset = -ray.x_offset * ray.a_tan;
	}
	if (angle < P2 || angle > P3) // looking right
	{	
		ray.x = (((int)player->x >> 6) << 6) + 64;
		ray.y = (player->x - ray.x) *ray.a_tan + player->y;
		ray.x_offset = 64;
		ray.y_offset = -ray.x_offset * ray.a_tan;
	}
	if (angle == 0 || angle == PI) // looking straight up or down
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
	double	ray_angle;
	int i;
	double dist;

	i = 0;
	ray_angle = player->angle - DR * 30;
	while (i < RAY_NUM)
	{
		if (ray_angle < 0)
			ray_angle += 2*PI;
		if (ray_angle > 2*PI)
			ray_angle -= 2*PI;
		find_horizontal_wall(player, &rays, ray_angle);
		find_vertical_wall(player, &rays, ray_angle);
		if (dist_pg_rayend(player->x, player->y, rays.ver_x, rays.ver_y)
		< dist_pg_rayend(player->x, player->y, rays.hor_x, rays.hor_y))
		{
				draw_lineray(player, rays.ver_x, rays.ver_y);
				dist = dist_pg_rayend(player->x, player->y, rays.ver_x, rays.ver_y);
		}
		else
		{
			draw_lineray(player, rays.hor_x, rays.hor_y);
			dist = dist_pg_rayend(player->x, player->y, rays.hor_x, rays.hor_y);
		}
		i++;
		scene3d(dist, i, player->angle - ray_angle, player);
		ray_angle += DR;
	}
}
