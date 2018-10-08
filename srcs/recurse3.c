/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_effect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:55 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 20:29:30 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_float3		rt_recurse_reflection(t_float3 *vector, t_float3 *normal)
{
	t_float3	reflected;
	float		tmp;

	tmp = 2 * rt_vector_dot_p(vector, normal);
	reflected.x = vector->x - tmp * normal->x;
	reflected.y = vector->y - tmp * normal->y;
	reflected.z = vector->z - tmp * normal->z;
	return (reflected);
}

/*
** Formule de Descartes n1 * sin(teta1) = n2 * sin(teta2)
*/

t_float3		rt_recurse_refraction(t_float3 *vector, t_float3 *normal,
		float n)
{
	t_float3	vector_i;
	t_float3	recurse;
	float		teta1;
	float		teta2;

	vector_i = (t_float3){.x = -vector->x, .y = -vector->y,
		.z = -vector->z};
	teta1 = rt_vector_dot_p(normal, &vector_i);
	teta2 = sqrtf(1 - (n * n) * (1 - teta1 * teta1));
	if (teta1 >= 0)
		teta1 = (n * teta1 - teta2);
	else
		teta1 = (n * teta1 + teta2);
	recurse.x = n * vector->x + teta1 * normal->x;
	recurse.y = n * vector->y + teta1 * normal->y;
	recurse.z = n * vector->z + teta1 * normal->z;
	rt_vector_normalize(&recurse);
	return (recurse);
}

void			rt_look_lights(t_refl_refr *ref, const t_scene *scene,
		const t_visible *v, const t_float3 *vector)
{
	size_t		i;
	t_float3	transparency;
	t_light		lum;

	i = 0;
	ref->visible = v->visible;
	while (i < scene->num_lum)
	{
		if (scene->light[i].type == L_DIRECTIONAL)
			transparency = rt_impact_to_light_directional(&ref->impact[0],
					&scene->light[i], scene, ref);
		else
			transparency = rt_impact_to_light_spot(&ref->impact[0],
					&scene->light[i], scene, ref);
		if (transparency.x > EPSILON || transparency.y > EPSILON
				|| transparency.z > EPSILON)
		{
			lum = scene->light[i];
			rt_float3_mult(&lum.luminance, &transparency, &lum.luminance);
			rt_light(&scene->object[v->visible], &lum, ref, vector);
		}
		i++;
	}
}

void			rt_rotate_screen(t_float4 *quaternion, t_view **screen,
		size_t x, size_t y)
{
	size_t		i;
	size_t		j;
	float		matrix[3][3];

	rt_quaternion_to_matrix(quaternion, matrix);
	j = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			screen[j][i].origin = rt_matrix_apply(&screen[j][i].origin, matrix);
			screen[j][i].vector = rt_matrix_apply(&screen[j][i].vector, matrix);
			i++;
		}
		j++;
	}
}

void			rt_translate_screen(t_float3 *vector, t_view **screen,
		size_t x, size_t y)
{
	size_t		i;
	size_t		j;

	j = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			screen[j][i].origin.x += vector->x;
			screen[j][i].origin.y += vector->y;
			screen[j][i].origin.z += vector->z;
			i++;
		}
		j++;
	}
}
