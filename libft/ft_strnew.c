/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:41:53 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/13 17:07:33 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	unsigned char	*a;
	size_t			i;

	i = 0;
	if (!(a = (unsigned char *)malloc(sizeof(unsigned char) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		a[i] = '\0';
		i++;
	}
	a[i] = '\0';
	return ((char *)a);
}
