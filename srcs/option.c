/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:52 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 21:17:50 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		this_color_modification(t_scene *scene, t_float3 *impact,
		t_visible *v, t_refl_refr *ref)
{
	int i;

	i = 0;
	if (scene->object[v->visible].color_state == CS_PERLIN
			|| scene->object[v->visible].color_state == CS_CHECKER
			|| (scene->object[v->visible].color_state == CS_TEXTURE
				&& scene->object[v->visible].texture[TEXTURE_COLOR]))
	{
		i = 0;
		while (i < APPLI_ALL)
		{
			if (g_apply_texture[i].type
					== scene->object[v->visible].type &&
					g_apply_texture[i].state
					== scene->object[v->visible].color_state &&
					g_apply_texture[i].used == CS_USED)
				ref->kd =
					(*g_apply_texture[i].f_text)(&scene->object[v->visible],
							impact, TEXTURE_COLOR);
			i++;
		}
	}
	else
		ref->kd = scene->object[v->visible].kd;
}

static void		this_normal_modification(t_scene *scene, t_visible *v,
		t_float3 *impact, t_float3 *real_normal)
{
	int			i;

	i = 0;
	while (i < APPLI_ALL)
	{
		if (g_apply_texture[i].type
				== scene->object[v->visible].type &&
				g_apply_texture[i].state
				== scene->object[v->visible].normal_state &&
				g_apply_texture[i].used == NS_USED)
			(*real_normal) =
				(*g_apply_texture[i].f_text)(&scene->object[v->visible],
						impact, TEXTURE_PERTU);
		i++;
	}
	(*real_normal).x = 2.0 * (1.0 - (*real_normal).x) + 1.0;
	(*real_normal).y = 2.0 * (*real_normal).y - 1.0;
	(*real_normal).z = -(2.0 * (*real_normal).z - 1.0);
	rt_vector_normalize(real_normal);
}

static void		this_ambient_modification(t_scene *scene, t_visible *v,
		t_refl_refr *ref)
{
	if (scene->object[v->visible].color_state == CS_TEXTURE
			&& scene->object[v->visible].texture[TEXTURE_COLOR])
		ref->ka = ref->kd;
}

void			apply_options(t_scene *scene, t_visible *v,
		t_refl_refr *ref, t_float3 *dir)
{
	t_float3	impact;
	t_float3	real_normal;

	if (dir)
		impact = rt_vector_impact(
				&scene->buffer[v->visible][ref->y][ref->x].origin,
				&scene->buffer[v->visible][ref->y][ref->x].vector, v->k);
	else
	{
		impact = rt_vector_impact(&v->ori, &v->vec, v->k);
		dir = &v->vec;
	}
	this_color_modification(scene, &impact, v, ref);
	if (scene->object[v->visible].normal_state == NS_TEXTURE
			&& scene->object[v->visible].texture[TEXTURE_PERTU])
	{
		this_normal_modification(scene, v, &impact, &real_normal);
		ref->normal = scene->object[v->visible].type
			== PLANE ? real_normal : rotate_normal(&real_normal,
					&(ref->normal), dir);
		rt_vector_normalize(&(ref->normal));
		rt_vector_reverse(&ref->normal);
	}
	this_ambient_modification(scene, v, ref);
}
