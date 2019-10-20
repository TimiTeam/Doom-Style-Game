/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 14:37:37 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 14:37:39 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					get_new_vecs(int id, t_world *world)
{
	t_vec				*new;
	int					i;
	int					j;

	i = 0;
	j = 0;
	if (!world || !world->vecs || !within(id, -1, world->n_v))
		return ;
	if (!(new = (t_vec *)ft_memalloc(sizeof(t_vec) * (world->n_v - 1))))
		return ;
	while (j < world->n_v)
	{
		if (j == id)
			j++;
		if (j < world->n_v)
			new[i++] = world->vecs[j++];
	}
	world->n_v--;
	free(world->vecs);
	world->vecs = new;
}

void					delete_vector(int id, t_world *world)
{
	int					i;
	int					j;

	if (!world || !world->vecs || !world->walls || !world->sec ||
	!within(id, -1, world->n_v))
		return ;
	get_new_vecs(id, world);
	i = -1;
	while (++i < world->n_w)
	{
		if (world->walls[i].v1 > id)
			world->walls[i].v1--;
		if (world->walls[i].v2 > id)
			world->walls[i].v2--;
	}
	i = -1;
	while (++i < world->n_s)
	{
		j = -1;
		while (++j < world->sec[i].n_w)
		{
			if (world->sec[i].v[j] > id)
				world->sec[i].v[j]--;
		}
	}
}
