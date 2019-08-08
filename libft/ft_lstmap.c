/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:12:08 by tbujalo           #+#    #+#             */
/*   Updated: 2018/11/02 14:05:02 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*list;

	if (!lst)
		return (NULL);
	list = f(lst);
	ret = list;
	while (lst->next)
	{
		lst = lst->next;
		if (!(list->next = f(lst)))
			return (NULL);
		list = list->next;
	}
	return (ret);
}
