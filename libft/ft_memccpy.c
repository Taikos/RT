/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:47:26 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/12 10:09:05 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
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
		if (temp[i] == (unsigned char)c)
			return (&(dt[i + 1]));
		i++;
	}
	return (NULL);
}
