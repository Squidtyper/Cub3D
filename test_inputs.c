/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_inputs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:35:51 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/09 17:30:54 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void    test_inputs(t_input *input)
{
	int i;
	int j;

	i = 0;
	while(input->map_points[i])
	{
		j = 0;
		while (input->map_points[i][j])
		{
			printf("%c ", input->map_points[i][j]);
			j++;
		}
		i++;
	}
	if (input->NO_tex)
		printf("NO_tex successfully imported");
	else
		printf("NO_tex import is unsuccessful");
	if (input->SO_tex)
		printf("SO_tex successfully imported");
	else
		printf("SO_tex import is unsuccessful");
	if (input->WE_tex)
		printf("WE_tex successfully imported");
	else
		printf("WE_tex import is unsuccessful");
	if (input->EA_tex)
		printf("EA_tex successfully imported");
	else
		printf("EA_tex import is unsuccessful");
}