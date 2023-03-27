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

#include "parsing_bonus.h"
#include <math.h>

void	fill_input_bonus(int x, int y, t_check *check, char c)
{
	if (check->p_found == true)
		player_error('D');
	check->input->a_player = get_angle(c);
	check->input->player_x = x;
	check->input->player_y = y;
	check->p_found = true;
	check->input->map_points[y][x] = '0';
}

void	get_player_bonus(t_check *check)
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
		exit(1);
	}
}
