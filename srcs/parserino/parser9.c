/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:18 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 19:15:32 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	this_compute_object_light_var_and_check_path(t_object *object,
		char *filename)
{
	int		i;

	rt_float3_min_max(&object->ka, 0, 1);
	rt_float3_min_max(&object->kd, 0, 1);
	rt_float3_min_max(&object->ks, 0, 1);
	rt_float_min_max(&object->ns, 1, 1000);
	i = 0;
	while (i < TEXTURE_ALL)
	{
		if (object->texture_path[i] && (object->texture[i] =
					SDL_LoadBMP(object->texture_path[i])) == NULL)
		{
			rt_error(ERROR_PATH, filename, 0, object->texture_path[i]);
			object->texture[i] = 0;
			free(object->texture_path[i]);
			object->texture_path[i] = 0;
		}
		i++;
	}
	rt_float3_min_max(&object->checkerdata.color1, 0, 1);
	rt_float3_min_max(&object->checkerdata.color2, 0, 1);
	rt_int_min_max(&object->checkerdata.w, 1, 10000);
	rt_int_min_max(&object->checkerdata.l, 1, 10000);
	rt_float3_min_max(&object->noisedata.color1, 0, 1);
	rt_float3_min_max(&object->noisedata.color2, 0, 1);
}

static void	this_compute_object_var(t_object *object, char *filename)
{
	t_float4	quaternion;

	this_compute_object_light_var_and_check_path(object, filename);
	rt_int_min_max(&object->noisedata.octaves, 1, 10);
	rt_float_min_max(&object->noisedata.persistence, EPSILON, 10);
	if (object->type == CONE)
		object->ray = powf(tanf(object->alpha), 2);
	rt_euler_to_quaternion(object->rotate.rot.x, object->rotate.rot.y,
			object->rotate.rot.z, &quaternion);
	rt_quaternion_to_matrix(&quaternion, object->rotate.mat);
	quaternion.x *= -1;
	quaternion.y *= -1;
	quaternion.z *= -1;
	rt_quaternion_to_matrix(&quaternion, object->rotate.mat_i);
	object->limit = 0;
	if ((object->limit_min.x != -INFINITY || object->limit_max.x != INFINITY)
			&& object->limit_min.x != object->limit_max.x)
		object->limit |= TRUE | LIMIT_X;
	if ((object->limit_min.y != -INFINITY || object->limit_max.y != INFINITY)
			&& object->limit_min.y != object->limit_max.y)
		object->limit |= TRUE | LIMIT_Y;
	if ((object->limit_min.z != -INFINITY || object->limit_max.z != INFINITY)
			&& object->limit_min.z != object->limit_max.z)
		object->limit |= TRUE | LIMIT_Z;
}

static void	this_compute_light_var(t_light *light)
{
	rt_float_min_max(&light->intensity, 0.1, 100);
	rt_float3_min_max(&light->color, 0, 100);
	light->luminance = (t_float3){
		.x = light->color.x * light->intensity,
			.y = light->color.y * light->intensity,
			.z = light->color.z * light->intensity};
	if (light->type == L_DIRECTIONAL)
	{
		light->pos.x = (light->pos.x == 0
				&& light->pos.y == 0 && light->pos.z == 0) ? 1 : light->pos.x;
		rt_vector_normalize(&light->pos);
	}
}

static void	this_compute_cam_var(t_cam *cam)
{
	rt_euler_to_quaternion(cam->rotate_start.x, cam->rotate_start.y,
			cam->rotate_start.z, &cam->rotate_start);
}

void		rt_post_computing(t_stock *stock, char *filename)
{
	size_t		cur_scn;
	t_num		num;

	cur_scn = 0;
	while (cur_scn < stock->num_scn)
	{
		num = (t_num){.obj = 0, .lum = 0, .cam = 0, .amb = 0};
		this_compute_light_var(&stock->scene[cur_scn].ambient);
		while (num.obj < stock->scene[cur_scn].num_obj)
			this_compute_object_var(&stock->scene[cur_scn].object[num.obj++],
					filename);
		while (num.lum < stock->scene[cur_scn].num_lum)
			this_compute_light_var(&stock->scene[cur_scn].light[num.lum++]);
		while (num.cam < stock->scene[cur_scn].num_cam)
			this_compute_cam_var(&stock->scene[cur_scn].cam[num.cam++]);
		cur_scn++;
	}
}
