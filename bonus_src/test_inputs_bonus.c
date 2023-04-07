/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_inputs_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:35:51 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 22:05:15 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	test_ghost(t_check_bonus *checkb)
{
	int i;
	int j;
	i = 0;

	while (checkb->check->input->map_points[i])
	{
		j = 0;
		while(checkb->check->input->map_points[i][j])
		{
			if (checkb->check->input->map_points[i][j] == 'G')
			{
				printf("Error: Sprite in map not supported\n");
				parsing_clean(checkb->check);
				free(checkb);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void    test_inputs_bonus(t_check_bonus *checkb)
{
	unsigned int i;
	unsigned int j;

	test_var(checkb->check);
	boundary_test_bonus(checkb->check->input->map_points, checkb->check->input->map_height, \
	checkb->check->input->map_width);
	test_ghost(checkb);
	i = 0;
	while(i < checkb->check->input->map_height)
	{
		j = 0;
		while (j < checkb->check->input->map_width)
		{
			write(1, &checkb->check->input->map_points[i][j], 1);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("map width: %d, map height: %d\n", checkb->check->input->map_width, checkb->check->input->map_height);
	printf("ceiling color: 0x%llX, floor color: 0x%llX\n", checkb->check->input->c_color, checkb->check->input->f_color);
}