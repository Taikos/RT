/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_interface3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:36:31 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 17:36:35 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	this_display_interface_1(t_idisplay *norm)
{
	if (norm->button[norm->len].value == VT_EDGE_HARD)
	{
		norm->win->filter = F_EDGE_HARD;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else if (norm->button[norm->len].value == VT_SHARPEN)
	{
		norm->win->filter = F_SHARPEN;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else if (norm->button[norm->len].value == VT_BLUR_BOX)
	{
		norm->win->filter = F_BLUR_BOX;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else if (norm->button[norm->len].value == VT_EMBOSSING)
	{
		norm->win->filter = F_EMBOSSING;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	return (0);
}

static int	this_display_interface_2(t_idisplay *norm)
{
	if (norm->button[norm->len].value == VT_ANTIALIAZ)
	{
		norm->win->filter = F_ANTIALIAZ;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else if (norm->button[norm->len].value == VT_BLACK_WHITE)
	{
		norm->win->filter = F_BLACK_WHITE;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else if (norm->button[norm->len].value == VT_SEPIA)
	{
		norm->win->filter = F_SEPIA;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else if (norm->button[norm->len].value == VT_CARTOON)
	{
		norm->win->filter = F_CARTOON;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	return (0);
}

int			rt_display_interface_3(t_idisplay *norm, int *cur_obj,
				int *cur_light)
{
	(void)cur_light;
	(void)cur_obj;
	if (this_display_interface_1(norm))
		return (1);
	else if (this_display_interface_2(norm))
		return (1);
	else if (norm->button[norm->len].value == V_TAKE_SCREEN)
		rt_picture_save_stable(norm->win, norm->win->pixel, "Screen.png");
	else if (norm->button[norm->len].value == V_TAKE_XML)
		rt_save_xml(norm->win, "Output.xml");
	else if (norm->button[norm->len].value == V_REFRESH)
		norm->refresh = 1;
	return (0);
}
