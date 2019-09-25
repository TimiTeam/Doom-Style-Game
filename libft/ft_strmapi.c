/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 12:41:26 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/30 12:55:36 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	unsigned int	i;
	size_t			size;

	ret = NULL;
	i = 0;
	size = 0;
	if (s)
		size = ft_strlen(s);
	if ((ret = (char*)malloc(sizeof(char) * size + 1)))
	{
		while (i < (unsigned int)size)
		{
			ret[i] = f(i, *s);
			i++;
			s++;
		}
		ret[i] = '\0';
	}
	return (ret);
}
