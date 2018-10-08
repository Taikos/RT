/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:11:34 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:11:36 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static int		this_init_memory_p2(t_view ****buffer, size_t n_obj,
					size_t xwin, size_t ywin)
{
	if (*buffer)
		free(*buffer);
	if (!(*buffer = (t_view ***)malloc(sizeof(t_view**) * n_obj + ywin
		* sizeof(t_view*) * n_obj + sizeof(t_view) * xwin * ywin * n_obj)))
		return (-1);
	return (0);
}

static int		this_init_memory(size_t x_win, size_t y_win, size_t num_obj,
					t_view ****buffer)
{
	static size_t xwin;
	static size_t ywin;
	static size_t n_obj;

	if (xwin != x_win || ywin != y_win || n_obj != num_obj)
	{
		xwin = x_win;
		ywin = y_win;
		n_obj = num_obj;
		if (this_init_memory_p2(buffer, n_obj, x_win, y_win) == -1)
			return (-1);
		while (num_obj-- > 0)
		{
			(*buffer)[num_obj] = (t_view**)((uint64_t)(*buffer) + n_obj
				* sizeof(t_view**) + (sizeof(t_view*) * ywin) * num_obj);
			y_win = ywin;
			while (y_win-- > 0)
				(*buffer)[num_obj][y_win] = (t_view*)((uint64_t)(*buffer)
					+ sizeof(t_view**) * n_obj + sizeof(t_view*) * ywin
					* n_obj + sizeof(t_view) * xwin * ywin * num_obj
					+ sizeof(t_view) * xwin * y_win);
		}
	}
	return (0);
}

static void		this_init_values(t_view *screen, t_float3 *origin, t_view *data,
															float matrix[3][3])
{
	*data = *screen;
	data->origin.x += origin->x;
	data->origin.y += origin->y;
	data->origin.z += origin->z;
	data->origin = rt_matrix_apply(&data->origin, matrix);
	data->vector = rt_matrix_apply(&data->vector, matrix);
}

static t_view	***this_init_buffer(t_view **screen, t_float3 *origin,
																t_scene *env)
{
	static t_view	***buffer;
	size_t			x;
	size_t			y;
	size_t			id;

	if (this_init_memory(env->x_win, env->y_win, env->num_obj, &buffer))
		return (NULL);
	id = env->num_obj;
	while (id-- > 0)
	{
		y = env->y_win;
		while (y-- > 0)
		{
			x = env->x_win;
			while (x-- > 0)
				this_init_values(&screen[y][x], &origin[id], &buffer[id][y][x],
					env->object[id].rotate.mat_i);
		}
	}
	return (buffer);
}

void			rt_update_buffer(t_scene *env, t_cam *cam)
{
	static t_float3	*origin;

	if (cam->moved == MOVMENT_ALL)
	{
		env->screen = rt_init_projection(env->x_win, env->y_win, cam->fov);
		origin = rt_init_origin(&cam->origin, env->object, env->num_obj);
		rt_rotate_screen(&cam->rotate_start, env->screen, env->x_win,
			env->y_win);
	}
	else if (cam->moved == ROTATE)
		rt_rotate_screen(&cam->rotate, env->screen, env->x_win, env->y_win);
	else if (cam->moved == TRANSLATE)
		origin = rt_init_origin(&cam->origin, env->object, env->num_obj);
	if (cam->moved)
		env->buffer = this_init_buffer(env->screen, origin, env);
	cam->moved = 0;
}
