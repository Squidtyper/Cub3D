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

#include "parsing.h"

void	clean_input(t_input *input)
{
	t_list	*buf;
	t_list	*buf2;

	if (input)
	{
		cleardarray(input->map_points);
		if (input->textures)
		{
			buf = input->textures;
			while (buf)
			{
				mlx_delete_texture((mlx_texture_t *)buf->content);
				buf2 = buf;
				buf = buf->next;
				free(buf2);
			}
		}
		free(input);
	}
}

void	tex_clean(t_tex_all *tex)
{
	if (!tex)
		return ;
	if (tex->no_found == true)
		mlx_delete_texture(tex->no_tex);
	if (tex->so_found == true)
		mlx_delete_texture(tex->so_tex);
	if (tex->we_found == true)
		mlx_delete_texture(tex->we_tex);
	if (tex->ea_found == true)
		mlx_delete_texture(tex->ea_tex);
	free(tex);
}

void	parsing_clean(t_check *check)
{
	if (!check)
		return ;
	if (check->input)
	{
		clean_input(check->input);
		tex_clean(check->tex);
		free(check);
	}
	exit(1);
}
