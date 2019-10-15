/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_read_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 22:22:34 by tbujalo           #+#    #+#             */
/*   Updated: 2019/10/15 22:22:49 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

int				kip_to_word(char *data, char *to_word)
{
	int			i;

	i = 0;
	while (data[i] && ft_strncmp(&data[i], to_word,
				ft_strlen(to_word)) && !ft_isdigit(data[i]))
		i++;
	return (i);
}

int				get_wall_count(char *str)
{
	int			count;

	count = 0;
	while (*str && *str != '\'' && ft_strncmp(str, "items", ft_strlen("items")))
		str++;
	if (!str)
		return (0);
	str++;
	while (*str && *str != '\'' && ft_strncmp(str, "items", ft_strlen("items")))
	{
		if (ft_isdigit(*str))
		{
			count++;
			while (*str && ft_isdigit(*str))
				str++;
			continue ;
		}
		str++;
	}
	return (count);
}
