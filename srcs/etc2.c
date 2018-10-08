/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:52 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 21:17:28 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			fade(float a)
{
	return (a * a * a * (a * (a * 6 - 15) + 10));
}

float			lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}

Uint32			getpixel(SDL_Surface *surface, int x, int y)
{
	int			bpp;
	Uint8		*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	else if (bpp == 4)
		return (*(Uint32 *)p);
	else
		return (0);
}

void			fill_matrix(float matrix[3][3], t_float3 *t,
				t_float3 *b, t_float3 *n)
{
	matrix[0][0] = t->x;
	matrix[0][1] = b->x;
	matrix[0][2] = n->x;
	matrix[1][0] = t->y;
	matrix[1][1] = b->y;
	matrix[1][2] = n->y;
	matrix[2][0] = t->z;
	matrix[2][1] = b->z;
	matrix[2][2] = n->z;
}

t_float3		rotate_normal(t_float3 *tex_normal,
				t_float3 *obj_normal, t_float3 *dir)
{
	t_float3	tangent;
	t_float3	btangent;
	float		matrix[3][3];

	tangent = rt_vector_cross_p(obj_normal, dir);
	rt_vector_normalize(&tangent);
	btangent = rt_vector_cross_p(&tangent, obj_normal);
	rt_vector_normalize(&btangent);
	fill_matrix(matrix, &tangent, &btangent, obj_normal);
	return (rt_matrix_apply(tex_normal, matrix));
}
