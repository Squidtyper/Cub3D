/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 18:13:19 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 16:16:52 by lizhang       ########   odam.nl         */
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

int	valid_map_line(char *str)
{
	int	i;
	int	n_digit;

	i = 0;
	n_digit = 0;
	while (str[i])
	{
		if (str[i] != 13 && str[i] != 32 && str[i] != 'N' && str[i] != 'S' \
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

void	find_map(t_check *check, char **lines)
{
	int		i;
	t_list	*map;
	t_list	*item;

	i = 0;
	map = NULL;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 3 && valid_map_line(lines[i]) == 1)
			break ;
		i++;
	}
	while (lines[i] && ft_strlen(lines[i]) > 3 && \
	valid_map_line(lines[i]) == 1)
	{
		item = ft_lstnew(ft_strdup(lines[i]));
		ft_lstadd_back(&map, item);
		i++;
	}
	if (ft_lstsize(map) < 3)
	{
		printf("Error: map does not suffice\n");
		exit(1);
	}
	check->input->map_points = convert_map(map, check->input);
}
