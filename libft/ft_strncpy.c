/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:57:09 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/28 14:58:11 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t l)
{
	char	*d;
	char	*s;

	if (l > 0)
	{
		d = dst;
		s = (char*)src;
		while (l != 0)
		{
			if (*s == '\0' && l > 0)
			{
				while (l != 0)
				{
					*d++ = '\0';
					l--;
				}
				break ;
			}
			*d++ = *s++;
			l--;
		}
	}
	return (dst);
}
