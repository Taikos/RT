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

void	rt_fill_disk(xmlNodePtr cur, t_scene *scene, t_num *num, char *filename)
{
	scene->object[num->obj].type = DISK;
	rt_fill_object(cur->children, &scene->object[num->obj],
			USED_DISK, filename);
	num->obj += 1;
}

void	rt_fill_light(xmlNodePtr ptr, t_light *light, uint64_t used,
			char *filename)
{
	xmlNodePtr	cur;
	int			i;

	i = 0;
	rt_get_string(ptr->parent, &(light)->name, PARSE_NAME);
	while (i < LIGHT_PARAM)
	{
		cur = ptr;
		while (cur && g_light[i].used & used)
		{
			if (!xmlStrcmp(cur->name, (xmlChar*)g_light[i].text))
			{
				(*g_light[i].f_prop)(cur,
								(void*)((uint64_t)light + g_light[i].offset),
								g_light[i].type);
				break ;
			}
			cur = cur->next;
		}
		if (!cur)
			rt_error(ERROR_NO_TAG, filename, 0,
				"missing tags in <'type of light'>");
		i++;
	}
}

void	rt_fill_object(xmlNodePtr ptr, t_object *object, uint64_t used,
			char *filename)
{
	xmlNodePtr	cur;
	int			i;

	rt_get_string(ptr->parent, &(object)->name, PARSE_NAME);
	i = 0;
	while (i < OBJECT_PARAM)
	{
		cur = ptr;
		while (cur && g_object[i].used & used)
		{
			if (!xmlStrcmp(cur->name, (xmlChar*)g_object[i].text))
			{
				(*g_object[i].f_prop)(cur,
							(void*)((uint64_t)object + g_object[i].offset),
							g_object[i].type);
				break ;
			}
			cur = cur->next;
		}
		if (!cur)
			rt_error(ERROR_NO_TAG, filename, 0,
				"missing tags in <'type of object'>");
		i++;
	}
}

void	rt_fill_plane(xmlNodePtr cur, t_scene *scene, t_num *num,
			char *filename)
{
	scene->object[num->obj].type = PLANE;
	rt_fill_object(cur->children, &scene->object[num->obj], USED_PLANE,
			filename);
	num->obj += 1;
}

void	rt_fill_scene(t_scene *scene, xmlNodePtr cur, char *filename)
{
	t_num			num;
	int				i;

	num = (t_num){.amb = 0, .lum = 0, .cam = 0, .obj = 0};
	cur = cur->children;
	while (cur)
	{
		i = 0;
		while (i < SCENE_PARAM)
		{
			if (!xmlStrcmp(cur->name, (xmlChar*)g_scene[i].text)
				&& g_scene[i].f_tag)
			{
				(*g_scene[i].f_tag)(cur, scene, &num, filename);
				break ;
			}
			i++;
		}
		cur = cur->next;
	}
}
