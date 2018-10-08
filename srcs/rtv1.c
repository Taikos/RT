/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:15 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 21:05:17 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		this_oriented_normal(t_float3 *vector, t_float3 *normal)
{
	float		angle;

	angle = rt_vector_angle(normal, vector);
	angle += (angle >= 3.0 * M_PI / 2.0 ? -2.0 * M_PI : 0.0);
	if (-M_PI / 2.0 <= angle && angle <= M_PI / 2.0)
	{
		normal->x *= -1;
		normal->y *= -1;
		normal->z *= -1;
	}
}

t_float3		rt_collider_normal(t_object *object, t_float3 *origin,
		t_float3 *vector, float k)
{
	t_float3	normal;

	if (object->type == PLANE || object->type == DISK)
	{
		if (origin->z >= 0.0)
			normal = (t_float3){.x = 0.0, .y = 0.0, .z = 1.0};
		else
			normal = (t_float3){.x = 0.0, .y = 0.0, .z = -1.0};
		rt_vector_normalize(&normal);
	}
	else
	{
		normal = rt_vector_impact(origin, vector, k);
		if (object->type == CYLINDER)
			normal.z = 0.0;
		else if (object->type == CONE)
			normal.z -= (normal.z < 0 ? -1 : 1) * (sqrtf(powf(normal.z, 2)
						+ powf(normal.y, 2) + powf(normal.x, 2))
						/ cosf(object->alpha));
		rt_vector_normalize(&normal);
		this_oriented_normal(vector, &normal);
	}
	return (normal);
}

float			rt_vector_angle(t_float3 *v1, t_float3 *v2)
{
	float		alpha;

	alpha = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	alpha = (alpha > 1 ? 1 : alpha);
	alpha = (alpha < -1 ? -1 : alpha);
	alpha = acosf(alpha);
	return (alpha);
}

void			rt_light_diffuse(const t_float3 *color_obj,
		const t_float3 *lightning, const float alpha_nl, t_float3 *target)
{
	t_float3	color;

	rt_float3_mult(color_obj, lightning, &color);
	target->x += color.x * alpha_nl;
	target->y += color.y * alpha_nl;
	target->z += color.z * alpha_nl;
}

void			rt_light(const t_object *object, const t_light *light,
		t_refl_refr *ref, const t_float3 *vector)
{
	t_float3	kolor;
	float		alpha;

	alpha = rt_vector_dot_p(&ref->normal, &ref->light);
	if (alpha > 0)
	{
		rt_float3_mult_float(&ref->kd, 1 - object->transparency, &kolor);
		rt_light_diffuse(&kolor, &light->luminance, alpha,
				&ref->color);
		ref->normal_h = (t_float3){.x = ref->light.x - vector->x,
			.y = ref->light.y - vector->y, .z = ref->light.z - vector->z};
		rt_vector_normalize(&ref->normal_h);
		alpha = powf(rt_vector_dot_p(&ref->normal, &ref->normal_h), object->ns);
		rt_light_diffuse(&ref->ks, &light->luminance, alpha,
				&ref->color);
	}
}

/*
**	Pour calculer le vecteur AB partant du point A vers le point B,
**	on soustrait la position de B à A soit :
**		AB = B - A.(Math 1)
**	On soustrait toujours le point d'arrivée au point de départ.
**
**	Pour calculer la longueur d'un vecteur
**	(utile pour la distance d'intersection) on utilise la formule :
**  	 |AB| = sqrt( X^2 + Y^2 + Z^2 ). (Math 2)
**	Un vecteur unitaire est un vecteur qui à pour longueur 1 : |AB| = 1.
**
**	Normaliser un vecteur consiste un rendre un vecteur
**	d'une longueur quelquonque en vecteur unitaire.
**	Pour cela il suffit de diviser chaque composante du vecteur (x, y, z),
**	par la longueur du vecteur.
**	Pour normaliser le vecteur A par exemple :
**	   A = ( Ax/|A|, Ay/|A|, Az/|A| ).(Math 3)
**
**	Pour calculer l'angle formé par deux vecteurs A et B
**	(utile dans le calcul de l'éclairage), on utilise le Dot Product.
**	La formule du Dot Product (produit scalaire) est la suivante :
**	   A dot B = |A||B|cos(A,B)= Ax*Bx + Ay*By + Az*Bz. (Math 4)
**	La plupart du temps les deux vecteurs A et B sont
**	normalisés avant le calcul, ce qui permet d'éliminer
**	la premiére partie de l'équation et de ne garder que :
**										cos(A,B)= Ax*Bx + Ay*By + Az*Bz.
**	Le cross product (produit vectoriel) permet quand à lui de calculer
**	un vecteur perpidenculaire aux deux autres
**	(en fait perpendiculaire au plan formé par les deux autres vecteurs).
**	Le vecteur résultant peut avoir deux directions différentes.
**	C'est en fait l'ordre de l'opération
**	qui determine la direction du vecteur final.
**	La formule du cross product  est la suivante :
**	   A*B = ( Ay*Bz-By*Az , Az*Bx-Bz*Ax , Ax*By-Bx*Ay ) (Math 5)
**
**	Un rayon dans un raytracer posséde trois caractéristiques :
**
**	-Une position O de départ(la source d'émission du rayon (vecteur))
**	-Un vecteur DIR de direction
**	-Une variable 't' représentant la distance parcourue par le rayon
**
**	Toutes ces caractéristiques se retrouvent dans l'équation d'un rayon,
**	la seule inconnue étant t.
**
**		ray = O + DIR * t
**
**	L'équation d'un rayon une fois résolue donne
**	donc une position dans l'espace, correspondante
**	la plupart du temps au point d'intersection du rayon avec un objet.
*/
