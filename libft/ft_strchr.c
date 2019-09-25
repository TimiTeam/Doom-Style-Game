/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:19:26 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/28 16:01:18 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int i)
{
	char			*ret;
	unsigned char	c;

	c = i;
	ret = NULL;
	while (*str)
	{
		if (*str == c)
		{
			ret = (char*)str;
			break ;
		}
		str++;
	}
	if (c == '\0')
		return ((char*)str);
	return (ret);
}
