/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_effect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:55 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 20:37:27 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				calc_fb(t_sdl *win, int x, int y)
{
	int			b1;
	int			b2;
	int			fb;

	b1 = (get_color_pixel(win, x, y, B));
	b2 = (get_color_pixel(win, (x + 1 >
					(int)win->scene.x_win ? x : x + 1), y, B));
	fb = b1 - b2;
	return (fb);
}

int				rt_impact_to_light(t_float3 *impact, t_light *light,
		t_scene *scene, t_refl_refr *ref)
{
	size_t		n;
	float		len;
	t_float3	tmp[2];
	t_impact	i;
	t_visible	v;

	n = 0;
	ref->light = (t_float3){.x = light->pos.x - impact->x, .y = light->pos.y -
		impact->y, .z = light->pos.z - impact->z};
	len = rt_vector_length(&ref->light);
	rt_vector_normalize(&ref->light);
	while (n < scene->num_obj)
	{
		rt_origin_object(impact, &scene->object[n], &tmp[0]);
		tmp[0] = rt_matrix_apply(&tmp[0], scene->object[n].rotate.mat_i);
		tmp[1] = rt_matrix_apply(&ref->light, scene->object[n].rotate.mat_i);
		(*g_colliders[scene->object[n].type])(&tmp[0],
				&tmp[1], &scene->object[n], &i);
		rt_impact_to_visible(&i, &v, n);
		if (v.k + light->ray <= len - light->ray &&
				(v.k > (v.visible == ref->visible ? EPSILON : 0)))
			return (TRUE);
		n++;
	}
	return (FALSE);
}

static void		this_impact_to_light_transparency(const t_scene *scene,
		size_t n, t_float3 *transparency_v2, t_float3 tmp[3])
{
	t_float3	ksi;

	ksi = (t_float3){.x = 1 - scene->object[n].ks.x,
		.y = 1 - scene->object[n].ks.y,
		.z = 1 - scene->object[n].ks.z};
	rt_float3_mult_float(&ksi,
			scene->object[n].transparency, &tmp[2]);
	rt_float3_mult(transparency_v2, &tmp[2], transparency_v2);
}

t_float3		rt_impact_to_light_directional(const t_float3 *impact,
		const t_light *light, const t_scene *scene, t_refl_refr *ref)
{
	size_t		n;
	t_float3	tmp[3];
	t_impact	i;
	t_visible	v;
	t_float3	transparency_v2;

	transparency_v2 = (t_float3){.x = 1, .y = 1, .z = 1};
	n = 0;
	ref->light = light->pos;
	ref->len = 1;
	while (n < scene->num_obj)
	{
		rt_origin_object(impact, &scene->object[n], &tmp[0]);
		tmp[0] = rt_matrix_apply(&tmp[0], scene->object[n].rotate.mat_i);
		tmp[1] = rt_matrix_apply(&ref->light, scene->object[n].rotate.mat_i);
		(*g_colliders[scene->object[n].type])(&tmp[0], &tmp[1],
				&scene->object[n], &i);
		rt_impact_to_visible(&i, &v, n);
		if (v.k >= 0.)
			this_impact_to_light_transparency(scene, n, &transparency_v2, tmp);
		n++;
	}
	return (transparency_v2);
}

t_float3		rt_impact_to_light_spot(const t_float3 *impact,
		const t_light *light, const t_scene *scene, t_refl_refr *ref)
{
	size_t		n;
	t_float3	tmp[3];
	t_impact	i;
	t_visible	v;
	t_float3	transparency_v2;

	transparency_v2 = (t_float3){.x = 1, .y = 1, .z = 1};
	n = 0;
	ref->light = (t_float3){.x = light->pos.x - impact->x,
		.y = light->pos.y - impact->y, .z = light->pos.z - impact->z};
	ref->len = rt_vector_length(&ref->light);
	rt_vector_normalize(&ref->light);
	while (n < scene->num_obj)
	{
		rt_origin_object(impact, &scene->object[n], &tmp[0]);
		tmp[0] = rt_matrix_apply(&tmp[0], scene->object[n].rotate.mat_i);
		tmp[1] = rt_matrix_apply(&ref->light, scene->object[n].rotate.mat_i);
		(*g_colliders[scene->object[n].type])(&tmp[0], &tmp[1],
				&scene->object[n], &i);
		rt_impact_to_visible(&i, &v, n);
		if (v.k + light->ray <= ref->len - light->ray && v.k >= 0)
			this_impact_to_light_transparency(scene, n, &transparency_v2, tmp);
		n++;
	}
	return (transparency_v2);
}
