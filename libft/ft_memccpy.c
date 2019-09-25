/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:13:17 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/29 19:21:15 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char			*d;
	unsigned char	*s;

	d = dst;
	s = (unsigned char*)src;
	if (n)
		while (n--)
			if ((*d++ = *s++) == (char)c)
				return (d);
	return (NULL);
}
