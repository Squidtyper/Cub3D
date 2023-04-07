/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   import_textures_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 17:32:02 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 22:07:41 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	get_texture_bonus(t_tex_bonus *tex_bonus)
{
	tex_bonus->door_tex = open_texture(DOORPNG);
	tex_bonus->door_found = true;
}

void	find_texture_bonus(t_check_bonus *checkb, char **lines)
{
	find_texture(checkb->check, lines);
	checkb->tex_bonus = (t_tex_bonus *)malloc(sizeof(t_tex_bonus));
	if (!checkb->tex_bonus)
		mallocerr();
	checkb->tex_bonus->door_found = false;
	get_texture_bonus(checkb->tex_bonus);
	ft_lstadd_back(&checkb->check->input->textures, \
	ft_lstnew(checkb->tex_bonus->door_tex));
	free(checkb->tex_bonus);
	checkb->tex_bonus = NULL;
}
