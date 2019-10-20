/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:22:50 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/09 16:23:19 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

char					*identify_extension(const char *line)
{
	char				*extension;
	size_t				i;
	size_t				len;

	if (!line || !(line = ft_strchr(line, '.')))
		return (NULL);
	len = ft_strlen(line);
	if (!(extension = ft_strdup(line)))
		return (NULL);
	i = 0;
	while (++i < len)
	{
		if (!ft_isalpha(extension[i]))
			return (NULL);
	}
	return (extension);
}

char					*identify_path(const char *line)
{
	char				*path;
	size_t				i;
	size_t				len;

	if (!line || !(line = ft_strchr(line, '.')))
		return (NULL);
	len = ft_strlen(line);
	if (!(path = ft_strdup(line)))
		return (NULL);
	i = 0;
	while (++i < len)
	{
		if (!ft_isalnum(path[i]) && path[i] != '.' && path[i] != '/')
			return (NULL);
	}
	return (path);
}

short					identify_section(const char *line)
{
	static const char	sections[TOTAL_SECTIONS][16] = { LEVELS, TEXTURES, \
						ITEMS };
	short				id;
	short				i;

	if (!line || !++line)
		return (-1);
	id = -1;
	i = -1;
	while (id == -1 && ++i < TOTAL_SECTIONS)
	{
		if (ft_tolower(line[0]) == ft_tolower(sections[i][0]))
			id = i;
	}
	return (id);
}
