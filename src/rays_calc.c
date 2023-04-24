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

/*
	you cannot a see a verical wall if you look up/down
	and you cannot see a horizontal wall if you look left/right
*/
static	void	st_set_no_wall(t_player *player, t_ray *ray, t_input *map_input)
{
		ray->base.y = player->pos.y * map_input->map_height;
		ray->base.x = player->pos.x * map_input->map_width;
		ray->pg_view = ray->max_pg_view;
}

static void	st_set_ray(t_exe_info *img, t_wall_pos *w_pos, t_ray *ray,
	t_drc pos)
{
	double	dist;

	dist = dist_pg_rayend(img->player.pos, ray->base);
	if (pos == HORIZONTAL)
	{
		w_pos->hor.x = ray->base.x;
		w_pos->hor.y = ray->base.y;
		w_pos->dist = dist;
		w_pos->side = set_direction(pos, ray->angle);
	}
	else
	{
		w_pos->ver.x = ray->base.x;
		w_pos->ver.y = ray->base.y;
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
    we devide by size
    then y and x become simply like our height and width in the previous map loop
*/
static void	st_find_wall_map(t_exe_info *img, t_ray *ray)
{
	int	x;
	int	y;

	while (ray->pg_view < ray->max_pg_view)
	{
		x = (int)(ray->base.x) / img->size;
		y = (int)(ray->base.y) / img->size;
		if ((y >= 0 && x >= 0)
			&& (y < (int)img->map_input->map_height && x
				< (int)img->map_input->map_width)
			&& is_wall(img->map_input->map_points[y][x]))
		{
			ray->pg_view = ray->max_pg_view;
		}
		else
		{
			ray->base.y += ray->offset.y;
			ray->base.x += ray->offset.x;
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
    the tan it's needed to find the position of the x endpoint of
    the ray (because it can touch every point of the wall)
        _____     _____
        ^            ^
        |            |
    in the current code to have the precision we devide and multiply
	the size of the block because
    we want to stop the moment that we hit the starting line of the wall 
    not reach for example the middle;
          ^
        __|__ 
          |
*/
void	find_horiz_wall(t_exe_info *img, t_wall_pos *w_pos, double angle)
{
	t_ray	r;

	r.max_pg_view = calc_max_wall_dist(img);
	r.pg_view = 0;
	r.tan = -1 / tan (angle);
	r.angle = angle;
	if (angle > PI)
	{
		r.base.y = ((int)(img->player.pos.y / img->size) * img->size) - 0.0001;
		r.base.x = (img->player.pos.y - r.base.y) * r.tan + img->player.pos.x;
		r.offset.y = -img->size;
		r.offset.x = -r.offset.y * r.tan;
	}
	if (angle < PI)
	{	
		r.base.y = ((int)(img->player.pos.y / img->size) * img->size)
			+ img->size;
		r.base.x = (img->player.pos.y - r.base.y) * r.tan + img->player.pos.x;
		r.offset.y = img->size;
		r.offset.x = -r.offset.y * r.tan;
	}
	if (angle == 0 || angle == PI)
		st_set_no_wall(&(img->player), &r, img->map_input);
	st_find_wall_map(img, &r);
	st_set_ray(img, w_pos, &r, HORIZONTAL);
}

/*
    This function checks if in front of you
    (depending on which direction are you looking, up down left or right ) 
    there is a vertical wall
    max_pg_view indicates how far a player can see
    angle > PI/2 && angle < 3*PI/2 looking left
    angle < PI/2 || angle > 3*PI/2 looking right
    angle == 0 || angle == PI up/down no possible vertical walls
    the tan it's needed to find the position of the y endpoint of the
    ray (because it can touch every point of the wall)
        ->    |       |   
              |    -> | 

    in the current code to have the precision the size of the block
    we want to stop the moment that we hit the starting line of the wall
    not reach for example the middle;
         -|->
          |
*/
void	find_vert_wall(t_exe_info *img, t_wall_pos *w_pos, double angle)
{
	t_ray	r;

	r.max_pg_view = calc_max_wall_dist(img);
	r.pg_view = 0;
	r.tan = -tan(angle);
	r.angle = angle;
	if (angle > PI / 2 && angle < 3 * PI / 2)
	{
		r.base.x = ((int)(img->player.pos.x / img->size) * img->size) - 0.0001;
		r.base.y = (img->player.pos.x - r.base.x) * r.tan + img->player.pos.y;
		r.offset.x = -img->size;
		r.offset.y = -r.offset.x * r.tan;
	}
	if (angle < PI / 2 || angle > 3 * PI / 2)
	{	
		r.base.x = (((int)(img->player.pos.x / img->size)) * img->size)
			+ img->size;
		r.base.y = (img->player.pos.x - r.base.x) * r.tan + img->player.pos.y;
		r.offset.x = img->size;
		r.offset.y = -r.offset.x * r.tan;
	}
	if (angle == PI / 2 || angle == 3 * PI / 2)
		st_set_no_wall(&(img->player), &r, img->map_input);
	st_find_wall_map(img, &r);
	st_set_ray(img, w_pos, &r, VERTICAL);
}
