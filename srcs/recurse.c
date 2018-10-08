/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_effect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:55 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 20:27:57 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_list				**rt_list_pool(int i, int thread)
{
	static t_list	*start[NUM_THREAD];
	static t_list	*end[NUM_THREAD];

	if (i == 1)
		return (&end[thread]);
	return (&start[thread]);
}

void				rt_add_pool(t_list *elem, int thread)
{
	t_list			**start;
	t_list			**end;

	elem->next = NULL;
	end = rt_list_pool(1, thread);
	if (!(*end))
	{
		start = rt_list_pool(0, thread);
		*start = elem;
	}
	else
		(*end)->next = elem;
	*end = elem;
}

t_list				*rt_get_pool(int thread)
{
	t_list			**start;
	t_list			*elem;

	start = rt_list_pool(0, thread);
	elem = *start;
	if (*start)
		*start = (*start)->next;
	if (!(*start))
	{
		start = rt_list_pool(1, thread);
		*start = NULL;
	}
	if (elem)
		elem->next = NULL;
	return (elem);
}

static void			this_recurse(t_list *elem, t_thread *data)
{
	t_recursive		*tmp;
	t_float3		color;

	tmp = (t_recursive *)elem->content;
	color = rt_recurse_pixel((t_recursive *)elem->content,
			&data->win->scene, data->thread);
	rt_float3_add(&color, tmp->color, tmp->color);
	color = *tmp->color;
	fix_color(&color.x, &color.y, &color.z);
	*(*(t_recursive *)elem->content).pixel = SDL_MapRGBA(data->win->pix,
											(int)(color.x * 255),
											(int)(color.y * 255),
											(int)(color.z * 255),
														0xff);
}

int					rt_recurse(void *data)
{
	int				thread;
	t_list			*elem;

	thread = ((t_thread*)data)->thread;
	rt_scene_pixels(((t_thread*)data)->win, thread, ((t_thread*)data)->screen);
	elem = rt_get_queue(thread);
	while (elem)
	{
		if ((*(t_recursive *)elem->content).iter < NUM_ITER)
			this_recurse(elem, (t_thread*)data);
		rt_add_pool(elem, thread);
		elem = rt_get_queue(thread);
	}
	return (0);
}
