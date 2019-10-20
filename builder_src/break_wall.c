/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 18:54:43 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/11 13:46:18 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					break_in(int *s_walls, int n, int prev)
{
	int					new;
	int					tmp[n];
	int					k;
	int					i;

	new = n - 1;
	i = 0;
	while (i < n)
	{
		tmp[i] = s_walls[i];
		i++;
	}
	i = 0;
	while (i < prev)
		i++;
	s_walls[i++] = tmp[new];
	while (i < n)
	{
		k = i - 1;
		if (k < 0)
			k = n - 1;
		s_walls[i++] = tmp[k];
	}
}

void					add_broken_secwall(t_world *w, int wall, int new_id, \
int i)
{
	int					j;
	int					pn[2];

	j = -1;
	while (++j < w->sec[i].n_w)
	{
		if (w->sec[i].s_walls[j] != wall)
			continue ;
		add_secwall(&w->sec[i].s_walls, w->sec[i].n_w++, new_id);
		if ((pn[0] = j - 1) < 0)
			pn[0] = w->sec[i].n_w - 2;
		if ((pn[1] = j + 1) >= w->sec[i].n_w)
			pn[1] = 0;
		break_in(w->sec[i].s_walls, w->sec[i].n_w, \
		w->walls[w->sec[i].s_walls[pn[0]]].v1 != \
		w->walls[w->sec[i].s_walls[j]].v1 &&
		w->walls[w->sec[i].s_walls[pn[0]]].v2 != \
		w->walls[w->sec[i].s_walls[j]].v1 ? pn[0] : pn[1]);
		if (w->sec[i].v)
			free(w->sec[i].v);
		get_sec_v(&w->sec[i], w->walls);
		make_continuous(&w->sec[i], w, i);
		validate_clockwise(w, i);
		break ;
	}
}

void					break_secwall(t_world *w, int wall, int new_id, \
int s)
{
	int					i;

	if (!w || !w->sec || !w->walls)
		return ;
	i = -1;
	while (++i < w->n_s)
	{
		if (i == s)
			continue ;
		add_broken_secwall(w, wall, new_id, i);
	}
}

unsigned short			break_wall(t_world *world, int vec, int wall, int s)
{
	int					two;
	int					new_id;

	if (!world || !within(wall, -1, world->n_w) || !within(vec, -1, world->n_v))
		return (FAIL);
	two = world->walls[wall].v2;
	if (add_wall(&world->walls, world->n_w, vec, two) == FAIL)
		return (FAIL);
	new_id = world->n_w;
	world->walls[wall].v2 = vec;
	world->n_w++;
	break_secwall(world, wall, new_id, s);
	return (SUCCESS);
}
