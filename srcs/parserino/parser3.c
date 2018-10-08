/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:57:29 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:58:44 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_fill_ambient(xmlNodePtr cur, t_scene *scene, t_num *num,
		char *filename)
{
	scene->ambient.type = L_AMBIENT;
	rt_fill_light(cur->children, &scene->ambient, USED_AMBIENT, filename);
	num->amb += 1;
}

void	rt_fill_camera(xmlNodePtr ptr, t_scene *scene, t_num *num,
		char *filename)
{
	xmlNodePtr	cur;
	int			i;

	i = 0;
	rt_get_string(ptr, &scene->cam[num->cam].name, PARSE_NAME);
	ptr = ptr->children;
	while (i < CAM_PARAM)
	{
		cur = ptr;
		while (cur)
		{
			if (!xmlStrcmp(cur->name, (xmlChar*)g_cam[i].text))
			{
				(*g_cam[i].f_prop)(cur,
						(void*)((uint64_t) & scene->cam[num->cam]
							+ g_cam[i].offset), g_cam[i].type);
				break ;
			}
			cur = cur->next;
		}
		if (!cur)
			rt_error(ERROR_NO_TAG, filename, 0, "missing tags in <camera>");
		i++;
	}
	num->cam += 1;
}

void	rt_fill_cone(xmlNodePtr cur, t_scene *scene, t_num *num, char *filename)
{
	scene->object[num->obj].type = CONE;
	rt_fill_object(cur->children, &scene->object[num->obj],
			USED_CONE, filename);
	num->obj += 1;
}

void	rt_fill_cylinder(xmlNodePtr cur, t_scene *scene, t_num *num,
		char *filename)
{
	scene->object[num->obj].type = CYLINDER;
	rt_fill_object(cur->children, &scene->object[num->obj], USED_CYLINDER,
			filename);
	num->obj += 1;
}

void	rt_fill_directional(xmlNodePtr cur, t_scene *scene, t_num *num,
		char *filename)
{
	scene->light[num->lum].type = L_DIRECTIONAL;
	rt_fill_light(cur->children, &scene->light[num->lum], USED_DIRECTIONAL,
			filename);
	num->lum += 1;
}
