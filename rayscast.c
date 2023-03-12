#include "cube3D.h"
#include <math.h>
#include <stdio.h>
#define RAY_NUM 60
#define HORIZONTAL 1
#define VERTICAL 0


/*
    find ipotenuse with pitagora teorem
    this function find the lenght of the ray
*/
static double	dist_pg_rayend(double ax, double ay, double bx, double by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

static void set_ray(t_player *player, t_ray_end *rays, t_rays *ray, int pos)
{
	double dist;

	dist = dist_pg_rayend(player->x, player->y, ray->x, ray->y);
	if (pos == HORIZONTAL)
	{
		rays->hor_x = ray->x;
		rays->hor_y = ray->y;
		rays->dist = dist;
		rays->pos = pos;
	}
	else
	{
		rays->ver_x = ray->x;
		rays->ver_y = ray->y;
		if (rays->dist > dist)
		{
			rays->dist = dist;
			rays->pos = pos;
		}
	}
}
/*
	you cannot a see a verical wall if you look up/down
	and you cannot see a horizontal wall if you look left/right
*/
static void set_no_wall(t_rays *rays,t_player *player)
{
		rays->y = player->y;
		rays->x = player->x;
		rays->dof = 8;
}
/*
    becase we chose the sixe of a each square to be 64 
    so the distance of each square is 64 but in the map 
    the distance is 1 (position in the array)
    we bitshift of 6 (\64)
    then y and x become simply like our i and j in the previus map loop
*/
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

/*
    This function check if in front of you 
    (dependig in witch direction are you looking, up down left or right ) 
    there is a horizonal wall
    dof inticate how far a player can see
    angle > PI looking down
    angle < PI looking up
    angle == 0 || angle == PI left/right no possible horizontal walls
    the a_tan it's needed to find the position of the x end point of
    the ray (because it can touch every point of the wall)
        _____     _____
        ^            ^
        |            |
    in the corrent code to have the precision of 64 (the sixe of the block)
    we bitshift right of 6 and then back of 6
    we want to stop in the moment than we hit the starting line of the wall 
    not reach for example the middle;
          ^
        __|__ 
          |
*/
static void	find_horizontal_wall(t_player *player, t_ray_end *rays, double angle)
{
	t_rays ray;

	ray.dof = 0;
	ray.a_tan = -1 / tan (angle);
	if (angle > PI)
	{	
		ray.y = (((int)player->y >> 6) << 6) - 0.0001;
		ray.x = (player->y - ray.y) * ray.a_tan + player->x;
		ray.y_offset = -64;
		ray.x_offset = -ray.y_offset * ray.a_tan;
	}
	if (angle < PI)
	{	
		ray.y = (((int)player->y >> 6) << 6) + 64;
		ray.x = (player->y - ray.y) * ray.a_tan + player->x;
		ray.y_offset = 64;
		ray.x_offset = -ray.y_offset * ray.a_tan;
	}
	if (angle == 0 || angle == PI)
		set_no_wall(&ray, player);
	find_wall_map(&ray);
	set_ray(player, rays, &ray, HORIZONTAL);
}

/*
    This function check if in front of you
    (dependig in witch direction are you looking, up down left or right ) 
    there is a vertical wall
    dof inticate how far a player can see
    angle > P2 && angle < P3 looking left
    angle < P2 || angle > P3 looking right
    angle == 0 || angle == PI up/down no possible vertical walls
    the a_tan it's needed to find the position of the y end point of the
    ray (because it can touch every point of the wall)
        ->    |       |   
              |    -> | 

    in the corrent code to have the precision of 64 (the sixe of the block)
    we bitshift right of 6 and then back of 6
    we want to stop in the moment than we hit the starting line of the wall
    not reach for example the middle;
         -|->
          |
*/
static void	find_vertical_wall(t_player *player, t_ray_end *rays, double angle)
{
	t_rays ray;

	ray.a_tan = -tan(angle);
	ray.dof = 0;
	if (angle > P2 && angle < P3)
	{
		ray.x = (((int)player->x >> 6) << 6) - 0.0001;
		ray.y = (player->x - ray.x) * ray.a_tan + player->y;
		ray.x_offset = -64;
		ray.y_offset = -ray.x_offset * ray.a_tan;
	}
	if (angle < P2 || angle > P3)
	{	
		ray.x = (((int)player->x >> 6) << 6) + 64;
		ray.y = (player->x - ray.x) *ray.a_tan + player->y;
		ray.x_offset = 64;
		ray.y_offset = -ray.x_offset * ray.a_tan;
	}
	if (angle == 0 || angle == PI)
		set_no_wall(&ray, player);
	find_wall_map(&ray);
	set_ray(player, rays, &ray, VERTICAL);

}

void set_print(t_print_info *info,t_player *player, t_ray_end *ray)
{
	info->img = player->img;
	info->start_x = player->x;
	info->start_y = player->y;
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

void	draw_rays_2D(t_player *player) 
{
	t_ray_end rays;
	t_print_info info;
	double	ray_angle;
	int i;

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
		set_print(&info, player, &rays);
		draw_lineray(&info);
		scene3d(&rays, i, player->angle - ray_angle, player);
		i++;
		ray_angle += DR;
	}
}
