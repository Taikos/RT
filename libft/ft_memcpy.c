/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:56:54 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/12 10:21:08 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dt;
	unsigned char	*temp;

	temp = (unsigned char *)src;
	dt = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		dt[i] = temp[i];
		i++;
	}
	return (dt);
}
