/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:52 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 21:33:37 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_float3		get_checker_sphere(t_object *obj, t_float3 *impact, int target)
{
	float		lati;
	float		longi;
	int			step;

	(void)target;
	get_pos_sphere(impact, &longi, &lati);
	step = ((int)(longi * obj->checkerdata.w)
	+ (int)(lati * obj->checkerdata.l)) % 2;
	if (step == 0)
		return (obj->checkerdata.color1);
	else
		return (obj->checkerdata.color2);
}

t_float3		get_checker_plane(t_object *obj, t_float3 *impact, int target)
{
	int			step;
	float		x;
	float		y;
	int			tmp;

	(void)target;
	x = fmod(impact->x, obj->checkerdata.w) >= 0 ? fmod(impact->x,
	obj->checkerdata.w) : obj->checkerdata.w + 1 - fmod(impact->x,
	obj->checkerdata.w);
	y = fmod(impact->y, obj->checkerdata.l) >= 0 ? fmod(impact->y,
	obj->checkerdata.l) : obj->checkerdata.l + 1 - fmod(impact->y,
	obj->checkerdata.l);
	tmp = (int)x + (int)y;
	step = tmp % 2;
	if (step == 0)
		return (obj->checkerdata.color1);
	else
		return (obj->checkerdata.color2);
}

t_float3		get_checker_cylinder(t_object *obj, t_float3 *impact,
		int target)
{
	int			step;
	float		circular;
	float		height;
	t_getpos	util;

	util.obj = obj;
	util.impact = impact;
	(void)target;
	height = get_pos_cylinder(util, &circular,
		obj->checkerdata.l, obj->checkerdata.w);
	step = ((int)height + (int)circular) % 2;
	if (step == 0)
		return (obj->checkerdata.color1);
	else
		return (obj->checkerdata.color2);
}

void			get_pos_sphere(t_float3 *impact, float *longi, float *lati)
{
	t_float3	tmp;
	t_float3	tmp2;

	tmp.x = 0;
	tmp.y = 1;
	tmp.z = 0;
	rt_vector_normalize(&tmp);
	tmp2 = *impact;
	tmp2.z = 0;
	rt_vector_normalize(&tmp2);
	*longi = impact->x < 0 ? 1.0 - rt_vector_angle(&tmp, &tmp2) / (2.0 * M_PI)
	: rt_vector_angle(&tmp, &tmp2) / (2.0 * M_PI);
	tmp.y = 0;
	tmp.z = 1;
	rt_vector_normalize(&tmp);
	tmp2 = *impact;
	rt_vector_normalize(&tmp2);
	*lati = rt_vector_angle(&tmp, &tmp2) / (M_PI);
	return ;
}

float			get_pos_cylinder(t_getpos vars, float *circular, int h, int w)
{
	float		height;
	t_float3	tmp;
	t_float3	tmp2;

	tmp.x = 0;
	tmp.y = 1;
	tmp.z = 0;
	rt_vector_normalize(&tmp);
	tmp2 = *vars.impact;
	tmp2.z = 0;
	rt_vector_normalize(&tmp2);
	*circular = (vars.impact->x < 0 ? 1.0 - rt_vector_angle(&tmp, &tmp2)
	/ (2.0 * M_PI) : rt_vector_angle(&tmp, &tmp2) / (2.0 * M_PI)) * w;
	if (vars.obj->type == CYLINDER)
		height = fmod(vars.impact->z, 2.0 * M_PI * vars.obj->ray) * h
	/ (2.0 * M_PI * vars.obj->ray);
	height = fmod(vars.impact->z, 4.0) * h / 4.0;
	if (height < 0)
		height = h + height;
	return (height);
}
