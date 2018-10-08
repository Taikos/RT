/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:11:54 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/18 09:20:20 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	if (!(s1) || !(s2))
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = 0;
	l = 0;
	if (!(dest = (char *)malloc(sizeof(char) * (i + j))))
		return (NULL);
	while (s1[l])
		dest[k++] = s1[l++];
	l = 0;
	while (s2[l])
		dest[k++] = s2[l++];
	dest[k] = '\0';
	return (dest);
}
