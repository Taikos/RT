/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_effect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:55 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 20:13:29 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	rt_vector_dot_p(t_float3 *v1, t_float3 *v2)
{
	float	dotp;

	dotp = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	dotp = (dotp > 1 ? 1 : dotp);
	dotp = (dotp < -1 ? -1 : dotp);
	return (dotp);
}

void	rt_vector_reverse(t_float3 *vector)
{
	vector->x *= -1.0;
	vector->y *= -1.0;
	vector->z *= -1.0;
}

t_list	**rt_list_queue(int i, int thread)
{
	static t_list *start[NUM_THREAD];
	static t_list *end[NUM_THREAD];

	if (i == 1)
		return (&end[thread]);
	return (&start[thread]);
}

void	rt_add_queue(t_recursive *data, int thread)
{
	t_list **start;
	t_list **end;
	t_list *elem;

	elem = rt_get_pool(thread);
	if (elem)
		ft_memcpy(elem->content, data, elem->content_size);
	else
		elem = ft_lstnew(data, sizeof(t_recursive));
	if (!elem)
		exit(0);
	end = rt_list_queue(1, thread);
	if (!(*end))
	{
		start = rt_list_queue(0, thread);
		*start = elem;
	}
	else
		(*end)->next = elem;
	*end = elem;
}

t_list	*rt_get_queue(int thread)
{
	t_list **start;
	t_list *elem;

	start = rt_list_queue(0, thread);
	elem = *start;
	if (*start)
		*start = (*start)->next;
	if (*start == NULL)
	{
		start = rt_list_queue(1, thread);
		*start = NULL;
	}
	return (elem);
}
