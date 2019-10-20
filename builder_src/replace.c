/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:48:20 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 16:48:21 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					replace_vector(int to_replace, int new, t_world *world)
{
	int					i;
	int					j;

	if (!world || !within(to_replace, -1, world->n_v) || !within(new, -1, \
	world->n_v))
		return ;
	i = 0;
	while (i < world->n_w)
	{
		if (world->walls[i].v1 == to_replace)
			world->walls[i].v1 = new;
		i++;
	}
	i = 0;
	while (i < world->n_s)
	{
		j = 0;
		while (j < world->sec[i].n_w)
		{
			if (world->sec[i].v[j] == to_replace)
				world->sec[i].v[j] = new;
			j++;
		}
		i++;
	}
}

void					replace_wall(int to_replace, int new, t_world *world)
{
	int					i;
	int					j;

	if (!world || !within(to_replace, -1, world->n_w) || !within(new, -1, \
	world->n_w))
		return ;
	i = 0;
	while (i < world->n_s)
	{
		j = 0;
		while (j < world->sec[i].n_w)
		{
			if (world->sec[i].s_walls[j] == to_replace)
				world->sec[i].s_walls[j] = new;
			j++;
		}
		i++;
	}
}
