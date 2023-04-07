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
	t_list *buf;

	buf = input->textures;
	if (input)
	{
		cleardarray(input->map_points);
		while (buf)
		{
			mlx_delete_texture((mlx_texture_t *)buf->content);
			buf=buf->next;
		}
		free(input->textures);
		free(input);
	}
}

void	tex_clean(t_tex_all *tex)
{
	if (!tex)
		return ;
	if (tex->no_tex)
		mlx_delete_texture(tex->no_tex);
	if (tex->so_tex)
		mlx_delete_texture(tex->so_tex);
	if (tex->we_tex)
		mlx_delete_texture(tex->we_tex);
	if (tex->ea_tex)
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