/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:18 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:59:11 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_get_float4(xmlNodePtr cur, void *ptr, char *name)
{
	t_float4		*num;
	static char		tmp[2];

	tmp[1] = '\0';
	num = ptr;
	tmp[0] = name[0];
	rt_get_float(cur, &num->w, tmp);
	tmp[0] = name[1];
	rt_get_float(cur, &num->x, tmp);
	tmp[0] = name[2];
	rt_get_float(cur, &num->y, tmp);
	tmp[0] = name[3];
	rt_get_float(cur, &num->z, tmp);
}

void	rt_get_int(xmlNodePtr cur, void *ptr, char *name)
{
	xmlChar *tmp;
	int		*num;

	num = (int*)ptr;
	tmp = xmlGetProp(cur, (xmlChar*)name);
	if (tmp)
	{
		*num = ft_atoi((char*)tmp);
		xmlFree(tmp);
	}
}

void	rt_get_path(xmlNodePtr cur, void *ptr, char *name)
{
	char	**str;
	int		i;

	i = 0;
	str = (char**)ptr;
	(void)name;
	while (i < TEXTURE_ALL)
	{
		rt_get_string(cur, &str[i], g_texture[i].name);
		i++;
	}
}

void	rt_get_string(xmlNodePtr cur, void *ptr, char *name)
{
	xmlChar *tmp;
	char	**str;

	str = (char**)ptr;
	*str = NULL;
	tmp = xmlGetProp(cur, (xmlChar*)name);
	if (tmp)
	{
		if (xmlStrcmp(tmp, (xmlChar*)""))
		{
			*str = (char*)ft_strdup((char*)tmp);
			if (*str == NULL)
				rt_error(ERROR_MALLOC, __FILE__, __LINE__, "");
		}
		xmlFree(tmp);
	}
}
