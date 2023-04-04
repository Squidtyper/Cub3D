/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keystroke_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 11:46:57 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/04/04 11:46:58 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"
#include <math.h>

void	key_w(t_exe_info *img, t_obj_seen *wall, t_obj_seen *door)
{
	if (!is_wall(img->map_input->map_points[wall->ipy][wall->ipx_add_xo]))
		img->player.pos.x += img->player.delta.x;
	if (!is_wall(img->map_input->map_points[wall->ipy_add_yo][wall->ipx]))
		img->player.pos.y += img->player.delta.y;
	if (img->map_input->map_points[door->ipy][door->ipx_sub_xo] == 'O')
		img->map_input->map_points[door->ipy][door->ipx_sub_xo] = 'D';
	if (img->map_input->map_points[door->ipy_sub_yo][door->ipx] == 'O')
		img->map_input->map_points[door->ipy_sub_yo][door->ipx] = 'D';
}

void	key_s(t_exe_info *img, t_obj_seen *wall, t_obj_seen *door)
{
	if (!is_wall(img->map_input->map_points[wall->ipy][wall->ipx_sub_xo]))
		img->player.pos.x -= img->player.delta.x;
	if (!is_wall(img->map_input->map_points[wall->ipy_sub_yo][wall->ipx]))
		img->player.pos.y -= img->player.delta.y;
	if (img->map_input->map_points[door->ipy][door->ipx_add_xo] == 'O')
		img->map_input->map_points[door->ipy][door->ipx_add_xo] = 'D';
	if (img->map_input->map_points[door->ipy_add_yo][door->ipx] == 'O')
		img->map_input->map_points[door->ipy_add_yo][door->ipx] = 'D';
}

void	key_a(t_exe_info *img, t_obj_seen *wall, t_obj_seen *door)
{
	if (!is_wall(img->map_input->map_points[wall->ipy][wall->ipx_add_yo]))
		img->player.pos.x += img->player.delta.y;
	if (!is_wall(img->map_input->map_points[wall->ipy_sub_xo][wall->ipx]))
		img->player.pos.y -= img->player.delta.x;
	if (img->map_input->map_points[door->ipy][door->ipx_sub_yo] == 'O')
		img->map_input->map_points[door->ipy][door->ipx_sub_yo] = 'D';
	if (img->map_input->map_points[door->ipy_add_xo][door->ipx] == 'O')
		img->map_input->map_points[door->ipy_add_xo][door->ipx] = 'D';
}

void	key_d(t_exe_info *img, t_obj_seen *wall, t_obj_seen *door)
{
	if (!is_wall(img->map_input->map_points[wall->ipy][wall->ipx_sub_yo]))
		img->player.pos.x -= img->player.delta.y;
	if (!is_wall(img->map_input->map_points[wall->ipy_add_xo][wall->ipx]))
		img->player.pos.y += img->player.delta.x;
	if (img->map_input->map_points[door->ipy][door->ipx_add_yo] == 'O')
		img->map_input->map_points[door->ipy][door->ipx_add_yo] = 'D';
	if (img->map_input->map_points[door->ipy_sub_xo][door->ipx] == 'O')
		img->map_input->map_points[door->ipy_sub_xo][door->ipx] = 'D';
}

void	key_space(t_exe_info *info)
{
	t_obj_seen	door;

	door.offset.x = 0;
	door.offset.y = 0;
	if (info->player.delta.x < 0)
		door.offset.x = -(info->size / 2.5);
	else
		door.offset.x = (info->size / 2.5);
	if (info->player.delta.y < 0)
		door.offset.y = -(info->size / 2.5);
	else
		door.offset.y = (info->size / 2.5);
	door.ipx_add_xo = (info->player.pos.x + door.offset.x) / info->size;
	door.ipy_add_yo = (info->player.pos.y + door.offset.y) / info->size;
	door.ipy = info->player.pos.y / info->size;
	door.ipx = info->player.pos.x / info->size;
	if (info->map_input->map_points[door.ipy][door.ipx_add_xo] == 'D')
		info->map_input->map_points[door.ipy][door.ipx_add_xo] = 'O';
	if (info->map_input->map_points[door.ipy_add_yo][door.ipx] == 'D')
		info->map_input->map_points[door.ipy_add_yo][door.ipx] = 'O';
}
