/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_parsing.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 19:50:02 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 22:05:00 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

typedef struct s_tex_all
{
	mlx_texture_t	*NO_tex;
	bool			NO_found;
	mlx_texture_t	*SO_tex;
	bool			SO_found;
	mlx_texture_t	*WE_tex;
	bool			WE_found;
	mlx_texture_t	*EA_tex;
	bool			EA_found;
}	t_tex_all;

void	clean_input(t_input *input)
{
	t_list *buf;

	buf = input->textures;
	if (input)
	{
		cleardarray(input->map_points);
		while (buf)
		{
			mlx_delete_texture((mlx_texture_t *)buf->content);
			buf = buf->next;
		}
		free(input->textures);
		free(input);
	}
}
