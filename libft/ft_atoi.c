/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 09:38:35 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/18 18:06:50 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long	a;
	long	minus;
	long	result;

	a = 0;
	minus = 1;
	result = 0;
	while (str[a] != '\0' && (str[a] == '\t' || str[a] == '\v'
	|| str[a] == '\n' || str[a] == '\r' || str[a] == '\f' || str[a] == ' '))
		a++;
	if (str[a] == '+')
		a++;
	else if (str[a] == '-')
	{
		minus = -1;
		a++;
	}
	while (str[a] != '\0' && (str[a] >= '0' && str[a] <= '9'))
	{
		result = (result * 10) + (str[a] - 48);
		a++;
	}
	return (minus * result);
}
