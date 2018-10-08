/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 16:51:30 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/19 09:56:38 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tempf;

	if (lst)
	{
		tempf = f(lst);
		(*tempf).next = ft_lstmap((*lst).next, f);
		return (tempf);
	}
	else
		return (NULL);
}
