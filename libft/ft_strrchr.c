/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:24:51 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/18 17:39:49 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t i;

	i = ft_strlen(s);
	while (i)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	if ((char)c == '\0' || s[i] == c)
		return ((char *)(s + i));
	else
		return (NULL);
}
