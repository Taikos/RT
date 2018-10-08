/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:15 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:13:17 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_float3_min_max(t_float3 *value, float min, float max)
{
	rt_float_min_max(&value->x, min, max);
	rt_float_min_max(&value->y, min, max);
	rt_float_min_max(&value->z, min, max);
}

void	rt_float3_mult(const t_float3 *v1, const t_float3 *v2, t_float3 *result)
{
	result->x = v1->x * v2->x;
	result->y = v1->y * v2->y;
	result->z = v1->z * v2->z;
}

void	rt_float3_mult_float(const t_float3 *v1, const float v2,
			t_float3 *result)
{
	result->x = v1->x * v2;
	result->y = v1->y * v2;
	result->z = v1->z * v2;
}

void	rt_float3_min(t_float3 *value, const float min)
{
	if (value->x < min)
		value->x = min;
	if (value->y < min)
		value->y = min;
	if (value->z < min)
		value->z = min;
}

void	rt_float3_add(const t_float3 *v1, const t_float3 *v2, t_float3 *result)
{
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;
}
