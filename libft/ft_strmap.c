/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:14:07 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/13 17:39:53 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*a;
	int		i;

	i = 0;
	if (!(s) || !(f))
		return (NULL);
	if (!(a = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (NULL);
	while (*s)
	{
		a[i] = f(*s++);
		i++;
	}
	a[i] = '\0';
	return (a);
}
