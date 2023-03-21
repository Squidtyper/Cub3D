/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_parsing_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 19:50:02 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 21:46:58 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D_bonus.h"

void	clean_input(t_input *input)
{
	if (input)
	{
		free(input->file_content);
		cleardarray(input->lines);
		cleardarray(input->map_points);
		mlx_delete_texture(input->NO_tex);
		mlx_delete_texture(input->SO_tex);
		mlx_delete_texture(input->WE_tex);
		mlx_delete_texture(input->EA_tex);
		mlx_delete_texture(input->door_tex);
		mlx_delete_texture(input->sprite_tex);
		free(input);
	}
}
