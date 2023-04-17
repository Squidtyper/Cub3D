/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keystroke.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 16:15:34 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/17 14:56:21 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	key_w(t_exe_info *img, t_obj_seen *set)
{
	if (!is_wall(img->map_input->map_points[set->ipy][set->ipx_add_xo]))
		img->player.pos.x += img->player.delta.x;
	if (!is_wall(img->map_input->map_points[set->ipy_add_yo][set->ipx]))
		img->player.pos.y += img->player.delta.y;
}

void	key_s(t_exe_info *img, t_obj_seen *set)
{
	if (!is_wall(img->map_input->map_points[set->ipy][set->ipx_sub_xo]))
		img->player.pos.x -= img->player.delta.x;
	if (!is_wall(img->map_input->map_points[set->ipy_sub_yo][set->ipx]))
		img->player.pos.y -= img->player.delta.y;
}

void	key_a(t_exe_info *img, t_obj_seen *set)
{
	if (!is_wall(img->map_input->map_points[set->ipy][set->ipx_add_yo]))
		img->player.pos.x += img->player.delta.y;
	if (!is_wall(img->map_input->map_points[set->ipy_sub_xo][set->ipx]))
		img->player.pos.y -= img->player.delta.x;
}

void	key_d(t_exe_info *img, t_obj_seen *set)
{
	if (!is_wall(img->map_input->map_points[set->ipy][set->ipx_sub_yo]))
		img->player.pos.x -= img->player.delta.y;
	if (!is_wall(img->map_input->map_points[set->ipy_add_xo][set->ipx]))
		img->player.pos.y += img->player.delta.x;
}
