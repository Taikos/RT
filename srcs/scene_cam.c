/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:22 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:13:24 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static t_float4	*this_rotate(t_float3 *axis, t_float3 *target1,
					t_float3 *target2, float alpha)
{
	static t_float4 quaternion;

	rt_quaternion_create(axis, alpha, &quaternion);
	rt_quaternion_apply(&quaternion, *target1, target1);
	rt_quaternion_apply(&quaternion, *target2, target2);
	return (&quaternion);
}

static t_float3	*this_translate(t_float3 *origin, t_float3 *translate,
					ssize_t sign)
{
	static t_float3	vec;

	vec = (t_float3){.x = (float)sign * translate->x,
			.y = (float)sign * translate->y, .z = (float)sign * translate->z};
	origin->x += vec.x;
	origin->y += vec.y;
	origin->z += vec.z;
	return (&vec);
}

static t_float3	*this_all_translate(size_t order, t_cam *cam)
{
	if (order == T_FORWARD)
		return (this_translate(&cam->origin, &cam->axis_x, 1 * cam->pitch));
	else if (order == T_BACKWARD)
		return (this_translate(&cam->origin, &cam->axis_x, -1 * cam->pitch));
	else if (order == T_UP)
		return (this_translate(&cam->origin, &cam->axis_z, 1 * cam->pitch));
	else if (order == T_DOWN)
		return (this_translate(&cam->origin, &cam->axis_z, -1 * cam->pitch));
	else if (order == T_RIGHT)
		return (this_translate(&cam->origin, &cam->axis_y, 1 * cam->pitch));
	else if (order == T_LEFT)
		return (this_translate(&cam->origin, &cam->axis_y, -1 * cam->pitch));
	else
		return (NULL);
}

static t_float4	*this_all_rotate(size_t order, t_cam *cam)
{
	if (order == R_RIGHT)
		return (this_rotate(&cam->axis_z, &cam->axis_x,
		&cam->axis_y, 1 * cam->alpha));
	else if (order == R_LEFT)
		return (this_rotate(&cam->axis_z, &cam->axis_x,
		&cam->axis_y, -1 * cam->alpha));
	else if (order == R_UP)
		return (this_rotate(&cam->axis_y, &cam->axis_x,
		&cam->axis_z, 1 * cam->alpha));
	else if (order == R_DOWN)
		return (this_rotate(&cam->axis_y, &cam->axis_x,
		&cam->axis_z, -1 * cam->alpha));
	else if (order == R_ROLL_RIGHT)
		return (this_rotate(&cam->axis_x, &cam->axis_y,
		&cam->axis_z, 1 * cam->alpha));
	else if (order == R_ROLL_LEFT)
		return (this_rotate(&cam->axis_x, &cam->axis_y,
		&cam->axis_z, -1 * cam->alpha));
	else
		return (NULL);
}

void			rt_scene_camera(size_t order, t_cam *cam)
{
	t_float4 *rot;
	t_float3 *translate;

	if (order && order < TRANSLATE)
	{
		if ((translate = this_all_translate(order, cam)) != NULL)
		{
			cam->origin.x += translate->x;
			cam->origin.y += translate->y;
			cam->origin.z += translate->z;
			cam->translate = *translate;
			cam->moved = TRANSLATE;
		}
	}
	else if (TRANSLATE < order && order < ROTATE)
	{
		if ((rot = this_all_rotate(order, cam)) != NULL)
		{
			cam->rotate = *rot;
			rt_quaternion_multiply(*rot, cam->rotate_start, &cam->rotate_start);
			cam->moved = ROTATE;
		}
	}
	else if (order == MOVMENT_ALL)
		cam->moved = MOVMENT_ALL;
}
