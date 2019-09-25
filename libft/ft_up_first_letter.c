/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_up_first_leter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:14:51 by tbujalo           #+#    #+#             */
/*   Updated: 2018/11/05 17:41:31 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_up_first_letter(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = str;
	if (!str)
		return (NULL);
	while (str[i])
	{
		while (str[i] <= 32 && str[i])
			i++;
		if (!str[i])
			break ;
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		while (str[i] > 32 && str[i])
			i++;
	}
	return (ret);
}
