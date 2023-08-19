/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:14:58 by apanikov          #+#    #+#             */
/*   Updated: 2023/02/07 18:40:20 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*j;
	t_list	*r;

	j = lst;
	if (!lst)
		return (0);
	new = ft_lstnew((*f)(j->content));
	if (!new)
		return (0);
	r = new;
	j = j->next;
	while (j)
	{
		new->next = ft_lstnew((*f)(j->content));
		if (!new->next)
		{
			ft_lstdelone(r, (*del));
			return (0);
		}
		new = new->next;
		j = j->next;
	}
	return (r);
}
