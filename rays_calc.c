/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays_calc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 16:32:33 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/14 18:04:17 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"
#include <math.h>
#include <stdio.h>
#define PI 3.1415926535


static void	set_ray(t_image_mlx *img, t_ray_end *rays, t_rays *ray, t_drc pos)
{
	double	dist;

	dist = dist_pg_rayend(img->player.x, img->player.y, ray->x, ray->y);
	if (pos == HORIZONTAL)
	{
		rays->hor_x = ray->x;
		rays->hor_y = ray->y;
		rays->dist = dist;
		rays->pos = set_direction(pos, img->player.angle);
	}
	else
	{
		rays->ver_x = ray->x;
		rays->ver_y = ray->y;
		if (rays->dist > dist)
		{
			rays->dist = dist;
			rays->pos = set_direction(pos, img->player.angle);
		}
	}
}

/*
    because we chose the block size
    so the distance of each square is block_size but on the map 
    the distance is 1 (position in the array)
    we devide by blk_size
    then y and x become simply like our height and width in the previous map loop
*/
static void	find_wall_map(t_rays *rays, t_image_mlx *img)
{
	int	x;
	int	y;

	while (rays->dof < 8)
	{
		x = (int)(rays->x) / img->blk_size;
		y = (int)(rays->y) / img->blk_size;
		if ((y >= 0 && x >= 0)
			&& (y < (int)img->map_input->map_height && x
				< (int)img->map_input->map_width)
			&& img->map_input->map_points[y][x] == '1')
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
    This function checks if in front of you 
    (depending on which direction are you looking, up down left or right ) 
    there is a horizontal wall
    dof indicate how far a player can see
    angle > PI looking down
    angle < PI looking up
    angle == 0 || angle == PI left/right no possible horizontal walls
    the a_tan it's needed to find the position of the x endpoint of
    the ray (because it can touch every point of the wall)
        _____     _____
        ^            ^
        |            |
    in the current code to have the precision of 64 (the size of the block)
    we bitshift right of 6 and then back of 6
    we want to stop the moment that we hit the starting line of the wall 
    not reach for example the middle;
          ^
        __|__ 
          |
*/
static void	find_horizontal_wall(t_image_mlx *img, t_ray_end *rays,
	double angle)
{
	t_rays	ray;

	ray.dof = 0;
	ray.a_tan = -1 / tan (angle);
	if (angle > PI)
	{
		ray.y = ((int)(img->player.y / img->blk_size) * img->blk_size) - 0.0001;
		ray.x = (img->player.y - ray.y) * ray.a_tan + img->player.x;
		ray.y_offset = -img->blk_size;
		ray.x_offset = -ray.y_offset * ray.a_tan;
	}
	if (angle < PI)
	{	
		ray.y = ((int)(img->player.y / img->blk_size) * img->blk_size)
			+ img->blk_size;
		ray.x = (img->player.y - ray.y) * ray.a_tan + img->player.x;
		ray.y_offset = img->blk_size;
		ray.x_offset = -ray.y_offset * ray.a_tan;
	}
	if (angle == 0 || angle == PI)
		set_no_wall(&ray, &(img->player));
	find_wall_map(&ray, img);
	set_ray(img, rays, &ray, HORIZONTAL);
}

/*
    This function checks if in front of you
    (depending on which direction are you looking, up down left or right ) 
    there is a vertical wall
    dof indicates how far a player can see
    angle > P2 && angle < P3 looking left
    angle < P2 || angle > P3 looking right
    angle == 0 || angle == PI up/down no possible vertical walls
    the a_tan it's needed to find the position of the y endpoint of the
    ray (because it can touch every point of the wall)
        ->    |       |   
              |    -> | 

    in the current code to have the precision of 64 (the size of the block)
    we bitshift right of 6 and then back of 6
    we want to stop the moment that we hit the starting line of the wall
    not reach for example the middle;
         -|->
          |
*/
static void	find_vertical_wall(t_image_mlx *img, t_ray_end *rays, double angle)
{
	t_rays	ray;

	ray.a_tan = -tan(angle);
	ray.dof = 0;
	
	if (angle > PI / 2 && angle < 3 * PI / 2)
	{
		ray.x = ((int)(img->player.x / img->blk_size) * img->blk_size) - 0.0001;
		ray.y = (img->player.x - ray.x) * ray.a_tan + img->player.y;
		ray.x_offset = -img->blk_size;
		ray.y_offset = -ray.x_offset * ray.a_tan;
	}
	if (angle < PI / 2 || angle > 3 * PI / 2)
	{	
		ray.x = (((int)(img->player.x / img->blk_size)) * img->blk_size)
			+ img->blk_size;
		ray.y = (img->player.x - ray.x) * ray.a_tan + img->player.y;
		ray.x_offset = img->blk_size;
		ray.y_offset = -ray.x_offset * ray.a_tan;
	}
	if (angle == 0 || angle == 3 * PI / 2)
		set_no_wall(&ray, &(img->player));
	find_wall_map(&ray, img);
	set_ray(img, rays, &ray, VERTICAL);
}

void	draw_rays_view(t_image_mlx *img)
{
	t_ray_end		rays;
	t_print_info	info;
	double			ray_angle;
	int				i;

	i = 0;
	ray_angle = img->player.angle - (0.0174533 * 30);
	while (i < 120)
	{
		if (ray_angle < 0)
			ray_angle += 2 * PI;
		if (ray_angle > 2 * PI)
			ray_angle -= 2 * PI;
		find_horizontal_wall(img, &rays, ray_angle);
		find_vertical_wall(img, &rays, ray_angle);
		set_print(&info, img, &rays);
		if (img->pad_x < HEIGHT_WIDTH)
			draw_lineray(&info, img);
		//scene3d(&rays, i, img->player.angle - ray_angle, img);
		i++;
		ray_angle += 0.0174533 / 2;
	}
}
