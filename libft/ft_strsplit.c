/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:12:28 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/20 16:54:23 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_insert(char const *s, char c, int i, char **dest)
{
	int a;
	int j;
	int count;

	a = 0;
	j = -1;
	count = 0;
	while (a <= i && s[j + 1] != '\0')
	{
		j++;
		if (s[j] != '\0' && s[j] != c)
		{
			while (s[j] != '\0' && s[j] != c)
			{
				dest[a][count] = s[j];
				count++;
				j++;
			}
			dest[a][count] = '\0';
			a++;
		}
		count = 0;
	}
	return (dest);
}

static int	ft_l_cnt(char const *s, char c, int i)
{
	int a;
	int j;
	int count;

	a = 0;
	j = -1;
	count = 0;
	while (a <= i)
	{
		j++;
		if (s[j] != c)
		{
			while (s[j] != c && s[j] != '\0')
			{
				count++;
				j++;
			}
			if (a == i)
				return (count);
			a++;
		}
		count = 0;
	}
	return (0);
}

static int	ft_w_count(char const *s, char c)
{
	int i;
	int word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			word++;
		}
	}
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**dest;
	int		word;
	int		i;

	if (!(s))
		return (NULL);
	word = ft_w_count(s, c);
	i = 0;
	if (!(dest = (char**)malloc(sizeof(char*) * (word + 1))))
		return (NULL);
	while (i < word)
	{
		if (!(dest[i] = (char*)malloc(sizeof(char) * (ft_l_cnt(s, c, i) + 1))))
			return (NULL);
		i++;
	}
	dest[i] = (char*)malloc(sizeof(char) * (1));
	ft_insert(s, c, i, dest);
	dest[i] = NULL;
	return (dest);
}
