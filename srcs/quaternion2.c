/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:59 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 20:03:20 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	rt_euler_to_quaternion(float alpha, float beta, float omega,
		t_float4 *quaternion)
{
	t_float4	tmp;
	t_float3	axis;

	axis = (t_float3){.x = 1};
	rt_quaternion_create(&axis, alpha, &tmp);
	axis = (t_float3){.y = 1};
	rt_quaternion_create(&axis, beta, quaternion);
	rt_quaternion_multiply(*quaternion, tmp, quaternion);
	axis = (t_float3){.z = 1};
	rt_quaternion_create(&axis, omega, &tmp);
	rt_quaternion_multiply(tmp, *quaternion, quaternion);
}

void	rt_quaternion_to_euler(float *alpha, float *beta, float *omega,
		t_float4 *quaternion)
{
	float	sinr;
	float	cosr;
	float	sinp;
	float	siny;
	float	cosy;

	sinr = 2.0 * (quaternion->w * quaternion->x + quaternion->y
			* quaternion->z);
	cosr = 1.0 - 2.0 * (quaternion->x * quaternion->x + quaternion->y
			* quaternion->y);
	*alpha = atan2(sinr, cosr);
	sinp = 2.0 * (quaternion->w * quaternion->y - quaternion->z
			* quaternion->x);
	if (fabs(sinp) >= 1)
		*beta = copysign(M_PI / 2, sinp);
	else
		*beta = asin(sinp);
	siny = 2.0 * (quaternion->w * quaternion->z + quaternion->x
			* quaternion->y);
	cosy = 1.0 - 2.0 * (quaternion->y * quaternion->y + quaternion->z
			* quaternion->z);
	*omega = atan2(siny, cosy);
}
