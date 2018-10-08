/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:12:10 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/18 09:21:58 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*dest;
	int		len;
	int		i;
	int		j;

	if (!(s))
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	j = 0;
	while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
		len--;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j++;
	len = len - j;
	if (len < 0)
		len = 0;
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
		dest[i++] = s[j++];
	dest[i] = '\0';
	return (dest);
}
