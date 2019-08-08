/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 12:28:51 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/30 12:40:47 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ret;
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	ret = NULL;
	if (s)
		size = ft_strlen(s);
	if (s && (ret = (char*)malloc(sizeof(char) * size + 1)))
	{
		while (i < size)
		{
			ret[i] = f(s[i]);
			i++;
		}
		ret[i] = '\0';
	}
	return (ret);
}
