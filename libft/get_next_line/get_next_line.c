/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 21:07:45 by lizhang       #+#    #+#                 */
/*   Updated: 2022/03/15 18:32:25 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*fstr;
	static char	last[BUFFER_SIZE + 1];
	size_t		nxt;
	size_t		count;
	char		*rline;

	if (fd < 0)
		return (NULL);
	fstr = ft_gnlfstr(fd, last);
	if (!fstr)
		return (NULL);
	rline = ft_gnlline(fstr);
	nxt = ft_gnlstrlen(rline);
	count = 0;
	while (fstr[nxt + count])
	{
		last[count] = fstr[nxt + count];
		count++;
	}
	last[count] = '\0';
	free(fstr);
	return (rline);
}
