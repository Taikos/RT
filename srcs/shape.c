/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:42 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 19:48:50 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** l'equation du plan étant z = 0,
** si Vz n'est pas nul :
**  - on trouve directement sa collision avec k = - Zpos / Vz
** sinon il n'y a pas de collision
*/

void	rt_collider_plane(t_float3 *origin, t_float3 *vector,
		const t_object *plane, t_impact *i)
{
	i->hit = TRUE;
	i->k1 = -origin->z / vector->z;
	i->k2 = i->k1;
	rt_apply_limits(plane, i, vector, origin);
}

/*
** l'equation de la sphere étant x^2 + y^2 + z^2 = R^2
** on calcul a, b et c tel que ak^2 + bk + c = 0
** on y integre l'equation de la droite (origine + vecteur)
** x = Xpos + kVx
** y = Ypos + kVy
** z = Zpos + kVz
** Avec :
**      - Xpos, Ypos et Zpos la position de la caméra, on a pris ici la
**      position inverse de l'objet afin de placer ce dernier en (0,0,0)
**      - Vx, Vy et Vz le vecteur concerné de la caméra
**      - k, la distance caméra <=> intersection que l'on cherche
** Ce qui nous donne (sans la position inverse) :
** a = Vx^2 + Vy^2 + Vz^2
** b = 2 * (Xpos * Vx + Ypos * Vy + Zpos * Vz)
** c = Xpos^2 + Ypos^2 + Zpos^2 - R^2
*/

void	rt_collider_sphere(t_float3 *origin, t_float3 *vector,
		const t_object *sphere, t_impact *i)
{
	t_double3 abc;

	abc.x = powf(vector->x, 2) + powf(vector->y, 2) + powf(vector->z, 2);
	abc.y = 2.0 * (origin->x * vector->x
			+ origin->y * vector->y
			+ origin->z * vector->z);
	abc.z = powf(origin->x, 2)
		+ powf(origin->y, 2)
		+ powf(origin->z, 2)
		- powf(sphere->ray, 2);
	rt_collider_delta(&abc, i);
	rt_apply_limits(sphere, i, vector, origin);
}

/*
** l'equation du cylindre étant
** x^2 + y^2 + z^2 - (ax + by + cz)^2 / (a^2 + b^2 + c^2) = R^2
** a b et c ici sont les valeurs du vecteur directionnel du cylindre,
** ici on prendra l'axe z
** après simplification on obtiens : x^2 + y^2 = R^2
** on calcul a, b et c tel que ak^2 + bk + c = 0
** on y integre l'equation de la droite (origine + vecteur)
** x = Xpos + kVx
** y = Ypos + kVy
** z = Zpos + kVz
** Avec :
**      - Xpos, Ypos et Zpos la position de la caméra, on a pris ici la
**      position inverse de l'objet afin de placer ce dernier en (0,0,0)
**      - Vx, Vy et Vz le vecteur concerné de la caméra
**      - k, la distance caméra <=> intersection que l'on cherche
** Ce qui nous donne (sans la position inverse) :
** a = Vx^2 + Vy^2
** b = 2 * (Xpos * Vx + Ypos * Vy)
** c = Xpos^2 + Ypos^2 - R^2
*/

void	rt_collider_cylinder(t_float3 *origin, t_float3 *vector,
		const t_object *cylinder, t_impact *i)
{
	t_double3 abc;

	abc.x = powf(vector->x, 2) + powf(vector->y, 2);
	abc.y = 2.0 * (origin->x * vector->x + origin->y * vector->y);
	abc.z = powf(origin->x, 2) + powf(origin->y, 2) - powf(cylinder->ray, 2);
	rt_collider_delta(&abc, i);
	rt_apply_limits(cylinder, i, vector, origin);
}

/*
** x^2 + y^2 - cte * z^2 = 0
** avec cte = tan(angle)^2 ici précalculé et stocké dans ray
**
** (Xpos + kVx)^2 + (Ypos + kVy)^2 - cte * (Zpos + kVz)^2 = 0
**
** + Xpos^2
** + Ypos^2
** - cte * Zpos^2
**
** 2 (Xpos * kVx + Ypos * kVy - cte * Zpos * kVz)
**
** + kVx^2
** + kVy^2
** - cte * kVz^2
**
**  ICI PAS DE RAYON MAIS UNE CONSTANTE QUE L'ON STOCK DANS LE RAYON
*/

void	rt_collider_cone(t_float3 *origin, t_float3 *vector,
		const t_object *cone, t_impact *i)
{
	t_double3 abc;

	abc.x = (double)vector->x * (double)vector->x
		+ (double)vector->y * (double)vector->y
		- (double)cone->ray * (double)vector->z * (double)vector->z;
	abc.y = 2.0 * ((double)origin->x * (double)vector->x
			+ (double)origin->y * (double)vector->y
			- (double)cone->ray * (double)origin->z * (double)vector->z);
	abc.z = (double)origin->x * (double)origin->x
		+ (double)origin->y * (double)origin->y
		- (double)cone->ray * (double)origin->z * (double)origin->z;
	rt_collider_delta(&abc, i);
	rt_apply_limits(cone, i, vector, origin);
}

/*
** l'equation du disque étant x^2 + y^2 <= R^2,
** si Vz n'est pas nul et que :
**  - on trouve directement sa collision avec k = - Zpos / Vz
** cette collision est temporaire et symbolise la collision avec le plan
** on vérifie que l'impact se situe dans le rayon correspondant du disque
** si c'est le cas on a collision
** sinon il n'y a pas de collision
*/

void	rt_collider_disk(t_float3 *origin, t_float3 *vector,
		const t_object *disk, t_impact *i)
{
	t_float3 v_i;

	i->hit = FALSE;
	i->k1 = -origin->z / vector->z;
	v_i = rt_vector_impact(origin, vector, i->k1);
	if (powf(v_i.x, 2) + powf(v_i.y, 2) <= powf(disk->ray, 2))
	{
		i->hit = TRUE;
		i->k2 = i->k1;
	}
	rt_apply_limits(disk, i, vector, origin);
}
