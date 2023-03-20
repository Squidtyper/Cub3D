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

#include "cube3D_bonus.h"
#include <stdio.h>

void    test_inputs(t_input *input)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while(i < input->map_height)
	{
		j = 0;
		while (j < input->map_width)
		{
			printf("%c ", input->map_points[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("map width: %d, map height: %d\n", input->map_width, input->map_height);
	printf("ceiling color: 0x%llX, floor color: 0x%llX\n", input->c_color, input->f_color);
	if (input->NO_tex)
		printf("NO_tex successfully imported\n");
	else
		printf("NO_tex import is unsuccessful\n");
	if (input->SO_tex)
		printf("SO_tex successfully imported\n");
	else
		printf("SO_tex import is unsuccessful\n");
	if (input->WE_tex)
		printf("WE_tex successfully imported\n");
	else
		printf("WE_tex import is unsuccessful\n");
	if (input->EA_tex)
		printf("EA_tex successfully imported\n");
	else
		printf("EA_tex import is unsuccessful\n");
	if (input->door_tex)
		printf("door_tex successfully imported\n");
	else
		printf("door_tex import is unsuccessful\n");
	if (input->sprite_tex)
		printf("sprite_tex successfully imported\n");
	else
		printf("sprite import is unsuccessful\n");
}