/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_player.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 18:11:40 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/17 16:02:34 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <math.h>
#define _USE_MATH_DEFINES

void	player_error(char c)
{
	if (c == 'D')
		printf("Error: map contains more than one player\n");
	else if (c == 'N')
		printf("Error: player not found in map");
}

double	get_angle(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	if (c == 'E')
		return (0);
	if (c == 'S')
		return (M_PI / 2);
	if (c == 'W')
		return (M_PI);
	return (0);
}

void	fill_input(int x, int y, t_check *check, char c)
{
	if (check->p_found == true)
	{
		player_error('D');
		parsing_clean(check);
	}
	check->input->a_player = get_angle(c);
	check->input->player_x = x;
	check->input->player_y = y;
	check->p_found = true;
	check->input->map_points[y][x] = '0';
}

void	get_player(t_check *check)
{
	unsigned int	i;
	unsigned int	j;
	char			c;

	i = 0;
	if (!check->input->map_points)
		return ;
	while (i < check->input->map_height)
	{
		j = 0;
		while (j < check->input->map_width)
		{
			c = check->input->map_points[i][j];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				fill_input(j, i, check, c);
			j++;
		}
		i++;
	}
	if (check->p_found == false)
	{
		player_error('N');
		parsing_clean(check);
	}
}
