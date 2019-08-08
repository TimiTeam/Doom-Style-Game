/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:24:47 by tbujalo           #+#    #+#             */
/*   Updated: 2018/11/09 16:05:33 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = dst;
	s = (char*)src;
	if (s < d)
		while (n--)
			*(d + n) = *(s + n);
	else if (s > d)
		while (n--)
			*d++ = *s++;
	return (dst);
}
