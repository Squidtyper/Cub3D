/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 21:03:33 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/17 15:24:54 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
size_t	ft_gnlstrlen(char *str);
char	*ft_gnlstrjoin(char *str1, char *str2);
int		ft_gnlnl(char *str);
char	*ft_gnlline(char *fstr);
char	*ft_gnlfstr(int fd, char *last);
#endif
