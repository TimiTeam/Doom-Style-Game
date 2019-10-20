/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_useless.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:46:13 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 16:46:15 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					delete_double_v(t_world *world)
{
	int					i;
	int					j;

	i = 0;
	while (i < world->n_v)
	{
		j = 0;
		while (j < i)
		{
			if (vec_same(world->vecs[i], world->vecs[j]))
			{
				replace_vector(i, j, world);
				delete_vector(i, world);
				i--;
				break ;
			}
			j++;
		}
		i++;
	}
}

void					delete_unused_v(t_world *world)
{
	int					i;
	int					j;
	unsigned short		used;

	i = 0;
	while (i < world->n_v)
	{
		j = 0;
		used = FALSE;
		while (j < world->n_w)
		{
			if (world->walls[j].v1 == i || world->walls[j].v2 == i)
			{
				used = TRUE;
				break ;
			}
			j++;
		}
		if (used == FALSE)
			delete_vector(i, world);
		else
			i++;
	}
}

void					delete_unused_walls(t_world *world)
{
	int					i;
	int					j;
	int					k;
	unsigned short		used;

	i = 0;
	while (i < world->n_w)
	{
		j = -1;
		used = FALSE;
		while (++j < world->n_s && used == FALSE)
		{
			k = -1;
			while (++k < world->sec[j].n_w && used == FALSE)
			{
				if (world->sec[j].s_walls[k] == i)
					used = TRUE;
			}
		}
		if (used == FALSE)
			delete_wall(i, world);
		else
			i++;
	}
}

void					delete_double_walls(t_world *world)
{
	int					i;
	int					j;

	i = 0;
	while (i < world->n_w)
	{
		j = 0;
		while (j < i)
		{
			if ((world->walls[i].v1 == world->walls[j].v2 &&
			world->walls[i].v2 == world->walls[j].v1) ||
				(world->walls[i].v1 == world->walls[j].v1 &&
				world->walls[i].v2 == world->walls[j].v2))
			{
				replace_wall(i, j, world);
				delete_wall(i, world);
				i--;
				break ;
			}
			j++;
		}
		i++;
	}
}
