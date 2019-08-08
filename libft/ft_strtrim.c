/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:36:30 by tbujalo           #+#    #+#             */
/*   Updated: 2018/10/30 16:44:18 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		max;
	int		min;
	int		p;

	p = 0;
	min = 0;
	if (!s)
		return (NULL);
	max = ft_strlen(s) - 1;
	while (is_space(s[min]))
		min++;
	while (is_space(s[max]))
		max--;
	if (max < 0)
		max = min - 1;
	if ((str = (char*)malloc(sizeof(char) * ((max += 1) - min) + 1)))
	{
		while (min < max)
			str[p++] = s[min++];
		str[p] = '\0';
	}
	return (str);
}
