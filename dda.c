#include "cube3D.h"
#include <math.h>
#include <stdio.h>


int	calculate_step(double y, double x)
{
	int	step;
	//ft_printf("4here \n");
	//printf("reach point %f %f \n", y, x);
	if (fabs(x) > fabs(y) && x != 0)
		step = x;
	else
		step = y;
	if (step < 0)
		step *= -1;
	//ft_printf("%d \n", step);
	return (step);
}

void	new_increase(double *y, double *x, int step)
{
	*y /= step;
	*x /= step;
}

void draw_line(t_player *player)
{
	double	y_increas = (4 + player->y + player->delta_y * 5) - player->y ;
	double	x_increas = (4 + player->x + player->delta_x * 5) - player->x ;
	double	print_x = player->x;
	double	print_y = player->y;
	int		step = calculate_step(y_increas, x_increas);
	if (step == 0)
		return ;
	new_increase(&y_increas, &x_increas, step);


	while (step--)
	{
		print_x += x_increas;
		print_y += y_increas;
		//printf("view %f %f ;\n %f  %f \n", print_x, print_y, x_increas, y_increas );
		mlx_put_pixel(player->img, round(print_x), round(print_y), 0xFF5733FF);
	}
}


void draw_lineray(t_player *player, t_rays ray)
{
	double	y_increas = player->y - ray.y;
	double	x_increas = player->x - ray.x;
	double	print_x = player->x;
	double	print_y =player->y;

	printf("rays %f %f ;\n player %f %f ;\n ", ray.y, ray.x, player->y, player->x);
	//if ()
	int		step = calculate_step(y_increas, x_increas);
	if (step == 0)
		return ;
	new_increase(&y_increas, &x_increas, step);
	//ft_printf("3here \n");
	//printf("start %f %f ;\n %f  %f \n", print_x, print_y, x_increas, y_increas );
	while (step--)
	{
		print_x += x_increas;
		print_y += y_increas;
		//printf("start %f %f ;\n %f  %f \n", print_x, print_y, x_increas, y_increas );
		mlx_put_pixel(player->img, round(print_x), round(print_y), 0x85b6c1FF);
	}
}

