/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 15:40:57 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/06 19:11:14 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "cube3D.h"
# include <readline/readline.h>

void	cleardarray(char **array)
{
	int	count;

	count = 0;
	if (!array || array == NULL)
		return ;
	while (array[count])
	{
		free(array[count]);
		count++;
	}
	if (array)
		free(array);
}

char	*join_free(char *str1, char *str2)
{
	char *newstr;

	if (!str1)
		return(str2);
	newstr = ft_strjoin(str1, str2);
	if (!newstr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	free(str1);
	free(str2);
	return(newstr);
}

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

void	parse_color(char **words, t_input *input)
{
	int		r;
	int		g;
	int		b;
	char	**frag;

	frag = ft_space_split(words[0]);
	if (!frag)
		mallocerr();
	if (frag[1])
		r = color_atoi(frag[1]);
	g = color_atoi(words[1]);
	b = color_atoi(words[2]);
	if (ft_strncmp(frag[0], "C", 2) == 0)
		input->c_color = r * 65536 + g * 256 + b;
	if (ft_strncmp(frag[0], "F", 2) == 0)
		input->f_color = r * 65536 + g * 256 + b;
	cleardarray(frag);
}

t_input	*find_color(t_input *input)
{
	char	**lines;
	char	**words;
	int		i;
	int		i2;

	i = 0;
	lines = ft_split(input->file_content, '\n');
	while (lines[i])
	{
		words = ft_split(lines[i], ',');
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
	return (input);
}

t_input *parse(int ac, char **av)
{
	t_input	*input;

	ac_error(ac);
	input = (t_input *)malloc(sizeof(t_input));
	if (!input)
		mallocerr();
	input->file_content = read_file(av[1]);
	find_color(input);
	return (input);
}