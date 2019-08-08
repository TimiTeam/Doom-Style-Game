/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 21:28:44 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/31 16:16:51 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ret;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(str);
	if ((ret = (char*)malloc(sizeof(char) * (size + 1))))
	{
		while (i < size)
		{
			ret[i] = str[i];
			i++;
		}
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}
