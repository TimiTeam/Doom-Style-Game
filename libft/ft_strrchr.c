/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:59:18 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/28 16:01:29 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int i)
{
	char			*ret;
	unsigned char	c;

	c = i;
	ret = NULL;
	while (*s)
	{
		if (*s == c)
			ret = (char*)s;
		s++;
	}
	if (c == '\0')
		return ((char*)s);
	return (ret);
}
