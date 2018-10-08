/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurse_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:06 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:13:08 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	this_search_visible(t_scene *scene, t_recursive *iter, t_visible *v)
{
	t_impact	impact;
	t_float3	ori;
	t_float3	vec;
	size_t		i;

	i = 0;
	while (i < scene->num_obj)
	{
		rt_origin_object(&iter->origin, &scene->object[i], &ori);
		ori = rt_matrix_apply(&ori, scene->object[i].rotate.mat_i);
		vec = rt_matrix_apply(&iter->vector, scene->object[i].rotate.mat_i);
		(*g_colliders[scene->object[i].type])(&ori, &vec, &scene->object[i],
					&impact);
		if (i == 0)
			rt_impact_to_visible(&impact, v, 0);
		if (i && !rt_first_noticeable(v, &impact, i))
			;
		else
		{
			v->ori = ori;
			v->vec = vec;
		}
		i++;
	}
}

static void	this_set_data_impact(t_scene *scene, t_recursive *iter,
				t_refl_refr *ref, t_visible *v)
{
	ref->normal = rt_collider_normal(&scene->object[v->visible],
				&v->ori, &v->vec, v->k);
	ref->ka = scene->object[v->visible].ka;
	ref->kd = scene->object[v->visible].kd;
	ref->ks = scene->object[v->visible].ks;
	apply_options((t_scene*)scene, (t_visible*)v, ref, NULL);
	ref->normal = rt_matrix_apply(&ref->normal,
	scene->object[v->visible].rotate.mat);
	ref->impact[0] = rt_vector_impact(&iter->origin, &iter->vector, v->k);
	rt_float3_mult(&ref->ka, &scene->ambient.luminance, &ref->color);
}

static void	this_recurse_pixel_refraction(t_scnpxl norm, t_scene *scene,
				t_refl_refr *ref, t_recursive *iter)
{
	t_float3	ksi;

	ksi = (t_float3){.x = 1 - scene->object[norm.v->visible].ks.x,
					.y = 1 - scene->object[norm.v->visible].ks.y,
					.z = 1 - scene->object[norm.v->visible].ks.z};
	norm.loop = *iter;
	rt_float3_mult_float(&norm.loop.coeff,
		scene->object[norm.v->visible].transparency, &norm.loop.coeff);
	rt_float3_mult(&ksi, &norm.loop.coeff,
		&norm.loop.coeff);
	if (norm.loop.coeff.x > EPSILON || norm.loop.coeff.y > EPSILON
		|| norm.loop.coeff.z > EPSILON)
	{
		norm.loop.iter += 1;
		norm.loop.vector = rt_recurse_refraction(&iter->vector,
			&(*ref).normal, 1);
		norm.loop.origin = (*ref).impact[0];
		rt_add_queue(&norm.loop, norm.thread);
	}
}

static void	this_recurse_pixel(t_scene *scene, t_refl_refr *ref,
				t_scnpxl norm, t_recursive *iter)
{
	if (scene->object[norm.v->visible].transparency < 1)
	{
		norm.loop = *iter;
		rt_float3_mult_float(&norm.loop.coeff,
			1 - scene->object[norm.v->visible].transparency, &norm.loop.coeff);
		rt_float3_mult(&scene->object[norm.v->visible].ks,
			&norm.loop.coeff, &norm.loop.coeff);
		if (norm.loop.coeff.x > EPSILON || norm.loop.coeff.y > EPSILON
			|| norm.loop.coeff.z > EPSILON)
		{
			norm.loop.iter += 1;
			norm.loop.vector =
				rt_recurse_reflection(&iter->vector, &(*ref).normal);
			norm.loop.origin = (*ref).impact[0];
			rt_add_queue(&norm.loop, norm.thread);
		}
	}
	if (scene->object[norm.v->visible].transparency > 0)
		this_recurse_pixel_refraction(norm, scene, ref, iter);
}

t_float3	rt_recurse_pixel(t_recursive *iter, t_scene *scene, int thread)
{
	t_visible	v;
	t_refl_refr	ref;
	t_scnpxl	norm;

	norm = (t_scnpxl){.v = &v, .thread = thread};
	this_search_visible(scene, iter, &v);
	ref.color = (t_float3){.x = 0, .y = 0, .z = 0};
	if (v.visible >= 0 && (size_t)v.visible < scene->num_obj)
	{
		this_set_data_impact(scene, iter, &ref, &v);
		rt_look_lights(&ref, scene, &v, &iter->vector);
		rt_float3_mult(&iter->coeff, &ref.color, &ref.color);
		rt_float3_min(&ref.color, 0);
		this_recurse_pixel(scene, &ref, norm, iter);
	}
	return (ref.color);
}
