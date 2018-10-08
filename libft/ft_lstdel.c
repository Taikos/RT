/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 15:53:36 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/18 16:51:06 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if ((**alst).next)
	{
		ft_lstdel(&((**alst).next), (*del));
		ft_lstdelone(alst, (*del));
	}
	else
		ft_lstdelone(alst, (*del));
}
