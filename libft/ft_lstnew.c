/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 15:02:42 by arguerin          #+#    #+#             */
/*   Updated: 2017/04/18 15:37:39 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;

	if ((lst = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	lst->next = NULL;
	if (content == NULL)
	{
		lst->content_size = 0;
		lst->content = NULL;
	}
	else
	{
		lst->content_size = content_size;
		lst->content = (void *)malloc(lst->content_size);
		if (!lst->content)
		{
			ft_memdel((void**)&lst);
			return (NULL);
		}
		ft_memcpy(lst->content, content, lst->content_size);
	}
	return (lst);
}
