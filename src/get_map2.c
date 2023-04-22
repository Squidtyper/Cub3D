/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 18:52:00 by lizhang       #+#    #+#                 */
/*   Updated: 2023/04/22 18:52:29 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*fill_map_line(char *content, unsigned int len)
{
	unsigned int	i;
	char			*to_fill;

	i = 0;
	len++;
	to_fill = (char *)malloc(sizeof(char) * (len + 1));
	while (content[i])
	{
		to_fill[i] = content[i];
		i++;
	}
	while (i < len)
	{
		to_fill[i] = ' ';
		i++;
	}
	to_fill[i] = '\0';
	return (to_fill);
}

unsigned int	get_map_width(t_list *map)
{
	t_list			*buf;
	unsigned int	len;
	unsigned int	width;

	buf = map;
	width = 0;
	while (buf)
	{
		len = ft_strlen((char *)buf->content);
		if (len > width)
			width = len;
		buf = buf->next;
	}
	return (width);
}

char	**convert_map(t_list *map, t_input *input)
{
	char			**array;
	t_list			*buf;
	unsigned int	i;

	buf = map;
	input->map_height = ft_lstsize(map);
	array = (char **)malloc(sizeof(char *) * (input->map_height + 1));
	input->map_width = get_map_width(map);
	i = 0;
	buf = map;
	while (i < input->map_height)
	{
		array[i] = fill_map_line((char *)buf->content, input->map_width);
		buf = buf->next;
		i++;
	}
	array[i] = NULL;
	ft_lstclear(&map, &free);
	return (array);
}
