#include "cube3D.h"
#include <math.h>
#include <stdio.h>
#include "libft/libft.h"


void	draw_rays_2D (t_player *player) 
{
	t_rays rays;
	double a_tan;

	rays.angle = player->angle;
	a_tan = -1 /tan (rays.angle);
	rays.i_ray = 0;

	//orizontal
	while (rays.i_ray < 1)
	{
		rays.dof = 0;
		if (rays.angle > PI) // looking up
		{	
			rays.y = (((int)player->y >> 6) << 6) -0.0001;
			rays.x = (player->y - rays.y) *a_tan + player->x;
			rays.y_offset = -64;
			rays.x_offset = -rays.y_offset * a_tan;
		}
		if (rays.angle < PI) // looking down
		{	
			rays.y = (((int)player->y >> 6) <<6) +64;
			rays.x = (player->y - rays.y) *a_tan + player->x;
			rays.y_offset = 64;
			rays.x_offset = -rays.y_offset * a_tan;
		}
		if (rays.angle ==0 || rays.angle == PI) // looking stright left right
		{	
			rays.y = player->y;
			rays.x =  player->x;
			rays.dof = 8;
		}
		while (rays.dof < 8)
		{
			rays.map_x = (int)(rays.x) >> 6;
			rays.map_y = (int)(rays.x) >> 6;
			rays.map_pos = rays.map_y * 8 + rays.map_x;
			if( rays.map_pos < 8 * 8 && mappa[rays.map_pos] == 1) //hit wall
				rays.dof = 8;
			else
			{
				rays.y += rays.y_offset;
				rays.x += rays.x_offset;
				rays.dof++;
			}
		}
		draw_lineray(player, rays);
		rays.i_ray++;
	}
}

