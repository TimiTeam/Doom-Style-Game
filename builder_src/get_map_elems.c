/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_elems.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 19:13:56 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 19:13:58 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

short					get_wall_txtr(char *line, unsigned short min, \
unsigned short max)
{
	int					tmp;

	tmp = 0;
	while (*line && ft_isdigit(*line) == FALSE)
		line++;
	if (*line)
		tmp = ft_atoi(line);
	if (tmp >= min && tmp < max)
		return ((short)tmp);
	else
		return (-1);
}

unsigned				get_fl_ceil(char *line, int *h, short *txtr, \
unsigned short max_txtr)
{
	unsigned short		height_found;
	int					tmp;

	if (!line || !h || !txtr)
		return (FAIL);
	height_found = FALSE;
	while (*line)
	{
		if (ft_isdigit(*line) || *line == '-')
		{
			if (height_found == TRUE)
			{
				tmp = ft_atoi(line);
				*txtr = within(tmp, -1, max_txtr) ? tmp : 0;
				break ;
			}
			*h = clamp(ft_atoi(line++), MIN_HEIGHT, MAX_HEIGHT);
			height_found = TRUE;
			while (*line && ft_isdigit(*line))
				line++;
		}
		else
			line++;
	}
	return (SUCCESS);
}

int						s_walls(t_sec *s, char *l, int n_w)
{
	int					*walls;
	int					i;

	if (!n_w || !s || !(l = ft_strchr(l, '\'')) ||
	!within((s->n_w = count_w(l, n_w)), -1, 127))
		return (FAIL);
	if (!(walls = (int *)ft_memalloc(sizeof(int) * s->n_w)))
		return (FAIL);
	ft_bzero(walls, sizeof(int) * s->n_w);
	i = 0;
	while (*(++l) && *l != '\'' && i < s->n_w)
	{
		if (ft_isdigit(*l))
		{
			walls[i] = ft_atoi(l);
			if (within(walls[i], -1, n_w))
				i++;
			if (!(l = ft_strchr(l, ' ')))
				break ;
		}
		else if (*l != ' ')
			return (FAIL);
	}
	s->s_walls = walls;
	return (SUCCESS);
}

int						fl_ceil(t_sec *sector, char *line)
{
	if (!sector || !line)
		return (FAIL);
	sector->fl = 0;
	sector->fl_t = 0;
	sector->ceil = 0;
	sector->ceil_t = 0;
	if (!(line = ft_strchr(line, 'f')))
		return (FAIL);
	if (get_fl_ceil(line, &sector->fl, &sector->fl_t, MAX_N_TXTRS)
		== FAIL)
		return (FAIL);
	if (!(line = ft_strchr(line, 'c')))
		return (FAIL);
	if (get_fl_ceil(line, &sector->ceil, &sector->ceil_t, MAX_N_TXTRS)
		== FAIL)
		return (FAIL);
	return (SUCCESS);
}

void					get_walls(t_wall *wall, char *line, t_vec p)
{
	if (!wall || !line)
		return ;
	wall->v1 = p.x;
	wall->v2 = p.y;
	while (*line && !ft_isalpha(*line))
		line++;
	wall->type = empty;
	if (*line == 'f' || *line == 'F')
		wall->type = filled;
	else if (*line == 't' || *line == 'T')
		wall->type = transparent;
	else if (*line == 'w' || *line == 'W')
		wall->type = window;
	wall->txtr = get_wall_txtr(line, 0, MAX_N_TXTRS);
}
