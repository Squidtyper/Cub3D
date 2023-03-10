/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_player.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 18:11:40 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/10 19:31:48 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	player_error(char c)
{
	if (c == 'D')
		printf("Error: map contains more than one player\n");
	else if (c == 'N')
		printf("Error: player not found in map");
	exit(1);
}

float	get_angle(char c)
{
	if (c == 'N')
		return (0);
	if (c == 'E')
		return (1.571);
	if (c == 'S')
		return (3.142);
	if (c == 'W')
		return (4.712);
    return (0);
}

void	get_player(t_input *input)
{
	unsigned int	i;
	unsigned int	j;
	char	c;

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
			{
				if (input->p_found == true)
					player_error('D');
				input->a_player = get_angle(c);
                input->player_x = j;
                input->player_y = i;
				input->p_found = true;
			}
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
