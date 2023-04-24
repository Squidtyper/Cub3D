/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   boundary_test.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 18:36:25 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/17 16:04:22 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	test_around(char **map, unsigned int i, unsigned int j)
{
	if (ft_strchr("01NSWE", map[i - 1][j]) == NULL || \
	ft_strchr("01NSWE", map[i - 1][j - 1]) == NULL || \
	ft_strchr("01NSWE", map[i - 1][j + 1]) == NULL || \
	ft_strchr("01NSWE", map[i][j - 1]) == NULL || \
	ft_strchr("01NSWE", map[i][j + 1]) == NULL || \
	ft_strchr("01NSWE", map[i + 1][j - 1]) == NULL || \
	ft_strchr("01NSWE", map[i + 1][j]) == NULL || \
	ft_strchr("01NSWE", map[i + 1][j + 1]) == NULL)
		return (false);
	return (true);
}

bool	boundary_test(char **m_p, unsigned int height, unsigned int width)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (ft_strchr("0NSWE", m_p[i][j]) != NULL)
			{
				if (i == 0 || i == (height - 1) || j == 0 || j == (width - 1) \
				|| test_around(m_p, i, j) == false)
				{
					printf("Error: map is not closed/has unexpected element\n");
					return (false);
				}
			}
			j++;
		}
		i++;
	}
	return (true);
}
