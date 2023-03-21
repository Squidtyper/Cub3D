/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 18:13:19 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 21:36:48 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D_bonus.h"

char	*fill_map_line(char *content, unsigned int len)
{
	unsigned int	i;
	char			*to_fill;

	i = 0;
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

int	valid_map_line(char *str)
{
	int	i;
	int	n_digit;

	i = 0;
	n_digit = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '	' && str[i] != 'N' && str[i] != 'S' \
		&& str[i] != 'W' && str[i] != 'E' && str[i] != 'G' &&ft_isdigit(str[i]) == 0)
			return (0);
		if (ft_isdigit(str[i]) == 1)
			n_digit++;
		i++;
	}
	if (n_digit == 0)
		return (0);
	return (1);
}
