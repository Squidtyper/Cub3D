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

int	valid_map_line(char *str)
{
	int	i;
	int	n_digit;

	i = 0;
	n_digit = 0;
	while (str[i])
	{
		if (str[i] != 13 && str[i] != 32 && str[i] != '\n' && str[i] != 'N' && \
		str[i] != 'S' && str[i] != 'W' && str[i] != 'E' && \
		ft_isdigit(str[i]) == 0)
			return (0);
		if (ft_isdigit(str[i]) == 1)
			n_digit++;
		i++;
	}
	if (n_digit == 0)
		return (0);
	return (1);
}

void	map_basic_check(t_list *map, char **lines, int i, t_check *check)
{
	while (lines[i])
	{
		if ((ft_strlen(lines[i]) > 1 && !lines[i + 1]) || \
		valid_map_line(lines[i]) == 1)
		{
			if ((ft_strlen(lines[i]) && !lines[i + 1]))
				printf("Error: map is not a the end of the file.\n");
			else if (valid_map_line(lines[i]) == 1)
				printf("Error: map contains invalid line\n");
			ft_lstclear(&map, &free);
			parsing_clean(check);
		}
		i++;
	}
	if (ft_lstsize(map) < 3)
	{
		printf("Error: map does not suffice\n");
		ft_lstclear(&map, &free);
		parsing_clean(check);
	}
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
		if (valid_map_line(lines[i]) == 1)
			break ;
		i++;
	}
	while (lines[i] && ft_strlen(lines[i]) >= 3 && \
	valid_map_line(lines[i]) == 1)
	{
		item = ft_lstnew(rm_nl(lines[i]));
		ft_lstadd_back(&map, item);
		i++;
	}
	map_basic_check(map, lines, i, check);
	check->input->map_points = convert_map(map, check->input);
}
