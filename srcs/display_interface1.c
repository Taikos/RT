/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_interface1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:36:10 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 17:36:12 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	this_display_interface_1(t_idisplay *norm)
{
	if (norm->var)
	{
		norm->refresh = 1;
		*norm->var += norm->button[norm->len].pitch;
		if (g_min_max[g_value[norm->button[norm->len].value].min_max].flags
		& MM_MIN && *norm->var < g_min_max[g_value[norm->button[norm->len].
		value].min_max].min)
			*norm->var = g_min_max[g_value[norm->button[
			norm->len].value].min_max].min;
		if (g_min_max[g_value[norm->button[norm->len].value].min_max].flags
		& MM_MAX && *norm->var > g_min_max[g_value[norm->button[norm->len].
		value].min_max].max)
			*norm->var = g_min_max[g_value[norm->button[
			norm->len].value].min_max].max;
		if (g_min_max[g_value[norm->button[norm->len].value].min_max] .flags
		& MM_TAN)
			norm->object->ray = powf(tanf(norm->object->alpha), 2);
		if (g_min_max[g_value[norm->button[norm->len].value].min_max].flags
		& MM_LUM)
			rt_float3_mult_float(&norm->light->color,
			norm->light->intensity, &norm->light->luminance);
	}
}

static int	this_display_interface_2(t_idisplay *norm)
{
	return (((*norm).button[(*norm).len].value == V_REFRESH
	&& (*norm).win->b_event) || ((*norm).button[(*norm).len].value
	== VT_EDGE_HARD && (*norm).win->filter == F_EDGE_HARD) ||
	((*norm).button[(*norm).len].value
	== VT_SHARPEN && (*norm).win->filter == F_SHARPEN) ||
	((*norm).button[(*norm).len].value
	== VT_BLUR_BOX && (*norm).win->filter == F_BLUR_BOX) ||
	((*norm).button[(*norm).len].value
	== VT_EMBOSSING && (*norm).win->filter == F_EMBOSSING) ||
	((*norm).button[(*norm).len].value
	== VT_ANTIALIAZ && (*norm).win->filter == F_ANTIALIAZ) ||
	((*norm).button[(*norm).len].value
	== VT_BLACK_WHITE && (*norm).win->filter == F_BLACK_WHITE) ||
	((*norm).button[(*norm).len].value
	== VT_SEPIA && (*norm).win->filter == F_SEPIA) ||
	((*norm).button[(*norm).len].value
	== VT_CARTOON && (*norm).win->filter == F_CARTOON) ||
	((*norm).button[(*norm).len].value
	== VT_PERLIN && (*norm).object->color_state == CS_PERLIN) ||
	((*norm).button[(*norm).len].value
	== VT_CHECKER && (*norm).object->color_state == CS_CHECKER) ||
	((*norm).button[(*norm).len].value
	== VT_TEXTURE && (*norm).object->color_state == CS_TEXTURE) ||
	((*norm).button[(*norm).len].value
	== VT_NORMAL && (*norm).object->normal_state == NS_TEXTURE));
}

static void	this_display_interface_4(t_idisplay *norm)
{
	if (this_display_interface_2(&(*norm)))
		SDL_RenderCopy((*norm).win->rndr_i,
		(*norm).win->button[(*norm).button[(*norm).len].id].hover,
		NULL, &(*norm).button[(*norm).len].position);
	else
		SDL_RenderCopy((*norm).win->rndr_i,
		(*norm).win->button[(*norm).button[(*norm).len].id].normal,
		NULL, &(*norm).button[(*norm).len].position);
}

static int	this_display_interface_3(t_idisplay *norm, int *cur_light,
				int *cur_obj)
{
	if (((*norm).x) >= (*norm).button[(*norm).len].position.x && (*norm).x
	<= (*norm).button[(*norm).len].position.x + (*norm).button[(*norm).len]
	.position.w &&
		(*norm).y >= (*norm).button[(*norm).len].position.y && (*norm).y
		<= (*norm).button[(*norm).len].position.y + (*norm).button[(*norm).len]
		.position.h)
	{
		if (!(*norm).win->b_event && (*norm).click
		&& (*norm).button[(*norm).len].value >= 0)
		{
			if (rt_display_interface_2(&(*norm), cur_obj, cur_light) == 1)
				return (1);
			this_display_interface_1(&(*norm));
			if ((*norm).val)
				return (rt_display_interface_4(&(*norm), cur_obj));
		}
		SDL_RenderCopy((*norm).win->rndr_i,
		(*norm).win->button[(*norm).button[(*norm).len].id].hover, NULL,
		&(*norm).button[(*norm).len].position);
	}
	else
		this_display_interface_4(norm);
	return (0);
}

int			rt_display_interface(t_idisplay norm)
{
	static int cur_obj;
	static int cur_light;

	norm.refresh = 0;
	SDL_RenderClear(norm.win->rndr_i);
	SDL_RenderCopy(norm.win->rndr_i, norm.background, NULL, NULL);
	norm.scene = &(norm.win->stock.scene[norm.win->stock.cur_scn]);
	norm.object = &(norm.scene->object[cur_obj]);
	norm.camera = &(norm.scene->cam[norm.scene->cur_cam]);
	norm.light = &(norm.scene->light[cur_light]);
	while (norm.len--)
	{
		if (this_display_interface_3(&norm, &cur_light, &cur_obj) == 1)
			return (1);
	}
	if (norm.refresh)
	{
		norm.win->b_event = SDL_TRUE;
		SDL_CondSignal(norm.win->c_event);
	}
	return (0);
}
