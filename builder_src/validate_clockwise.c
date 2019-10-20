/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_clockwise.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:55:22 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 16:55:23 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

int						*reverse_order(int *p, int n_p)
{
	int					*tab;
	int					i;
	int					j;

	if (p)
	{
		if (!(tab = (int *)ft_memalloc(sizeof(int) * n_p)))
			return (NULL);
		i = 0;
		j = n_p - 1;
		while (i < n_p)
			tab[j--] = p[i++];
		free(p);
		return (tab);
	}
	return (NULL);
}

void					make_continuous(t_sec *sec, t_world *world, int sec_no)
{
	int					i;
	int					j;
	static char			tab[MAX_N_WALLS] = { 0 };

	if (!world || !sec || !world->walls || !sec->s_walls || !sec->v)
		return ;
	if (sec_no == 0)
	{
		ft_memset(tab, '0', sizeof(char) * MAX_N_WALLS);
	}
	i = 0;
	j = 0;
	while (j < sec->n_w)
	{
		if (tab[sec->s_walls[j]] == '0')
		{
			world->walls[sec->s_walls[j]].v1 = sec->v[i];
			world->walls[sec->s_walls[j]].v2 = sec->v[(i + 1) % sec->n_v];
			tab[sec->s_walls[j]] = '1';
		}
		j++;
		i++;
	}
}

void					validate_clockwise(t_world *world, int sec)
{
	int					i;
	int					sum;
	t_vec				one;
	t_vec				two;

	if (!world)
		return ;
	i = 0;
	sum = 0;
	while (i < world->sec[sec].n_v)
	{
		one = world->vecs[world->sec[sec].v[i]];
		two = world->vecs[world->sec[sec].v[(i + 1) % world->sec[sec].n_v]];
		sum += (two.x - one.x) * (one.y + two.y);
		i++;
	}
	if (sum > 0)
	{
		world->sec[sec].s_walls = reverse_order(world->sec[sec].s_walls, \
		world->sec[sec].n_w);
		free(world->sec[sec].v);
		get_sec_v(&world->sec[sec], world->walls);
	}
	make_continuous(&world->sec[sec], world, sec);
}
