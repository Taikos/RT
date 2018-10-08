/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:29 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 19:47:23 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	this_search_visible(const t_scene *scene, const size_t y,
				const size_t x, t_visible *v)
{
	t_impact	i;
	size_t		a;

	a = 0;
	(*g_colliders[scene->object[a].type])(&scene->buffer[a][y][x].origin,
	&scene->buffer[a][y][x].vector, &scene->object[a], &i);
	rt_impact_to_visible(&i, v, 0);
	while (++a < scene->num_obj)
	{
		(*g_colliders[scene->object[a].type])(&scene->buffer[a][y][x].origin,
		&scene->buffer[a][y][x].vector, &scene->object[a], &i);
		rt_first_noticeable(v, &i, a);
	}
}

static void	this_set_data_impact(const t_scene *scene, t_refl_refr *ref,
				const t_visible *v, const t_cam *cam)
{
	ref->normal = rt_collider_normal(&scene->object[v->visible],
	&scene->buffer[v->visible][ref->y][ref->x].origin,
	&scene->buffer[v->visible][ref->y][ref->x].vector, v->k);
	ref->ka = scene->object[v->visible].ka;
	ref->kd = scene->object[v->visible].kd;
	ref->ks = scene->object[v->visible].ks;
	apply_options((t_scene*)scene, (t_visible*)v, ref,
		&scene->buffer[v->visible][ref->y][ref->x].vector);
	ref->normal = rt_matrix_apply(&ref->normal,
	scene->object[v->visible].rotate.mat);
	ref->impact[0] = (t_float3){.x = cam->origin.x
	+ scene->screen[ref->y][ref->x].origin.x, .y = cam->origin.y
	+ scene->screen[ref->y][ref->x].origin.y, .z = cam->origin.z
	+ scene->screen[ref->y][ref->x].origin.z};
	ref->impact[0] = rt_vector_impact(&ref->impact[0],
	&scene->screen[ref->y][ref->x].vector, v->k);
	rt_float3_mult(&ref->ka, &scene->ambient.luminance, &ref->color);
}

static void	this_scene_pixel_refraction(t_sdl *win, t_refl_refr *ref,
				t_visible *v, t_scnpxl *norm)
{
	(*norm).loop.color = &(*norm).screen[(*ref).x
	+ (*ref).y * win->scene.x_win];
	(*norm).loop.coeff = (t_float3){
		.x = 1 - win->scene.object[(*v).visible].ks.x,
		.y = 1 - win->scene.object[(*v).visible].ks.y,
		.z = 1 - win->scene.object[(*v).visible].ks.z};
	rt_float3_mult_float(&(*norm).loop.coeff,
	win->scene.object[(*v).visible].transparency, &(*norm).loop.coeff);
	(*norm).loop.iter = 1;
	(*norm).loop.pixel = &(win->pixel[(*ref).x
	+ (*ref).y * win->scene.x_win]);
	(*norm).loop.vector = rt_recurse_refraction(
		&win->scene.screen[(*ref).y][(*ref).x].vector, &(*ref).normal, 1);
	(*norm).loop.origin = (*ref).impact[0];
	rt_add_queue(&(*norm).loop, (*norm).thread);
}

static void	this_scene_pixel(t_sdl *win, t_refl_refr *ref, t_visible *v,
				t_scnpxl norm)
{
	this_set_data_impact(&win->scene, ref, v, &win->cam);
	rt_look_lights(ref, &win->scene, v,
	&win->scene.screen[(*ref).y][(*ref).x].vector);
	if (win->scene.object[(*v).visible].transparency < 1)
	{
		norm.loop.color = &norm.screen[(*ref).x + (*ref).y * win->scene.x_win];
		rt_float3_mult_float(&win->scene.object[(*v).visible].ks, 1
		- win->scene.object[(*v).visible].transparency, &norm.loop.coeff);
		norm.loop.iter = 1;
		norm.loop.pixel = &(win->pixel[(*ref).x + (*ref).y * win->scene.x_win]);
		norm.loop.vector = rt_recurse_reflection(
		&win->scene.screen[(*ref).y][(*ref).x].vector, &(*ref).normal);
		norm.loop.origin = (*ref).impact[0];
		rt_add_queue(&norm.loop, norm.thread);
	}
	if (win->scene.object[(*v).visible].transparency >
			EPSILON && win->scene.object[(*v).visible].transparency <= 1)
		this_scene_pixel_refraction(win, ref, v, &norm);
}

int			rt_scene_pixels(t_sdl *win, int thread, t_float3 *screen)
{
	t_visible	v;
	t_refl_refr	ref;
	t_scnpxl	norm;

	ref.y = thread;
	while (ref.y < win->scene.y_win)
	{
		ref.x = 0;
		while (ref.x < win->scene.x_win)
		{
			norm = (t_scnpxl){.screen = screen, .thread = thread};
			this_search_visible(&win->scene, ref.y, ref.x, &v);
			ref.color = (t_float3){.x = 0, .y = 0, .z = 0};
			if (v.visible >= 0 && (size_t)v.visible < win->scene.num_obj)
				this_scene_pixel(win, &ref, &v, norm);
			screen[ref.x + ref.y * win->scene.x_win] = ref.color;
			fix_color(&ref.color.x, &ref.color.y, &ref.color.z);
			win->pixel[ref.x + ref.y * win->scene.x_win] = SDL_MapRGBA(win->pix,
			(int)(ref.color.x * 255), (int)(ref.color.y * 255),
			(int)(ref.color.z * 255), 0xff);
			ref.x++;
		}
		ref.y += NUM_THREAD;
	}
	return (1);
}
