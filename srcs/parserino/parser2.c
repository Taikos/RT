/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:54:04 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:54:54 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_check_scene(t_num *num, xmlNodePtr cur, char *filename)
{
	int i;

	*num = (t_num){.amb = 0, .lum = 0, .cam = 0, .obj = 0};
	if (!cur)
		rt_error(ERROR_NO_TAG, filename, 0, "<.../>");
	while (cur)
	{
		i = 0;
		while (i < SCENE_PARAM)
		{
			if (!xmlStrcmp(cur->name, (xmlChar*)g_scene[i].text))
			{
				*((int*)((uint64_t)num + g_scene[i].offset)) += 1;
			}
			i++;
		}
		cur = cur->next;
	}
}

void	rt_default_camera(t_cam *camera)
{
	ft_memset(camera, 0, sizeof(t_cam));
	camera->pitch = 1;
	camera->moved = MOVMENT_ALL;
	camera->alpha = 0.157;
	camera->fov = 1.57;
	camera->axis_x = (t_float3){.x = 1, .y = 0, .z = 0};
	camera->axis_y = (t_float3){.x = 0, .y = 1, .z = 0};
	camera->axis_z = (t_float3){.x = 0, .y = 0, .z = 1};
}

void	rt_default_light(t_light *light)
{
	ft_memset(light, 0, sizeof(t_light));
	light->intensity = 0.1;
	light->ray = 0.1;
	light->color = (t_float3){.x = 1, .y = 1, .z = 1};
}

void	rt_default_object(t_object *object)
{
	ft_memset(object, 0, sizeof(t_object));
	object->ray = 1;
	object->limit_min = (t_float3){.x = -INFINITY, .y = -INFINITY,
						.z = -INFINITY};
	object->limit_max = (t_float3){.x = INFINITY, .y = INFINITY, .z = INFINITY};
}

void	rt_default_scene(t_stock *stock)
{
	size_t		cur_scn;
	size_t		cur_obj;
	size_t		cur_cam;
	size_t		cur_lum;

	cur_scn = 0;
	while (cur_scn < stock->num_scn)
	{
		cur_obj = 0;
		cur_lum = 0;
		cur_cam = 0;
		while (cur_obj < stock->scene[cur_scn].num_obj)
			rt_default_object(&stock->scene[cur_scn].object[cur_obj++]);
		while (cur_lum < stock->scene[cur_scn].num_lum)
			rt_default_light(&stock->scene[cur_scn].light[cur_lum++]);
		while (cur_cam < stock->scene[cur_scn].num_cam)
			rt_default_camera(&stock->scene[cur_scn].cam[cur_cam++]);
		rt_default_light(&stock->scene[cur_scn].ambient);
		cur_scn++;
	}
}
