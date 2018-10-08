/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:52 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:12:54 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		rt_atof_start(char *str)
{
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		pos = ((str[i] >= '1' && str[i] <= '9') && pos == 0) ? i + 1 : pos;
		i++;
	}
	if (pos != 0)
		pos = i + 1 - pos;
	else
		pos = -1;
	return (pos);
}

static int		rt_atof_power(int nb, int power)
{
	int	ret;

	ret = nb;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 1)
	{
		ret *= nb;
		power--;
	}
	return (ret);
}

static float	rt_atof_how_power(int i)
{
	if (i > 0)
		return ((float)rt_atof_power(10, i - 1));
	else if (i < 0)
		return (0.1);
	return (0);
}

static int		rt_atof_setup(int i, char *str, int *sg, float *rap)
{
	while ((str[i] == ' ') || (str[i] == '	') || (str[i] == '\n')
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	*sg = (str[i] == '-') ? -1 : 1;
	i += (str[i] == '+' || str[i] == '-') ? 1 : 0;
	*rap = rt_atof_how_power(rt_atof_start(&str[i]));
	while (str[i] == '0')
		i++;
	return (i);
}

double			rt_atof(char *str)
{
	double	ret;
	int		i;
	int		sg;
	float	rap;
	int		point;

	point = 1;
	ret = 0;
	i = 0;
	i = rt_atof_setup(i, str, &sg, &rap);
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] == '.' && point))
	{
		if (str[i] == '.')
			point = 0;
		else
		{
			ret = ret + ((str[i] - '0') * rap);
			rap = rap / 10;
		}
		i++;
	}
	return (ret * sg);
}
