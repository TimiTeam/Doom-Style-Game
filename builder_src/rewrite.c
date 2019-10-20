/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:10:21 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 20:10:23 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					write_wall_type(int type, int fd)
{
	if (type == filled)
		ft_putstr_fd(" filled ", fd);
	else if (type == empty)
		ft_putstr_fd(" empty ", fd);
	else if (type == window)
		ft_putstr_fd(" window ", fd);
	else if (type == transparent)
		ft_putstr_fd(" transparent ", fd);
}

unsigned short			write_assets(int fd, t_media *media)
{
	int i;

	i = 0;
	if (!media)
		return (FAIL);
	while (i < TOTAL_SECTIONS)
	{
		write_section(fd, media, i);
		i++;
	}
	return (SUCCESS);
}

unsigned short			write_level(int fd, t_world world)
{
	static char			count[3][12] = { "Vectors: ", "Walls: ", "Sectors: " };
	int					i;

	i = 0;
	while (i < 3)
	{
		ft_putstr_fd("Count ", fd);
		ft_putstr_fd(count[i], fd);
		if (i == 0)
			ft_putnbr_fd(world.n_v, fd);
		else if (i == 1)
			ft_putnbr_fd(world.n_w, fd);
		else if (i == 2)
			ft_putnbr_fd(world.n_s, fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
	i = -1;
	while (++i < 4)
		write_level_section(fd, world, i);
	return (SUCCESS);
}

unsigned short			rewrite_levels(t_media *media)
{
	int					fd;
	int					i;

	if (!media || !media->worlds)
		return (FAIL);
	i = -1;
	while (++i < media->n_worlds)
	{
		if (open_for_write(media->worlds[i].full_p, &fd) == FAIL)
			return (FAIL);
		if (write_level(fd, media->worlds[i]) == FAIL)
			return (FAIL);
		if (close_file(fd) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

unsigned short			rewrite_media(t_media *media)
{
	int					fd;

	if (!media)
		return (FAIL);
	if (open_for_write(ASSET_FILE, &fd) == FAIL)
	{
		ft_putendl("error in writing assets\n");
		return (FAIL);
	}
	if (write_assets(fd, media) == FAIL)
	{
		ft_putendl("error in writing assets\n");
		return (FAIL);
	}
	if (close_file(fd) == FAIL)
	{
		ft_putendl("error in writing assets\n");
		return (FAIL);
	}
	validate_media(media);
	rewrite_levels(media);
	return (SUCCESS);
}
