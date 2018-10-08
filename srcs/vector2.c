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

float	rt_vector_length(t_float3 *v)
{
	return (sqrtf(v->x * v->x + v->y * v->y + v->z * v->z));
}

void	rt_int_min_max(int *number, int min, int max)
{
	if (*number < min)
		*number = min;
	if (*number > max)
		*number = max;
}

void	rt_float_min_max(float *number, float min, float max)
{
	if (*number < min)
		*number = min;
	if (*number > max)
		*number = max;
}
