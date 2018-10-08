/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:09:18 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/13 17:08:08 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*a;
	size_t			i;

	i = 0;
	if (!(a = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		return (NULL);
	while (i < size)
	{
		a[i] = 0;
		i++;
	}
	return (a);
}
