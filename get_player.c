/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_player.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 18:11:40 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/16 18:35:09 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"
#define _USE_MATH_DEFINES
#include <math.h>

void	player_error(char c)
{
	if (c == 'D')
		printf("Error: map contains more than one player\n");
	else if (c == 'N')
		printf("Error: player not found in map");
	exit(1);
}

double	get_angle(char c)
{
	if (c == 'N')
		return (M_PI / 2);
	if (c == 'E')
		return (0);
	if (c == 'S')
		return (3 * M_PI/2);
	if (c == 'W')
		return (M_PI);
	return (0);
}

void	fill_input(int x, int y, t_input *input, char c)
{
	if (input->p_found == true)
		player_error('D');
	input->a_player = get_angle(c);
	input->player_x = x;
	input->player_y = y;
	input->p_found = true;
	input->map_points[y][x] = '0';
}

void	get_player(t_input *input)
{
	unsigned int	i;
	unsigned int	j;
	char			c;

	i = 0;
	if (!input->map_points)
		return ;
	while (i < input->map_height)
	{
		j = 0;
		while (j < input->map_width)
		{
			c = input->map_points[i][j];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				fill_input(j, i, input, c);
			j++;
		}
		i++;
	}
	if (input->p_found == false)
	{
		player_error('N');
		exit(1);
	}
}
