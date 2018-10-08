/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:15 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 20:50:22 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					rt_first_noticeable(t_visible *v1, t_impact *i2, int id)
{
	t_visible		v2;

	rt_impact_to_visible(i2, &v2, id);
	if (v1->visible >= 0 && v2.visible >= 0)
	{
		if (v1->k >= v2.k)
		{
			*v1 = v2;
			return (1);
		}
	}
	else if (v1->visible >= 0)
		;
	else if (v2.visible >= 0)
	{
		*v1 = v2;
		return (1);
	}
	else
		*v1 = (t_visible){.visible = -1, .k = -1};
	return (0);
}

inline static int	this_custom_limits(float x, float min, float max)
{
	if (min <= max && min < x && x < max)
		return (TRUE);
	else if (min >= max && !(min > x && x > max))
		return (TRUE);
	else
		return (FALSE);
}

inline static int	this_inside_limits(int limit, t_float3 *k,
		const t_float3 *min, const t_float3 *max)
{
	if ((((limit & LIMIT_X) && this_custom_limits(k->x, min->x, max->x)
					== TRUE)
				|| !(limit & LIMIT_X))
			&& ((limit & LIMIT_Y && this_custom_limits(k->y, min->y, max->y)
					== TRUE)
				|| !(limit & LIMIT_Y))
			&& ((limit & LIMIT_Z && this_custom_limits(k->z, min->z, max->z)
					== TRUE)
				|| !(limit & LIMIT_Z)))
		return (TRUE);
	else
		return (FALSE);
}

void				rt_apply_limits(const t_object *object, t_impact *impact,
		t_float3 *ray, t_float3 *origin)
{
	t_float3		k1;
	t_float3		k2;

	if (impact->hit & TRUE)
	{
		if (object->limit & TRUE)
		{
			k1 = rt_vector_impact(origin, ray, impact->k1);
			k2 = rt_vector_impact(origin, ray, impact->k2);
			if (this_inside_limits(object->limit, &k1, &object->limit_min,
						&object->limit_max) == TRUE)
				impact->hit |= K1;
			if (this_inside_limits(object->limit, &k2, &object->limit_min,
						&object->limit_max) == TRUE)
				impact->hit |= K2;
		}
		else
			impact->hit |= (K1 | K2);
	}
}

/*
** ce calcul dependant uniquement de la position de la camera et de celle
** de l'objet on le calcul pour chaque objets avant de boucler sur les pixels
*/

void				rt_origin_object(const t_float3 *origin,
		const t_object *object, t_float3 *const new_origin)
{
	new_origin->x = origin->x - object->pos.x;
	new_origin->y = origin->y - object->pos.y;
	new_origin->z = origin->z - object->pos.z;
}
