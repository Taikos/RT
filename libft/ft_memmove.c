/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:32:34 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/13 15:03:22 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tsrc;
	unsigned char	*tdest;

	tdest = (unsigned char *)dest;
	tsrc = (unsigned char *)src;
	if (src < dest)
	{
		while (n--)
			tdest[n] = tsrc[n];
		return (tdest);
	}
	else
		return (ft_memcpy(tdest, tsrc, n));
}
