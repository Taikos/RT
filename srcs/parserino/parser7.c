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

void			rt_put_t_float_fd(void *ptr, char *vname, char *tname, int fd)
{
	float		*value;
	int			indent;

	value = ptr;
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
	rt_putfloat_fd(*value, fd);
	ft_putstr_fd("\"", fd);
	ft_putstr_fd("/>\n", fd);
}

static void		this_put_t_float3_fd(t_float3 *value, char *vname, int fd)
{
	if (value->y != -INFINITY && value->y != INFINITY)
	{
		ft_putstr_fd(" ", fd);
		ft_putchar_fd(vname[1], fd);
		ft_putstr_fd("=\"", fd);
		rt_putfloat_fd(value->y, fd);
		ft_putstr_fd("\"", fd);
	}
	if (value->z != -INFINITY && value->z != INFINITY)
	{
		ft_putstr_fd(" ", fd);
		ft_putchar_fd(vname[2], fd);
		ft_putstr_fd("=\"", fd);
		rt_putfloat_fd(value->z, fd);
		ft_putstr_fd("\"", fd);
	}
	ft_putstr_fd("/>\n", fd);
}

void			rt_put_t_float3_fd(void *ptr, char *vname, char *tname, int fd)
{
	t_float3	*value;
	int			indent;

	value = ptr;
	indent = 3;
	if (!vname || ft_strlen(vname) < 3)
		rt_error(ERROR_DEF_SAVE, "output.xml", 0, "undetected value name");
	while (indent-- > 0)
		ft_putstr_fd("\t", fd);
	ft_putstr_fd("<", fd);
	ft_putstr_fd(tname, fd);
	if (value->x != -INFINITY && value->x != INFINITY)
	{
		ft_putstr_fd(" ", fd);
		ft_putchar_fd(vname[0], fd);
		ft_putstr_fd("=\"", fd);
		rt_putfloat_fd(value->x, fd);
		ft_putstr_fd("\"", fd);
	}
	this_put_t_float3_fd(value, vname, fd);
}

static void		this_vive_la_norme(t_float3 convert, int fd)
{
	rt_putfloat_fd(convert.z, fd);
	ft_putstr_fd("\"/>\n", fd);
}

void			rt_put_t_float4_fd(void *ptr, char *vname, char *tname, int fd)
{
	t_float4	*value;
	t_float3	convert;
	int			indent;

	value = ptr;
	indent = 3;
	if (!vname || ft_strlen(vname) < 4)
		rt_error(ERROR_DEF_SAVE, "output.xml", 0, "undetected value name");
	while (indent-- > 0)
		ft_putstr_fd("\t", fd);
	rt_quaternion_to_euler(&convert.x, &convert.y, &convert.z, value);
	ft_putstr_fd("<", fd);
	ft_putstr_fd(tname, fd);
	ft_putstr_fd(" ", fd);
	ft_putchar_fd(vname[1], fd);
	ft_putstr_fd("=\"", fd);
	rt_putfloat_fd(convert.x, fd);
	ft_putstr_fd("\" ", fd);
	ft_putchar_fd(vname[2], fd);
	ft_putstr_fd("=\"", fd);
	rt_putfloat_fd(convert.y, fd);
	ft_putstr_fd("\" ", fd);
	ft_putchar_fd(vname[3], fd);
	ft_putstr_fd("=\"", fd);
	this_vive_la_norme(convert, fd);
}
