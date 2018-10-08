/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:52 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 21:41:10 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		this_part_two(long int l, int fd)
{
	if (l < 0)
	{
		ft_putchar_fd('-', fd);
		l = -l;
	}
	if (l > 9)
	{
		this_part_two(l / 10, fd);
		this_part_two(l % 10, fd);
	}
	else
	{
		l = l + 48;
		ft_putchar_fd(l, fd);
	}
}

static void		this_part_three(float *nbr, long l, int *precision, int fd)
{
	ft_putchar_fd('.', fd);
	while (*nbr > 0 && (*precision)--)
	{
		(*nbr) = (*nbr) * 10;
		l = (long)(*nbr);
		l = l % 10;
		(*nbr) = (*nbr) - l;
		ft_putchar_fd(l + 48, fd);
	}
}

void			rt_putfloat_fd(float nbr, int fd)
{
	long		l;
	float		r;
	int			precision;

	precision = 10;
	if (nbr < 0 && nbr != INFINITY && nbr != -INFINITY)
	{
		ft_putstr_fd("-", fd);
		nbr = -nbr;
	}
	l = (long)nbr;
	r = 0.5;
	if (nbr == INFINITY || nbr == -INFINITY)
	{
		if (nbr == -INFINITY)
			ft_putstr_fd("-", fd);
		ft_putstr_fd("99999999999", fd);
		return ;
	}
	if ((fabs(nbr - l) >= r) && (precision == 0))
		l = ((l > 0) ? l + 1 : l - 1);
	this_part_two(l, fd);
	nbr = fabs(nbr - l);
	if (nbr > 0 && precision != 0)
		this_part_three(&nbr, l, &precision, fd);
}

t_float3		rt_vector_cross_p(t_float3 *v1, t_float3 *v2)
{
	t_float3	cross;

	cross.x = v1->y * v2->z - v1->z * v2->y;
	cross.y = v1->x * v2->z - v1->z * v2->x;
	cross.z = v1->x * v2->y - v1->y * v2->x;
	return (cross);
}

t_float3		get_noise_value_plane(t_object *obj, t_float3 *impact,
		int target)
{
	float		x;
	float		y;
	float		res;
	t_float3	color;

	(void)target;
	(void)obj;
	x = fmod(impact->x, 16);
	y = fmod(impact->y, 16);
	if (x < 0)
		x = 16 + x;
	if (y < 0)
		y = 16 + y;
	res = octave(x, y, obj->noisedata.octaves, obj->noisedata.persistence);
	color.x = \
		res * obj->noisedata.color1.x + obj->noisedata.color2.x * (1 - res);
	color.y = \
		res * obj->noisedata.color1.y + obj->noisedata.color2.y * (1 - res);
	color.z = \
		res * obj->noisedata.color1.z + obj->noisedata.color2.z * (1 - res);
	return (color);
}
