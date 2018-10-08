/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:12:42 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/20 16:55:10 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_itoa(int n)
{
	int i;

	i = 1;
	while (n / 10 != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*dest;
	int		len;
	int		minus;

	len = ft_len_itoa(n);
	minus = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		len = len + 1;
		minus = 1;
	}
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	dest[len] = '\0';
	while (len-- > 0)
	{
		dest[len] = n % 10 + 48;
		n = n / 10;
	}
	if (minus == 1)
		dest[0] = '-';
	return (dest);
}
