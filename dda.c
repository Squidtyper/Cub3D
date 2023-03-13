#include "cube3D.h"
#include <math.h>
#include <stdio.h>
#define LINE_THICKNESS 8


int	calculate_step(double y, double x)
{
	int	step;

	if (fabs(x) > fabs(y) && x != 0)
		step = x;
	else
		step = y;
	if (step < 0)
		step *= -1;
	return (step);
}

void	new_increase(double *y, double *x, int step)
{
	*y /= step;
	*x /= step;
}

void draw_lineray(t_print_info *info)
{
	double	x_increas;
	double	y_increas;
	int		step;

	x_increas = info->start_x - info->end_x;
	y_increas = info->start_y - info->end_y;
	step = calculate_step(y_increas, x_increas);
	if (step == 0)
		return ;
	new_increase(&y_increas, &x_increas, step);
	while (step--)
	{
		info->start_x -= x_increas;
		info->start_y -= y_increas;
		printf("%f, %f \n",round(info->start_x), round(info->start_y));
		mlx_put_pixel(info->img, round(info->start_x), round(info->start_y), info->color);
	}
}

void	draw3d(t_print_info *info)
{
	double	x_increas;
	double	y_increas;
	int		step;
	int		i;

	x_increas = info->start_x - info->end_x;
	y_increas = info->start_y - info->end_y;
	step = calculate_step(y_increas, x_increas);
	if (step == 0)
		return ;
	new_increase(&y_increas, &x_increas, step);
	i = 0;
	while (step--)
	{
		info->start_x -= x_increas;
		info->start_y -= y_increas;
		while (i < LINE_THICKNESS)
		{
			mlx_put_pixel(info->img, round(info->start_x + i), round(info->start_y), info->color);
			i++;
		}
		i = 0;
	}
}

void	draw_player_direction(t_image_mlx *img)
{
	double	y_increas;
	double	x_increas;
	double	print_x;
	double	print_y;
	int		step;

	if (img->pad_x == HEIGHT_WIDTH)
		return ;
	print_x = img->player.x;
	print_y = img->player.y;
	x_increas = img->player.delta_x * 1;
	y_increas = img->player.delta_y * 1;
	step = calculate_step(y_increas, x_increas);
	if (step == 0)
		return ;
	new_increase(&y_increas, &x_increas, step);
	while (step--)
	{
		print_x += x_increas;
		print_y += y_increas;
		mlx_put_pixel(img->player.img, round(print_x),
			round(print_y), 0xFFeb34db);
	}
}
