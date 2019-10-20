/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:26:51 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/09 17:10:17 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

int						sector_closed(int *tmp, int n)
{
	int					i;

	if (!tmp)
		return (FALSE);
	if (tmp[0] != tmp[n - 1])
		return (FALSE);
	i = 1;
	while (i < n - 2)
	{
		if (tmp[i] != tmp[i + 1])
			return (FALSE);
		i += 2;
	}
	return (TRUE);
}

unsigned short			get_status_read(char *line, unsigned short status)
{
	static char			tab[5] = "0VWSP";
	int					j;

	if (!line)
		return (status);
	j = -1;
	while (++j < 5 && tab[j] && line[0])
	{
		if (tab[j] != line[0])
			continue ;
		status = j;
		break ;
	}
	return (status);
}

unsigned				read_map(int fd, t_world *world, \
unsigned short world_no, int ret)
{
	char				*line;
	unsigned short		i_st[2];

	if (!world || fd < 1)
		return (FAIL);
	i_st[1] = 0;
	line = NULL;
	i_st[0] = -1;
	while ((ret = get_next_line(fd, &(line))) == 1)
	{
		if (++i_st[0] == 0 && init_vec(line, world) == FAIL)
			break ;
		else if (i_st[0] == 1 && init_walls(line, world) == FAIL)
			break ;
		else if (i_st[0] == 2 && init_sec(line, world) == FAIL)
			break ;
		else if (!(ft_isdigit(line[0]) && i_st[1] > 0 && i_st[1] < 6))
			i_st[1] = get_status_read(line, i_st[1]);
		else if (read_line(line, i_st[1], world, world_no) == FAIL)
			break ;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (ret != 0 ? FAIL : SUCCESS);
}

unsigned				get_map(t_world *world, unsigned short world_no)
{
	int					fd;
	int					i;

	if (!world || !world->full_p)
		return (FAIL);
	if (open_for_read(world->full_p, &fd) == FAIL)
		return (FAIL);
	if (read_map(fd, world, world_no, 0) == FAIL)
		return (FAIL);
	i = 0;
	while (i < world->n_s)
		get_sec_v(&world->sec[i++], world->walls);
	if (close_file(fd) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
