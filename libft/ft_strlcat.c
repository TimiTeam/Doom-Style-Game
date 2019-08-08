/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:44:40 by tbujalo           #+#    #+#             */
/*   Updated: 2018/11/05 18:02:53 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const char	*d;
	const char	*s;
	size_t		n;
	size_t		len;

	d = dst;
	s = src;
	n = size;
	while (n-- != 0 && *dst != '\0')
		dst++;
	len = dst - d;
	n = size - len;
	if (n-- == 0)
		return (len + ft_strlen(src));
	while (*src != '\0')
	{
		if (n != 0)
		{
			*dst++ = *src;
			n--;
		}
		src++;
	}
	*dst = '\0';
	return (len + (src - s));
}
