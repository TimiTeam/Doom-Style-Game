/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 10:12:20 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/30 10:28:31 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (size < 1000000000)
		if ((ret = (char*)malloc(sizeof(char) * size + 1)))
		{
			while (i < size)
				ret[i++] = 0;
			ret[i] = '\0';
			return (ret);
		}
	return (NULL);
}
