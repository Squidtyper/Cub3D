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

#include "parsing_bonus.h"

void	parsing_clean_bonus(t_check_bonus *checkb)
{
	t_check	*buf;

	buf = checkb->check;
	if (checkb->tex_bonus)
	{
		if (checkb->tex_bonus->door_found == true)
			mlx_delete_texture(checkb->tex_bonus->door_tex);
		free(checkb->tex_bonus);
	}
	free(checkb);
	parsing_clean(buf);
}
