/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 15:40:57 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/17 16:00:05 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <errno.h>

int	open_file(char *name)
{
	int		fd_file;

	fd_file = open(name, O_RDONLY);
	if (fd_file <= 0)
	{
		printf("Error: %s: %s\n", name, strerror(errno));
		exit(1);
	}
	return (fd_file);
}

char	*read_file(char *name)
{
	int		file_fd;
	char	*content;
	char	*buf;

	content = NULL;
	if (ft_strncmp(name + ((ft_strlen(name) - 4)), ".cub", 4) != 0)
	{
		printf("Error: %s: file is not .cub format", name);
		exit(1);
	}
	file_fd = open_file(name);
	if (file_fd <= 0)
	{
		printf("Error: %s: %s\n", name, strerror(errno));
		exit(1);
	}
	buf = get_next_line(file_fd);
	while (buf)
	{
		content = join_free(content, buf);
		buf = get_next_line(file_fd);
	}
	return (content);
}

void	pre_fill(t_check *check)
{
	check->input = (t_input *)malloc(sizeof(t_input));
	if (!check->input)
		mallocerr();
	check->input->map_points = NULL;
	check->input->map_width = 0;
	check->input->map_height = 0;
	check->input->textures = NULL;
	check->c_found = false;
	check->f_found = false;
	check->tex = NULL;
	check->p_found = false;
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
		if (ft_strlen(lines[i]) > 3 && only_digits(lines[i]) == 1)
			break ;
		i++;
	}
	printf("valid map lines return %d\n", valid_map_line(lines[i]));
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

t_input	*parse(int ac, char **av)
{
	t_check	*check;
	char	*file_content;
	char	**lines;
	t_input	*input_r;

	ac_error(ac);
	check = (t_check *)malloc(sizeof(t_check));
	if (!check)
		mallocerr();
	input_r = check->input;
	pre_fill(check);
	file_content = read_file(av[1]);
	lines = ft_split(file_content, '\n');
	if (!lines)
		mallocerr();
	free(file_content);
	find_color(check, lines);
	find_texture(check, lines);
	find_map(check, lines);
	cleardarray(lines);
	get_player(check);
	test_inputs(check);
	free(check);
	return (input_r);
}
