/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:17:04 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 16:17:06 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

int						my_rename(const char *oldname, const char *newname)
{
	char				*tmp;
	char				*tmp2;

	if (!oldname || !newname)
		return (FAIL);
	tmp = ft_strjoin("mv ", oldname);
	if (tmp)
	{
		tmp2 = ft_strjoin(tmp, " ");
		free(tmp);
		if (tmp2)
		{
			tmp = ft_strjoin(tmp2, newname);
			free(tmp2);
			if (tmp)
			{
				system(tmp);
				free(tmp);
				return (SUCCESS);
			}
		}
	}
	return (FAIL);
}

unsigned				open_for_write(const char *path, int *fd)
{
	if (!path || !fd)
		return (FAIL);
	*fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR |\
	S_IRGRP | S_IROTH);
	if (*fd == -1)
		return (FAIL);
	return (SUCCESS);
}

unsigned				close_file(int fd)
{
	if (close(fd) == -1)
		return (FAIL);
	return (SUCCESS);
}

unsigned				open_for_read(const char *path, int *fd)
{
	if (!path || !fd)
		return (FAIL);
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
		return (FAIL);
	return (SUCCESS);
}
