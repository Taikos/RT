/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:52 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 21:16:13 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_float3		get_tex_value_plane(t_object *obj, t_float3 *impact, int target)
{
	t_float3	color;
	int			x;
	int			y;
	t_uint8_3	ucolor;

	x = fmod(impact->x * obj->texture[target]->w / 4, obj->texture[target]->w);
	y = fmod(impact->y * obj->texture[target]->h / 4, obj->texture[target]->h);
	if (x < 0)
		x = obj->texture[target]->w + x;
	if (y < 0)
		y = obj->texture[target]->h + y;
	SDL_GetRGB(getpixel(obj->texture[target], x, y),
	obj->texture[target]->format, &(ucolor.r), &(ucolor.g), &(ucolor.b));
	color.x = ucolor.r / 255.0;
	color.y = ucolor.g / 255.0;
	color.z = ucolor.b / 255.0;
	return (color);
}

t_float3		get_tex_value_cone(SDL_Surface *tex, t_float3 *impact)
{
	(void)tex;
	(void)impact;
	return (*impact);
}

t_float3		get_tex_value_disk(SDL_Surface *tex, t_float3 *impact)
{
	(void)tex;
	(void)impact;
	return (*impact);
}

t_float3		get_tex_value_cylinder(t_object *obj,
		t_float3 *impact, int target)
{
	float		circular;
	float		height;
	t_float3	color;
	t_uint8_3	ucolor;
	t_getpos	util;

	util.obj = obj;
	util.impact = impact;
	height = get_pos_cylinder(util, &circular, obj->texture[target]->h, 1);
	SDL_GetRGB(getpixel(obj->texture[target],
		obj->texture[target]->w * circular > obj->texture[target]->w - 1
		? obj->texture[target]->w - 1 : obj->texture[target]->w * circular,
		height > obj->texture[target]->h - 1
		? obj->texture[target]->h - 1 : height), obj->texture[target]->format,
		&(ucolor.r), &(ucolor.g), &(ucolor.b));
	color.x = ucolor.r / 255.0;
	color.y = ucolor.g / 255.0;
	color.z = ucolor.b / 255.0;
	return (color);
}

t_float3		get_tex_value_sphere(t_object *obj,
		t_float3 *impact, int target)
{
	float		lati_longi[2];
	t_float3	color;
	uint8_t		x;
	uint8_t		y;
	uint8_t		z;

	get_pos_sphere(impact, &lati_longi[1], &lati_longi[0]);
	SDL_GetRGB(getpixel(obj->texture[target], obj->texture[target]->w
	* (lati_longi[1]),
	obj->texture[target]->h * lati_longi[0]),
	obj->texture[target]->format, &x, &y, &z);
	color.x = x / 255.0;
	color.y = y / 255.0;
	color.z = z / 255.0;
	return (color);
}
