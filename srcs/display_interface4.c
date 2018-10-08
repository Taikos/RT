/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_interface4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:37:05 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/24 15:21:15 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		this_display_interface_1(t_idisplay *norm)
{
	(*norm).pouet = (*norm).button[(*norm).len].pitch > 0 ? 1 : -1;
	if (((*norm).button[(*norm).len].value == V_CUR_OBJ && *(*norm).val
				+ (*norm).pouet >= (int)(*norm).scene->num_obj))
		*(*norm).val = 0;
	else if ((*norm).button[(*norm).len].value == V_CUR_OBJ && *(*norm).val
			+ (*norm).pouet < 0)
		*(*norm).val = (int)(*norm).scene->num_obj - 1;
	else
		*(*norm).val += (*norm).pouet;
	*(*norm).val = *(*norm).val < 0 ? 0 : *(*norm).val;
}

/*
**=======================    Debut du if    ====================================
**(*norm).button[(*norm).len].value == V_CUR_SCENE && *(*norm).val
**+ (*norm).pouet >= (int)(*norm).win->stock.num_scn)
**	|| ((*norm).button[(*norm).len].value == V_CUR_CAM && *(*norm).val
**	+ (*norm).pouet >= (int)(*norm).scene->num_cam)
**	|| ((*norm).button[(*norm).len].value == V_CUR_LIGHT && *(*norm).val
**	+ (*norm).pouet >= (int)(*norm).scene->num_lum)
**	||
*/

/*
**======================       Ligne 27     ====================================
**else if ((*norm).button[(*norm).len].value == V_CUR_SCENE && *(*norm).val
**+ (*norm).pouet < 0)
**	*(*norm).val = (int)(*norm).win->stock.num_scn - 1;
**else if ((*norm).button[(*norm).len].value == V_CUR_CAM && *(*norm).val
**+ (*norm).pouet < 0)
**	*(*norm).val = (int)(*norm).scene->num_cam - 1;
**else if ((*norm).button[(*norm).len].value == V_CUR_LIGHT && *(*norm).val
**+ (*norm).pouet < 0)
**	*(*norm).val = (int)(*norm).scene->num_lum - 1;
*/

static int		this_display_interface_2(t_idisplay *norm)
{
	if ((*norm).object->type == PLANE && *(*norm).id != I_PLANE_P)
	{
		*(*norm).id = I_PLANE_P;
		(*norm).win->b_event = SDL_TRUE;
		return (1);
	}
	else if ((*norm).object->type == CONE && *(*norm).id != I_CONE_P)
	{
		*(*norm).id = I_CONE_P;
		(*norm).win->b_event = SDL_TRUE;
		return (1);
	}
	else if ((*norm).object->type == DISK && *(*norm).id != I_DISK_P)
	{
		*(*norm).id = I_DISK_P;
		(*norm).win->b_event = SDL_TRUE;
		return (1);
	}
	return (0);
}

int				rt_display_interface_4(t_idisplay *norm, int *cur_obj)
{
	(*norm).refresh = 1;
	this_display_interface_1(&(*norm));
	if ((*norm).button[(*norm).len].value == V_CUR_OBJ)
	{
		(*norm).object = &((*norm).scene->object[(*cur_obj)]);
		if ((*norm).object->type == CYLINDER && *(*norm).id != I_CYLINDER_P)
		{
			*(*norm).id = I_CYLINDER_P;
			(*norm).win->b_event = SDL_TRUE;
			return (1);
		}
		else if ((*norm).object->type == SPHERE && *(*norm).id != I_SPHERE_P)
		{
			*(*norm).id = I_SPHERE_P;
			(*norm).win->b_event = SDL_TRUE;
			return (1);
		}
		else if (this_display_interface_2(&(*norm)))
			return (1);
	}
	return (0);
}
