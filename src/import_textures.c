/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   import_textures.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 17:32:02 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 16:10:05 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>
#include <errno.h>

mlx_texture_t	*open_texture(char *path)
{
	int				fd;
	mlx_texture_t	*tex;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
	{
		printf("Error: %s: %s\n", path, strerror(errno));
		exit(1);
	}
	close(fd);
	tex = mlx_load_png(path);
	if (tex == NULL)
	{
		printf("Error: %s: file is not a png file.\n", path);
		exit(1);
	}
	return (tex);
}

void	texture_error(bool testvalue, char *what)
{
	if (testvalue == true)
	{
		printf("Error: double %s texture in input\n", what);
		exit(1);
	}
}

void	get_texture(t_tex_all *col, char **words)
{
	if (ft_strncmp(words[0], "NO", 3) == 0)
	{
		texture_error(col->NO_found, "NO");
		col->NO_tex = open_texture(words[1]);
		col->NO_found = true;
	}
	if (ft_strncmp(words[0], "SO", 3) == 0)
	{
		texture_error(col->SO_found, "SO");
		col->SO_tex = open_texture(words[1]);
		col->SO_found = true;
	}
	if (ft_strncmp(words[0], "WE", 3) == 0)
	{
		texture_error(col->WE_found, "WE");
		col->WE_tex = open_texture(words[1]);
		col->WE_found = true;
	}
	if (ft_strncmp(words[0], "EA", 3) == 0)
	{
		texture_error(col->EA_found, "EA");
		col->EA_tex = open_texture(words[1]);
		col->EA_found = true;
	}
}

t_list	*texture_to_list(t_tex_all *col)
{
	t_list	*textures;
	
	textures = ft_lstnew(col->NO_tex);
	ft_lstadd_back(&textures, ft_lstnew(col->SO_tex));
	ft_lstadd_back(&textures, ft_lstnew(col->WE_tex));
	ft_lstadd_back(&textures, ft_lstnew(col->EA_tex));
	return (textures);
}

void	find_texture(t_input *input, t_f_con *f_con)
{
	int			i;
	char		**words;
	t_tex_all	*col;

	i = 0;
	col = (t_tex_all *)malloc(sizeof(t_tex_all));
	col->NO_found = false;
	col->EA_found = false;
	col->SO_found = false;
	col->WE_found = false;
	while (f_con->lines[i])
	{
		words = ft_space_split(f_con->lines[i]);
		get_texture(col, words);
		cleardarray(words);
		i++;
	}
	input->textures = texture_to_list(col);
	free(col);
}
