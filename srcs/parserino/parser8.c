/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:18 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 19:12:13 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_put_end_tag(char *type, int indent, int fd)
{
	while (indent-- > 0)
		ft_putstr_fd("\t", fd);
	ft_putstr_fd("</", fd);
	ft_putstr_fd(type, fd);
	ft_putstr_fd(">\n", fd);
}

void	rt_put_path_fd(void *ptr, char *vname, char *tname, int fd)
{
	char		**value;
	int			indent;
	int			i;

	value = (char **)ptr;
	indent = 3;
	(void)vname;
	while (indent-- > 0)
		ft_putstr_fd("\t", fd);
	ft_putstr_fd("<", fd);
	ft_putstr_fd(tname, fd);
	i = 0;
	while (i < TEXTURE_ALL)
	{
		if (value[i] && ft_strcmp(value[i], ""))
		{
			ft_putstr_fd(" ", fd);
			ft_putstr_fd(g_texture[i].name, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(value[i], fd);
			ft_putstr_fd("\"", fd);
		}
		i++;
	}
	ft_putstr_fd("/>\n", fd);
}

void	rt_put_start_tag_name(char *type, char *name, int indent, int fd)
{
	while (indent-- > 0)
		ft_putstr_fd("\t", fd);
	ft_putstr_fd("<", fd);
	ft_putstr_fd(type, fd);
	if (name && ft_strcmp(name, ""))
	{
		ft_putstr_fd(" name=\"", fd);
		ft_putstr_fd(name, fd);
		ft_putstr_fd("\"", fd);
	}
	ft_putstr_fd(">\n", fd);
}

void	rt_put_string_fd(void *ptr, char *vname, char *tname, int fd)
{
	char		**value;
	int			indent;

	value = (char**)ptr;
	indent = 3;
	if (!vname || ft_strlen(vname) < 1)
		rt_error(ERROR_DEF_SAVE, "output.xml", 0, "undetected value name");
	while (indent-- > 0)
		ft_putstr_fd("\t", fd);
	ft_putstr_fd("<", fd);
	ft_putstr_fd(tname, fd);
	ft_putstr_fd(" ", fd);
	ft_putstr_fd(vname, fd);
	ft_putstr_fd("=\"", fd);
	ft_putstr_fd(*value, fd);
	ft_putstr_fd("\"/>\n", fd);
}
