/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:59 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 20:06:24 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

/*
** Relations quaternonique :
** i^2 = j^2 = k^2 = ijk = -1
**
** Donc : i^2 = -1 | j^2 = -1 | k^2 = -1
**        ij = k   | jk = i   | ki = j
**        ji = -k  | kj = -i  | ik = -j
**
** Tout quaternion q s'ecrit sous la forme :
** q = a + bi + cj + dk
**
** ex : q1 = 3i - k   et   q2 = 2 + j + k
**
** q1q2 = (3i - k)(2 + j + k)
**      = 3i(2 + j + k) - k(2 + j + k)
**      = 6i + 3ij + 3ik - 2k - kj - k^2
**      = 6i + 3k - 3j - 2k + i + 1
**      = 1 + 7i - 3j + k
*/

void			rt_quaternion_create(t_float3 *axis, float alpha,
		t_float4 *quaternion)
{
	float		a;
	float		s_a;

	a = alpha / 2.0;
	s_a = sinf(a);
	quaternion->w = cosf(a);
	quaternion->x = axis->x * s_a;
	quaternion->y = axis->y * s_a;
	quaternion->z = axis->z * s_a;
}

void			rt_quaternion_multiply(t_float4 q1, t_float4 q2,
		t_float4 *result)
{
	result->w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result->x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result->y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result->z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
}

void			rt_quaternion_apply(t_float4 *q, t_float3 v, t_float3 *result)
{
	float		values[9];

	values[0] = q->w * q->x;
	values[1] = q->w * q->y;
	values[2] = q->w * q->z;
	values[3] = -q->x * q->x;
	values[4] = q->x * q->y;
	values[5] = q->x * q->z;
	values[6] = -q->y * q->y;
	values[7] = q->y * q->z;
	values[8] = -q->z * q->z;
	result->x = 2 * ((values[6] + values[8]) * v.x + (values[4] - values[2])
				* v.y + (values[1] + values[5]) * v.z) + v.x;
	result->y = 2 * ((values[2] + values[4]) * v.x + (values[3] + values[8])
				* v.y + (values[7] - values[0]) * v.z) + v.y;
	result->z = 2 * ((values[5] - values[1]) * v.x + (values[0] + values[7])
				* v.y + (values[3] + values[6]) * v.z) + v.z;
}

void			rt_quaternion_to_matrix(t_float4 *q, float m[3][3])
{
	float		values[9];

	values[0] = q->x * q->x;
	values[1] = q->x * q->y;
	values[2] = q->x * q->z;
	values[3] = q->x * q->w;
	values[4] = q->y * q->y;
	values[5] = q->y * q->z;
	values[6] = q->y * q->w;
	values[7] = q->z * q->z;
	values[8] = q->z * q->w;
	m[0][0] = 1 - 2 * (values[4] + values[7]);
	m[0][1] = 2 * (values[1] - values[8]);
	m[0][2] = 2 * (values[2] + values[6]);
	m[1][0] = 2 * (values[1] + values[8]);
	m[1][1] = 1 - 2 * (values[0] + values[7]);
	m[1][2] = 2 * (values[5] - values[3]);
	m[2][0] = 2 * (values[2] - values[6]);
	m[2][1] = 2 * (values[5] + values[3]);
	m[2][2] = 1 - 2 * (values[0] + values[4]);
}

t_float3		rt_matrix_apply(t_float3 *vector, float matrix[3][3])
{
	t_float3	result;

	result.x = vector->x * matrix[0][0] + vector->y * matrix[0][1] + vector->z
				* matrix[0][2];
	result.y = vector->x * matrix[1][0] + vector->y * matrix[1][1] + vector->z
				* matrix[1][2];
	result.z = vector->x * matrix[2][0] + vector->y * matrix[2][1] + vector->z
				* matrix[2][2];
	return (result);
}
