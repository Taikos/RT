/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:18 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 19:03:32 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_fill_sphere(xmlNodePtr cur, t_scene *scene, t_num *num,
		char *filename)
{
	scene->object[num->obj].type = SPHERE;
	rt_fill_object(cur->children, &scene->object[num->obj],
			USED_SPHERE, filename);
	num->obj += 1;
}

void	rt_fill_spot(xmlNodePtr cur, t_scene *scene, t_num *num, char *filename)
{
	scene->light[num->lum].type = L_SPOT;
	rt_fill_light(cur->children, &scene->light[num->lum], USED_SPOT, filename);
	num->lum += 1;
}

void	rt_fill(xmlNodePtr cur, t_stock **stock, char *filename)
{
	int cur_scn;

	cur_scn = 0;
	while (cur)
	{
		if (!xmlStrcmp(cur->name, (xmlChar*)"scene"))
		{
			rt_get_string(cur, &(*stock)->scene[cur_scn].name, PARSE_NAME);
			rt_fill_scene(&(*stock)->scene[cur_scn], cur, filename);
			cur_scn++;
		}
		cur = cur->next;
	}
	(*stock)->cur_scn = 0;
}

void	rt_get_float(xmlNodePtr cur, void *ptr, char *name)
{
	xmlChar		*tmp;
	float		*num;

	num = (float*)ptr;
	tmp = xmlGetProp(cur, (xmlChar*)name);
	if (tmp)
	{
		*num = rt_atof((char*)tmp);
		xmlFree(tmp);
	}
}

void	rt_get_float3(xmlNodePtr cur, void *ptr, char *name)
{
	t_float3		*num;
	static char		tmp[2];

	num = ptr;
	tmp[1] = '\0';
	tmp[0] = name[0];
	rt_get_float(cur, &num->x, tmp);
	tmp[0] = name[1];
	rt_get_float(cur, &num->y, tmp);
	tmp[0] = name[2];
	rt_get_float(cur, &num->z, tmp);
}
