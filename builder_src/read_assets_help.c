/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_assets_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:26:29 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 18:26:30 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			count_w(char const *s, int n)
{
	unsigned short		count;
	int					tmp;

	count = 0;
	s++;
	while (*s && *s != '\'')
	{
		if (ft_isdigit(*s))
		{
			tmp = ft_atoi(s);
			if (within(tmp, -1, n))
				count++;
			while (*s && ft_isdigit(*s))
				s++;
		}
		else if (*s != ' ')
			return (0);
		else
			s++;
	}
	return (count);
}

unsigned short			get_n(char *line, unsigned short min, \
unsigned short max)
{
	int					tmp;

	tmp = 0;
	while (*line && ft_isdigit(*line) == FALSE)
		line++;
	if (*line)
		tmp = ft_atoi(line);
	if (tmp >= min && tmp < max)
		return ((unsigned)tmp);
	else
		return (0);
}

int						read_item_type(char *line)
{
	static char			types[TOTAL_TYPES][12] = { "coin", "key", "object",\
	"enemy", "super_bonus", "health", "ammo", "gun", "light" };
	int					res;

	while (*line && !ft_isalpha(*line))
		line++;
	if (line)
	{
		res = -1;
		while (++res < TOTAL_TYPES)
		{
			if (*line == types[res][0])
				return (res);
		}
	}
	return (-1);
}
