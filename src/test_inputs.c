/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_inputs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:35:51 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/17 16:02:51 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	test_var(t_check *check)
{
	if (!check->input->map_points || !check->tex || check->c_found == false || \
	check->f_found == false || check->p_found == false)
	{
		printf("Error: information incomplete. Cannot start Cub3D");
		exit(1);
	}
}

void    test_inputs(t_check *check)
{
	unsigned int i;
	unsigned int j;

	test_var(check);
	boundary_test(check->input->map_points, check->input->map_height, \
	check->input->map_width);
	i = 0;
	while(i < check->input->map_height)
	{
		j = 0;
		while (j < check->input->map_width)
		{
			printf("%c ", check->input->map_points[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("map width: %d, map height: %d\n", check->input->map_width, check->input->map_height);
	printf("ceiling color: 0x%llX, floor color: 0x%llX\n", check->input->c_color, check->input->f_color);
}