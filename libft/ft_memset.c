/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:07:52 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/18 17:11:30 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	temp = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		temp[i] = (unsigned char)c;
		i++;
	}
	return (temp);
}
