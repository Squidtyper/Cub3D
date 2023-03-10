/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 18:13:19 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/10 20:17:34 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	fill_map_line(char *to_fill, char *content, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while(content[i])
	{
		to_fill[i] = content[i];
		i++;
	}
	while (i < len - 1)
	{
		to_fill[i] = ' ';
		i++;
	}
	to_fill[i] = '\0';
}

char	**convert_map(t_list *map, t_input *input)
{
	char			**array;
	t_list			*buf;
	unsigned int	len;
	unsigned int	i;

	buf = map;
	input->map_height = ft_lstsize(buf);
	array = (char **)malloc(sizeof(char *) * (input->map_height + 1));
	buf = map;
	input->map_width = 0;
	while (buf)
	{
		len = ft_strlen((char *)buf->content);
		if(len > input->map_width)
			input->map_width = len;
		buf = buf->next;
	}
	i = 0;
	buf = map;
	while (i < input->map_height)
	{
		array[i] = (char *)malloc(sizeof(char) * (input->map_width +1));
		fill_map_line(array[i], (char *)buf->content, input->map_width + 1);
		buf = buf->next;
		i++;
	}
    array[i] = NULL;
	return (array);
}

int	valid_map_line(char *str)
{
	int	i;
	int	n_digit;

	i = 0;
	n_digit = 0;
	while(str[i])
	{
		if(str[i] != ' ' && str[i] !='	' && str[i] != 'N' && str[i] != 'S' \
		&& str[i] != 'W' && str[i] != 'E' && ft_isdigit(str[i]) == 0)
			return (0);
		if (ft_isdigit(str[i]) == 1)
			n_digit++;
		i++;
	}
	if (n_digit == 0)
		return (0);
	return (1);
}
