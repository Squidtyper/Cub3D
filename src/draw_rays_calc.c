/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays_calc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 16:32:33 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/17 14:16:39 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <math.h>
#define PI 3.1415926535

static void	st_set_ray(t_exe_info *img, t_wall_pos *w_pos, t_ray *ray,
	t_drc pos)
{
	double	dist;

	dist = dist_pg_rayend(img->player.x, img->player.y, ray->x, ray->y);
	if (pos == HORIZONTAL)
	{
		w_pos->hor_x = ray->x;
		w_pos->hor_y = ray->y;
		w_pos->dist = dist;
		w_pos->side = set_direction(pos, ray->angle);
	}
	else
	{
		w_pos->ver_x = ray->x;
		w_pos->ver_y = ray->y;
		if (w_pos->dist > dist)
		{
			w_pos->dist = dist;
			w_pos->side = set_direction(pos, ray->angle);
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
static void	st_find_wall_map(t_exe_info *img, t_ray *ray)
{
	int	x;
	int	y;

	while (ray->pg_view < ray->max_pg_view)
	{
		x = (int)(ray->x) / img->blk_size;
		y = (int)(ray->y) / img->blk_size;
		if ((y >= 0 && x >= 0)
			&& (y < (int)img->map_input->map_height && x
				< (int)img->map_input->map_width)
			&& is_wall(img->map_input->map_points[y][x]))
		{
			ray->pg_view = ray->max_pg_view;
		}
		else
		{
			ray->y += ray->y_offset;
			ray->x += ray->x_offset;
			ray->pg_view++;
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
static void	st_find_horiz_wall(t_exe_info *img, t_wall_pos *w_pos,
	double angle)
{
	t_ray	ray;

	ray.max_pg_view = calc_max_wall_dist(img);
	ray.pg_view = 0;
	ray.tan = -1 / tan (angle);
	ray.angle = angle;
	if (angle > PI)
	{
		ray.y = ((int)(img->player.y / img->blk_size) * img->blk_size) - 0.0001;
		ray.x = (img->player.y - ray.y) * ray.tan + img->player.x;
		ray.y_offset = -img->blk_size;
		ray.x_offset = -ray.y_offset * ray.tan;
	}
	if (angle < PI)
	{	
		ray.y = ((int)(img->player.y / img->blk_size) * img->blk_size)
			+ img->blk_size;
		ray.x = (img->player.y - ray.y) * ray.tan + img->player.x;
		ray.y_offset = img->blk_size;
		ray.x_offset = -ray.y_offset * ray.tan;
	}
	if (angle == 0 || angle == PI)
		set_no_wall(&(img->player), &ray);
	st_find_wall_map(img, &ray);
	st_set_ray(img, w_pos, &ray, HORIZONTAL);
}

/*
    This function checks if in front of you
    (depending on which direction are you looking, up down left or right ) 
    there is a vertical wall
    dof indicates how far a player can see
    angle > PI/2 && angle < 3*PI/2 looking left
    angle < PI/2 || angle > 3*PI/2 looking right
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
static void	st_find_vert_wall(t_exe_info *img, t_wall_pos *w_pos,
	double angle)
{
	t_ray	ray;

	ray.max_pg_view = calc_max_wall_dist(img);
	ray.pg_view = 0;
	ray.tan = -tan(angle);
	ray.angle = angle;
	if (angle > PI / 2 && angle < 3 * PI / 2)
	{
		ray.x = ((int)(img->player.x / img->blk_size) * img->blk_size) - 0.0001;
		ray.y = (img->player.x - ray.x) * ray.tan + img->player.y;
		ray.x_offset = -img->blk_size;
		ray.y_offset = -ray.x_offset * ray.tan;
	}
	if (angle < PI / 2 || angle > 3 * PI / 2)
	{	
		ray.x = (((int)(img->player.x / img->blk_size)) * img->blk_size)
			+ img->blk_size;
		ray.y = (img->player.x - ray.x) * ray.tan + img->player.y;
		ray.x_offset = img->blk_size;
		ray.y_offset = -ray.x_offset * ray.tan;
	}
	if (angle == 0 || angle == 3 * PI / 2)
		set_no_wall(&(img->player), &ray);
	st_find_wall_map(img, &ray);
	st_set_ray(img, w_pos, &ray, VERTICAL);
}

void	draw_ray_scene(t_exe_info *img)
{
	t_wall_pos		w_pos;
	t_print_info	info;
	double			ray_angle;
	int				i;

	i = 0;
	ray_angle = img->player.angle - (0.0174533 * 30);
	while (i < HEIGHT_WIDTH)
	{
		if (ray_angle < 0)
			ray_angle += 2 * PI;
		if (ray_angle > 2 * PI)
			ray_angle -= 2 * PI;
		st_find_horiz_wall(img, &w_pos, ray_angle);
		st_find_vert_wall(img, &w_pos, ray_angle);
		set_print(img, &info, &w_pos);
		draw_scene(img, &w_pos, i, img->player.angle - ray_angle);
		if (img->pad_x < HEIGHT_WIDTH)
			draw_ray(img, &info);
		ray_angle += 0.0174533 / 17;
		i++;
	}
}
