/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:41:19 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/13 17:43:26 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*a;
	int		i;

	i = 0;
	if (!(s) || !(f))
		return (NULL);
	if (!(a = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (0);
	while (*s)
	{
		a[i] = f(i, *s++);
		i++;
	}
	a[i] = '\0';
	return (a);
}
