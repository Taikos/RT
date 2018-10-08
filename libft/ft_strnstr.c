/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:12:18 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/13 13:13:52 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *tofind, size_t n)
{
	int i;
	int j;

	i = 0;
	if (tofind[0] == '\0')
		return ((char*)src);
	while (src[i] != '\0' && n > 0)
	{
		j = 0;
		while (tofind[j] == src[i + j] && (n - j > 0))
		{
			if (tofind[j + 1] == '\0')
				return ((char *)(src + i));
			j++;
		}
		i++;
		n--;
	}
	return (NULL);
}
