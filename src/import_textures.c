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
#include <errno.h>

mlx_texture_t	*open_texture(char *path)
{
	int				fd;
	mlx_texture_t	*tex;

	path = clear_str_space(path);
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
	free(path);
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
		texture_error(col->no_found, "NO");
		col->no_tex = open_texture(words[1]);
		col->no_found = true;
	}
	if (ft_strncmp(words[0], "SO", 3) == 0)
	{
		texture_error(col->so_found, "SO");
		col->so_tex = open_texture(words[1]);
		col->so_found = true;
	}
	if (ft_strncmp(words[0], "WE", 3) == 0)
	{
		texture_error(col->we_found, "WE");
		col->we_tex = open_texture(words[1]);
		col->we_found = true;
	}
	if (ft_strncmp(words[0], "EA", 3) == 0)
	{
		texture_error(col->ea_found, "EA");
		col->ea_tex = open_texture(words[1]);
		col->ea_found = true;
	}
}

t_list	*texture_to_list(t_tex_all *col)
{
	t_list	*textures;

	textures = ft_lstnew(col->no_tex);
	ft_lstadd_back(&textures, ft_lstnew(col->so_tex));
	ft_lstadd_back(&textures, ft_lstnew(col->we_tex));
	ft_lstadd_back(&textures, ft_lstnew(col->ea_tex));
	return (textures);
}

void	find_texture(t_check *check, char **lines)
{
	int			i;
	char		**words;

	i = 0;
	check->tex = (t_tex_all *)malloc(sizeof(t_tex_all));
	check->tex->no_found = false;
	check->tex->ea_found = false;
	check->tex->so_found = false;
	check->tex->we_found = false;
	while (lines[i])
	{
		words = ft_space_split(lines[i]);
		if (!words)
			mallocerr();
		if (words[0])
			get_texture(check->tex, words);
		cleardarray(words);
		i++;
	}
	check->input->textures = texture_to_list(check->tex);
	free(check->tex);
	check->tex = NULL;
}
