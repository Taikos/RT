/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:15 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 20:46:13 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** on considère une caméra en {0, 0, 0} orienté vers les x positifs
** et un ecran de projection placé en :
** x = 1
** un fov de 90 degré en radian => fov = 1.5708
**
**                 z             x (nord)
**                  |          /
**                  |        /
**                  |      /
**                  |    /
**                  |  /
**  -y (ouest) _____|/________ y (est)
**                 /|
**               /  |
**             /    |
**           /      |
**        -x (sud)   -z (altitude)
*/

void			rt_vector_cam(const size_t xwin, const size_t ywin,
		t_view **screen, const float fov)
{
	size_t		x;
	size_t		y;
	float		pitch;

	pitch = tanf(fov / 2.0) * 2.0 / xwin;
	y = 0;
	while (y < ywin)
	{
		x = 0;
		while (x < xwin)
		{
			screen[y][x].vector = (t_float3){.x = 1.0,
				.y = pitch * 0.5 + pitch * (x - xwin / 2.0),
				.z = pitch * -0.5 - pitch * (y - ywin / 2.0)};
			screen[y][x].origin = (t_float3){.x = 0,
				.y = screen[y][x].vector.y,
				.z = screen[y][x].vector.z};
			rt_vector_normalize(&screen[y][x].vector);
			x++;
		}
		y++;
	}
}

/*
** delta = b^2 - 4ac
** si delta est positif, il y a deux distances
** si delta est egale a 0 on a une distance
** sinon on a pas de collision
** pour les distances on a :
** (-b -sqrt(delta)) / 2a
** (-b +sqrt(delta)) / 2a
*/

void			rt_collider_delta(t_double3 *abc, t_impact *i)
{
	double		delta;

	delta = (double)abc->y * (double)abc->y - 4.0
		* (double)abc->x * (double)abc->z;
	if (delta >= 0)
	{
		delta = sqrt(delta);
		i->hit = TRUE;
		i->k1 = ((double)-abc->y + (double)delta) / (2.0 * (double)abc->x);
		i->k2 = ((double)-abc->y - (double)delta) / (2.0 * (double)abc->x);
	}
	else
		i->hit = FALSE;
}

t_float3		rt_vector_impact(t_float3 *origin, t_float3 *vector, float k)
{
	t_float3	impact;

	impact.x = vector->x * k + origin->x;
	impact.y = vector->y * k + origin->y;
	impact.z = vector->z * k + origin->z;
	return (impact);
}

void			rt_vector_normalize(t_float3 *vector)
{
	float		norme;

	norme = sqrtf(powf(vector->x, 2) + powf(vector->y, 2) + powf(vector->z, 2));
	vector->x /= norme;
	vector->y /= norme;
	vector->z /= norme;
}

void			rt_impact_to_visible(t_impact *cldr, t_visible *view, int id)
{
	*view = (t_visible){.visible = -1, .k = -1};
	if (cldr->hit & TRUE)
	{
		if (cldr->k1 > EPSILON && (cldr->hit & K1))
			view->k = cldr->k1;
		if (cldr->k2 > EPSILON && (cldr->hit & K2))
		{
			if (view->k < 0 || (view->k >= 0 && cldr->k2 < view->k))
				view->k = cldr->k2;
		}
		if (view->k >= 0)
			view->visible = id;
	}
}
