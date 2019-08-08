/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:53:49 by tbujalo           #+#    #+#             */
/*   Updated: 2018/11/01 16:52:08 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	char	*cp;

	new = NULL;
	if (content)
		cp = ft_strdup((char*)content);
	else
	{
		cp = NULL;
		content_size = 0;
	}
	if ((new = (t_list*)malloc(sizeof(t_list))))
	{
		new->content = cp;
		new->content_size = content_size;
		new->next = NULL;
	}
	return (new);
}
