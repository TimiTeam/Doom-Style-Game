/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:19:36 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 12:19:38 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

char					*get_name(int i)
{
	char				*nb;
	char				*name;

	nb = ft_itoa(i);
	if (nb)
	{
		name = ft_strjoin("new_level_", nb);
		free(nb);
		if (name)
			return (name);
	}
	return (NULL);
}

char					*get_full_p(char *name, char *ext, char *path)
{
	char				*with_path;
	char				*res;

	if (!path || !ext || !name)
		return (NULL);
	with_path = ft_strjoin(path, name);
	if (with_path)
	{
		res = ft_strjoin(with_path, ext);
		free(with_path);
		if (res)
			return (res);
	}
	return (NULL);
}
