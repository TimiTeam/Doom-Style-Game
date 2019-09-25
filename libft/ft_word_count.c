/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:36:16 by tbujalo           #+#    #+#             */
/*   Updated: 2018/11/09 19:00:42 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_word_count(char *words, char s)
{
	char	*str;

	if (!words || !s)
		return (0);
	str = words;
	while (*str == s && *str)
		str++;
	if (*str != '\0' && *str != s)
	{
		while (*str != s && *str)
			str++;
		return (1 + ft_word_count(str, s));
	}
	return (0);
}
