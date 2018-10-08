/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 10:27:38 by arguerin          #+#    #+#             */
/*   Updated: 2017/06/21 17:38:24 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_cb		comb(char *tmp, char *rd)
{
	unsigned int	l1;
	unsigned int	l2;
	t_cb			cb;

	l1 = 0;
	l2 = 0;
	cb.len = 0;
	if (tmp != '\0')
		l1 = ft_strlen(tmp);
	if (rd != '\0')
		l2 = ft_strlen(rd);
	cb.track = (char *)malloc(sizeof(t_cb) * (l1 + l2 + 1));
	ft_memmove(cb.track, tmp, l1);
	ft_memmove(cb.track + l1, rd, l2);
	cb.track[l1 + l2] = '\0';
	free(tmp);
	while (cb.track[cb.len] != '\0' && cb.track[cb.len] != '\n')
		cb.len = cb.len + 1;
	if (cb.track[cb.len] != '\n')
		cb.len = -1;
	else
		cb.track[cb.len] = '\0';
	return (cb);
}

static int		convert(char **line, char **tmp, char **rd)
{
	int		len;
	t_cb	cb;
	char	*free_me;

	cb = comb(*tmp, *rd);
	*tmp = cb.track;
	len = cb.len;
	if (len >= 0)
	{
		*line = ft_strdup(*tmp);
		free_me = *tmp;
		*tmp = ft_strdup(*tmp + cb.len + 1);
		free(free_me);
		return (1);
	}
	else
		return (0);
}

int				get_next_line(int const fd, char **line)
{
	char		*rd;
	int			get;
	static char	*tmp[BUFF_SIZE];

	rd = ft_strnew(BUFF_SIZE);
	if (fd < 0 || fd >= 10240 || read(fd, rd, 0) < 0 || BUFF_SIZE <= 0)
		return (-1);
	while (read(fd, rd, BUFF_SIZE) > 0)
	{
		get = convert(line, &tmp[fd], &rd);
		free(rd);
		if (get == 1)
			return (get);
		rd = ft_strnew(BUFF_SIZE);
	}
	get = convert(line, &tmp[fd], &rd);
	if (get == 1)
		return (1);
	else if (ft_strlen(tmp[fd]) > 0)
	{
		*line = ft_strdup(tmp[fd]);
		ft_strdel(&tmp[fd]);
		return (1);
	}
	return (get);
}
