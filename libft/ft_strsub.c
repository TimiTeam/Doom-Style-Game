/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:21:50 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/30 13:39:36 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = NULL;
	if (s)
		if ((ret = (char*)malloc(sizeof(char) * len + 1)))
		{
			while (i < len)
				ret[i++] = s[start++];
			ret[i] = '\0';
		}
	return (ret);
}
