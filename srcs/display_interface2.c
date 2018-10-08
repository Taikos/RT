/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_interface2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:36:20 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/24 15:20:23 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		this_display_interface_1(t_idisplay *norm,
		int *cur_obj)
{
	if (norm->button[norm->len].value < VC_POS_X)
		norm->var = (float*)((uint64_t)norm->object
				+ g_value[norm->button[norm->len].value].offset);
	else if (norm->button[norm->len].value < VL_POS_X)
		norm->var = (float*)((uint64_t)norm->camera
				+ g_value[norm->button[norm->len].value].offset);
	else if (norm->button[norm->len].value < VALUE_ALL)
		norm->var = (float*)((uint64_t)norm->light
				+ g_value[norm->button[norm->len].value].offset);
	else if (norm->button[norm->len].value == V_CUR_OBJ)
		norm->val = (int*)cur_obj;
	else if (norm->button[norm->len].value == V_GO_HOME && (*norm->id = I_HOME))
	{
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else
		return (2);
	return (0);
}

/*
**==============================================================================
**				Fonctionnalité Switch Cam / Scene / Light Removed
**==============================================================================
** ===================        Ligne 27         =================================
**else if (norm->button[norm->len].value == V_CUR_SCENE)
**	norm->val = (int*)&norm->win->stock.cur_scn;
**else if (norm->button[norm->len].value == V_CUR_CAM)
**	norm->val = (int*)&norm->scene->cur_cam;
** ===================        Ligne 33         =================================
**else if (norm->button[norm->len].value == V_CUR_LIGHT)
**	norm->val = (int*)cur_light;
*/

static int		this_display_interface_2(t_idisplay *norm, int *cur_obj)
{
	if (norm->button[norm->len].value == V_GO_EDIT)
	{
		*norm->id = I_ADD;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else if (norm->button[norm->len].value == V_GO_OBJECT)
	{
		*cur_obj = 0;
		if (norm->object->type == CYLINDER)
			*norm->id = I_CYLINDER_P;
		else if (norm->object->type == SPHERE)
			*norm->id = I_SPHERE_P;
		else if (norm->object->type == PLANE)
			*norm->id = I_PLANE_P;
		else if (norm->object->type == CONE)
			*norm->id = I_CONE_P;
		else if (norm->object->type == DISK)
			*norm->id = I_DISK_P;
	}
	else
		return (2);
	return (0);
}

/*
** if (norm->button[norm->len].value == V_GO_LIGHT)
** {
** 	*cur_light = 0;
** 	if (norm->light->type == L_DIRECTIONAL)
** 		*norm->id = I_SUN;
** 	else if (norm->light->type == L_SPOT)
** 		*norm->id = I_LIGHT;
** 	else if (norm->light->type == L_AMBIENT)
** 		*norm->id = I_AMBIENT;
** }
**
** a mettre au debut de this_display_interface_3
** ajouter un parametre cur_light a l'appel de
** cette fonction ligne 140
*/

static int		this_display_interface_3(t_idisplay *norm)
{
	if (norm->button[norm->len].value == V_GO_OTHER)
		*norm->id = I_OTHER;
	else if (norm->button[norm->len].value == VT_PERLIN)
	{
		norm->object->color_state = CS_PERLIN;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else
		return (2);
	return (0);
}

static int		this_display_interface_4(t_idisplay *norm)
{
	if (norm->button[norm->len].value == VT_CHECKER)
	{
		norm->object->color_state = CS_CHECKER;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else if (norm->button[norm->len].value == VT_TEXTURE)
	{
		norm->object->color_state = CS_TEXTURE;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else if (norm->button[norm->len].value == VT_NORMAL)
	{
		norm->object->normal_state = NS_TEXTURE;
		norm->win->b_event = SDL_TRUE;
		return (1);
	}
	else
		return (2);
	return (0);
}

int				rt_display_interface_2(t_idisplay *norm,
		int *cur_obj, int *cur_light)
{
	int		i;

	norm->var = NULL;
	norm->val = NULL;
	if ((i = this_display_interface_1(norm, cur_obj)) && i == 1)
		return (1);
	else if (i && (i = this_display_interface_2(norm, cur_obj))
			&& i == 1)
		return (1);
	else if (i && (i = this_display_interface_3(norm))
			&& i == 1)
		return (1);
	else if (i && (i = this_display_interface_4(norm))
			&& i == 1)
		return (1);
	else if (i && (i = rt_display_interface_3(norm, cur_obj,
					cur_light)) && i == 1)
		return (1);
	return (0);
}

/*
** if ((i = this_display_interface_1(norm, cur_obj, cur_light)) && i == 1)
** ligne 136
*/
