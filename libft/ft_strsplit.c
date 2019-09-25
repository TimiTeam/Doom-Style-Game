/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:00:13 by tbujalo           #+#    #+#             */
/*   Updated: 2018/11/09 15:55:47 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	w_c(const char *s, char c)
{
	int		wc;

	wc = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			wc++;
			while (*s != c && *s)
				s++;
		}
	}
	return (wc);
}

static char	*get_word(const char *str, int *si, int end)
{
	char	*ret;
	int		i;
	int		size;

	size = *si;
	i = 0;
	ret = (char*)malloc(sizeof(char) * size + 1);
	while (size)
		ret[i++] = str[end - size--];
	ret[i] = '\0';
	*si = 0;
	return (ret);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		i;
	int		j;
	int		lenw;

	j = 0;
	lenw = 0;
	i = 0;
	if (!s || !c || !(array = (char**)malloc(sizeof(char*) * w_c(s, c) + 1)))
		return (NULL);
	while (s[i] && j < w_c(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			lenw++;
		}
		array[j++] = get_word(s, &lenw, i);
	}
	array[j] = 0;
	return (array);
}
