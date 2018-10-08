/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:42:06 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/12 16:29:00 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *src, const char *tofind)
{
	int i;
	int j;

	i = 0;
	if (tofind[0] == '\0')
		return ((char*)src);
	while (src[i] != '\0')
	{
		j = 0;
		while (tofind[j] == src[i + j])
		{
			if (tofind[j + 1] == '\0')
				return ((char *)(src + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
