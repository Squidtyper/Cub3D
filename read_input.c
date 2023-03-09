/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 15:40:57 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/09 18:07:09 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "cube3D.h"
# include <readline/readline.h>

int    open_file(char *name)
{
	int		fd_file;

	fd_file = open(name, O_RDONLY);
	if (fd_file < 0)
	{
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return(0);
	}
	return(fd_file);
}

char	*read_file(char *name)
{
	int		file_fd;
	char	*content;
	char	*buf;

	content = NULL;
	file_fd = open_file(name);
	buf = get_next_line(file_fd);
	while (buf)
	{
		content = join_free(content, buf);
		buf = get_next_line(file_fd);
	}
	return(content);
}

void	color_double(bool testvalue)
{
	if (testvalue == true)
	{
		printf("Error: double values for ceiling color or floor color found\n");
		exit(1);
	}
}

int	only_digits(char *str)
{
	int	i;
	int	n_digit;

	i = 0;
	n_digit = 0;
	while(str[i])
	{
		if(str[i] != ' ' && str[i]!='	' && ft_isdigit(str[i]) == 0)
			return (0);
		if (ft_isdigit(str[i]) == 1)
			n_digit++;
		i++;
	}
	if (n_digit == 0)
		return (0);
	return (1);
}

void	parse_color(char **words, t_input *input)
{
	int		r;
	int		g;
	int		b;
	char	**frag;

	frag = ft_space_split(words[0]);
	r = 0;
	if (!frag)
		mallocerr();
	if ((frag[1] && only_digits(frag[1]) == 0) || \
	only_digits(words[1]) == 0 ||only_digits(words[2]) == 0)
	{
		printf("Error: garbage data in color code found\n");
		exit(1);
	}
	if (frag[1])
		r = color_atoi(frag[1]);
	g = color_atoi(words[1]);
	b = color_atoi(words[2]);
	if (r > 255 || g > 255 || b > 255)
	{
		printf("Error: rgb color cannot exceed 0 - 255");
		exit(1);
	}
	if (ft_strncmp(frag[0], "C", 2) == 0)
	{
		color_double(input->c_found);
		input->c_color = r * 65536 + g * 256 + b;
		input->c_found = true;
	}
	if (ft_strncmp(frag[0], "F", 2) == 0)
	{
		color_double(input->f_found);
		input->f_color = r * 65536 + g * 256 + b;
		input->f_found = true;
	}
	cleardarray(frag);
}

void	find_color(t_input *input)
{
	char	**words;
	int		i;
	int		i2;

	i = 0;
	input->lines = ft_split(input->file_content, '\n');
	while (input->lines[i])
	{
		words = ft_split(input->lines[i], ',');
		if (!words)
			mallocerr();
		i2 = 0;
		while (words[i2])
			i2++;
		if (i2 == 3)
			parse_color(words, input);
		i++;
		cleardarray(words);
	}
}

void	pre_fill(t_input *input)
{
	input->file_content = NULL;
	input->lines = NULL;
	input->map_points = NULL;
	input->c_color = 0;
	input->f_color = 0;
	input->c_found = false;
	input->f_found =false;
	input->NO_tex = NULL;
	input->SO_tex = NULL;
	input->WE_tex = NULL;
	input->EA_tex = NULL;
	input->a_player = 0;
	input->p_found = false;
}

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

void	find_map(t_input *input)
{
	int		i;
	t_list	*map;
	t_list	*item;
	t_list	*buf;

	i = 0;
	map = NULL;
	while (input->lines[i])
	{
		if (ft_strlen(input->lines[i]) > 3 && only_digits(input->lines[i]) == 1)
			break ;
		i++;
	}
	while(input->lines[i] && ft_strlen(input->lines[i]) > 3 && valid_map_line(input->lines[i]) == 1)
	{
		item = ft_lstnew(ft_strdup(input->lines[i]));
		ft_lstadd_back(&map, item);
		i++;
	}
	buf = map;
	if (ft_lstsize(buf) < 3)
	{
		printf("Error: map does not suffice\n");
		exit(1);
	}
	input->map_points = convert_map(map, input);
}


t_input *parse(int ac, char **av)
{
	t_input	*input;

	ac_error(ac);
	input = (t_input *)malloc(sizeof(t_input));
	pre_fill(input);
	if (!input)
		mallocerr();
	input->file_content = read_file(av[1]);
	find_color(input);
	find_texture(input);
	find_map(input);
	return (input);
}
