/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:28:08 by tbujalo           #+#    #+#             */
/*   Updated: 2018/11/04 16:45:58 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	char	*st1;
	char	*st2;
	size_t	l;

	if (!*s2 || (ft_strcmp(s1, s2)) == 0)
		return ((char*)s1);
	while (*s1 && len)
	{
		st1 = (char*)s1;
		st2 = (char*)s2;
		l = len--;
		while (*st1 == *st2 && *st2 && *st1 && l)
		{
			l--;
			st1++;
			st2++;
		}
		if (!*st2)
			return ((char*)s1);
		s1++;
	}
	return (NULL);
}
