#include "cube3D.h"
#include <math.h>
#include <stdio.h>
#define PI 3.1415926535
//void draw(t_image_mlx *img,int line_h, int s_x, int s_y, t_ray_end *rays);
// void	draw3d(t_print_info *info, t_image_mlx *img)
// {
// 	double	x_increas;
// 	double	y_increas;
// 	int		step;
// 	int		i;

// 	x_increas = info->start_x - info->end_x;
// 	y_increas = info->start_y - info->end_y;
// 	step = calculate_step(y_increas, x_increas);
// 	if (step == 0)
// 		return ;
// 	new_increase(&y_increas, &x_increas, step);
// 	i = 0;
// 	while (step--)
// 	{
// 		info->start_x -= x_increas;
// 		info->start_y -= y_increas;
// 		while (i < 9)
// 		{
// 			mlx_put_pixel(info->img, round(info->start_x + i), round(info->start_y), info->color);
// 			i++;
// 		}
// 		i = 0;
// 	}
// }

/*
    To draw the scene we use vertical lines
    line_h is the length of the line that gives the illusion of the distance
    line offset is just a padding of the line to have them 
    at the center of the screen.
    To avoid the fisheye effect (that happens because of different length of the ray) 
    we need to myltiply the distance of the ray with the cosine of the 
    distance of the player angle and the ray angle
    all the numeric values are going to be change based on the size of the screen
*/
typedef struct s_tex
{
	double	x;
	double	x_offste;
	double	y;
	double	y_offset;
	double	step_x;
	double	step_y;
	t_drc	wall;
	double	angle;
	double	line_h;
	double	ray;
}	t_tex;

void draw_square_ray(t_image_mlx *img, double start_x, double start_y, uint32_t color)
{
	int y;
	int x;

	y = 0;
	while (y < 9)
	{
		x = 0;
		while (x < 9)
		{
			mlx_put_pixel(img->player.img, x + round(start_x) , y + round(start_y) , color << 4);
			x++;
		}
		y++;
	}
}

mlx_texture_t	*calculate_texture(t_image_mlx *img, t_tex *tex)
{
	if (tex->wall == VERTICAL_LEFT)
		return ( img->map_input->EA_tex);
	else if (tex->wall == VERTICAL_RIGHT)
		return (img->map_input->WE_tex);
	else if (tex->wall == HORIZONTAL_UP)
		return (img->map_input->NO_tex);
	else
		return (img->map_input->SO_tex);
}

double	calculate_x(t_image_mlx *img, mlx_texture_t *texture, t_tex *tex)
{
	double	x;

	if (img->blk_size > img->map_input->EA_tex->width) 
		x = (int)(tex->ray / (img->blk_size / texture->width)) % texture->width;
	else
		x = (int)(tex->ray * (texture->width / img->blk_size)) % texture->width;
	if (tex->wall == HORIZONTAL_DOWN || tex->wall == VERTICAL_LEFT)
		x = texture->width - 1 - x;
	return (x);
}

void draw_wall (t_image_mlx *img, double start_x, double start_y, t_tex *tex)
{
	int y;
	int color;
	mlx_texture_t	*texture;
	
	texture = calculate_texture(img, tex);
	tex->step_y = img->map_input->EA_tex->height / tex->step_y;
	tex->y = tex->y_offset * tex->step_y;
	tex->x = calculate_x(img, texture, tex);
	y = 0;
	while (y < tex->line_h)
	{
		color = img->map_input->EA_tex->pixels[(int)(tex->y * img->map_input->EA_tex->width + (int)tex->x)];
		draw_square_ray(img, start_x, y + start_y, color);
		y++;
		tex->y += tex->step_y;
	}

}
void	set_ray(t_ray_end *rays, t_tex *tex)
{
	if (rays->pos == VERTICAL_LEFT || rays->pos == VERTICAL_RIGHT)
		tex->ray = rays->ver_y;
	else
		tex->ray = rays->hor_x;
}

void scene3d(t_ray_end *rays, int ray, double angle, t_image_mlx *img)
{
	double line_h;
	double line_offset;
	//t_print_info info;
	//int	y;
	t_tex texture;


	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	rays->dist = rays->dist * cos(angle);
	line_h = (img->blk_size * (HEIGHT_WIDTH / 1.5) ) / rays->dist;
	texture.step_y = line_h;
	texture.y_offset  = 0;
	if (line_h > HEIGHT_WIDTH / 1.5) 
	{	
		texture.y_offset = (line_h - HEIGHT_WIDTH / 1.5) / 2.0;
		line_h = HEIGHT_WIDTH / 1.5;
	}
	line_offset = HEIGHT_WIDTH / 2 - ((int)line_h >> 1) ;
	texture.line_h = line_h;
	
	texture.angle = angle;
	texture.wall = rays->pos;
	set_ray(rays, &texture);
	draw_wall(img, ray * 8.52, line_offset + 30, &texture);
}

// uint32_t color_calc(t_image_mlx *img,int line_h, int y, int x, t_ray_end *rays)
// {
// 	mlx_texture_t *corrent;
// 	double	step;
// 	double step_x;
// 	uint32_t y_t;
// 	uint32_t x_t;
// 	double ray_x;
// 	if (x)
// 		ray_x = 0;

// 	if (rays->pos == VERTICAL_LEFT)
// 	{	corrent = img->map_input->EA_tex;
// 		ray_x = rays->ver_x;
// 	}
// 	else if (rays->pos == VERTICAL_RIGHT)
// 	{
// 		corrent = img->map_input->WE_tex;
// 		ray_x = rays->ver_x;
// 	}
// 	else if (rays->pos == HORIZONTAL_UP)
// 	{	corrent = img->map_input->NO_tex;
// 		ray_x = rays->hor_x;
// 	}
// 	else
// 	{
// 		corrent = img->map_input->SO_tex;
// 		ray_x = rays->hor_x;
// 	}
// 	corrent->pixels[]
// 	color = get_rgba(corrent->pixels[y_t+(x_t *  corrent->bytes_per_pixel)],
// 	corrent->pixels[y_t+(x_t *  corrent->bytes_per_pixel)+1], corrent->pixels[y_t+(x_t *  corrent->bytes_per_pixel)+2],corrent->pixels[y_t+(x_t *  corrent->bytes_per_pixel)] + 3);
// 	step = corrent->height / line_h;
// 	step_x = img->blk_size / corrent->width;
// 	y_t = (y *  corrent->bytes_per_pixel) * step * corrent->width ;
// 	x_t = (int)(ray_x/step_x) % (int)round(corrent->width);
// 	return(corrent->pixels[y_t+(x_t *  corrent->bytes_per_pixel)]);
// }

// void draw(t_image_mlx *img,int line_h, int s_x, int s_y, t_ray_end *rays)
// {
// 	int y;
// 	int x;
// 	uint32_t color;

// 	y = 0;
	
// 	while (y < line_h)
// 	{
// 		color = color_calc(img, line_h, y, x, rays);
// 		x=0;
// 		while (x < 9)
// 		{
// 			mlx_put_pixel(img->player.img, round(s_x) +x ,round(s_y) + y , color);
// 			x++;
// 		}
// 		y++;
// 	}
	
// }


