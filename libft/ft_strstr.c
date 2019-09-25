/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:22:24 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/29 13:42:20 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	char	*st1;
	char	*st2;

	if (!*s2)
		return ((char*)s1);
	while (*s1)
	{
		st1 = (char*)s1;
		st2 = (char*)s2;
		while (*st1 == *st2 && *st1 && *st2)
		{
			st1++;
			st2++;
		}
		if (!*st2)
			return ((char*)s1);
		s1++;
	}
	return (NULL);
}
