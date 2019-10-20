/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:10:42 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 18:15:24 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					write_item_type(int type, int fd)
{
	static char			types[TOTAL_TYPES][13] = { "coin ", "key ", "object ",\
	"enemy ", "super_bonus ", "health ", "ammo ", "gun ", "light " };

	if (type >= 0 && type < TOTAL_TYPES)
	{
		ft_putstr_fd(types[type], fd);
	}
}

int						get_n_files(int section, t_media *media)
{
	if (media)
	{
		if (section == 0)
			return (media->n_worlds);
		else if (section == 1)
			return (media->n_t);
		else if (section == 2)
			return (media->n_itf);
	}
	return (-1);
}

void					write_file(int section, int i, int fd, t_media *media)
{
	if (!media)
		return ;
	ft_putnbr_fd(i, fd);
	ft_putstr_fd(") ", fd);
	if (section == 0 && media->worlds && media->worlds[i].name)
		ft_putstr_fd(media->worlds[i].name, fd);
	else if (section == 1 && media->txtr && media->txtr[i].name)
		ft_putstr_fd(media->txtr[i].name, fd);
	else if (section == 2 && media->it_f && media->it_f[i].name)
	{
		if (!ft_strcmp("jetpack", media->it_f[i].name))
			ft_putstr_fd("objectjetpack ", fd);
		else
			write_item_type(media->it_f[i].type, fd);
		ft_putstr_fd(media->it_f[i].name, fd);
	}
	ft_putchar_fd('\n', fd);
}

void					write_head(int line, t_media *media, int section, \
int fd)
{
	static char			title[TOTAL_SECTIONS][11] = { "Levels", "Textures ", \
	"Items" };
	static char			prefix[5][13] = { "#", "Path: ", "Extension: ",\
	"File Names: ", "###" };

	if (!media)
		return ;
	ft_putstr_fd(prefix[line], fd);
	if (line == 0 && title[section])
	{
		ft_putstr_fd(title[section], fd);
		if (section == 1)
			ft_putnbr_fd(media->n_t, fd);
	}
	else if (line == 1 && media->paths[section])
		ft_putstr_fd(media->paths[section], fd);
	else if (line == 2 && media->extensions[section])
		ft_putstr_fd(media->extensions[section], fd);
	ft_putchar_fd('\n', fd);
}

unsigned short			write_section(int fd, t_media *media, int section)
{
	unsigned short		line;
	unsigned short		i;
	int					n_files;

	if (!media)
		return (FAIL);
	line = -1;
	while (++line < 4)
		write_head(line, media, section, fd);
	if ((n_files = get_n_files(section, media)) == -1)
		return (FAIL);
	n_files = clamp(n_files, 0, 300);
	i = -1;
	while (++i < n_files)
		write_file(section, i, fd, media);
	ft_putendl_fd("###", fd);
	ft_putchar_fd('\n', fd);
	return (SUCCESS);
}
