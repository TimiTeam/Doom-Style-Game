/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 15:21:48 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/23 15:21:50 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					free_sector(t_sec *sector)
{
	if (!sector)
		return ;
	if (sector->s_walls)
		free(sector->s_walls);
	sector->s_walls = NULL;
	if (sector->v)
		free(sector->v);
	sector->v = NULL;
	if (sector->items)
		free(sector->items);
	sector->items = NULL;
}

void					copy_sec_values(t_sec *new, t_sec *old)
{
	if (new && old)
	{
		new->fl = old->fl;
		new->ceil = old->ceil;
		new->fl_t = old->fl_t;
		new->ceil_t = old->ceil_t;
		new->n_it = old->n_it;
		new->n_w = old->n_w;
		new->n_v = old->n_v;
		new->status = old->status;
		new->type[0] = old->type[0];
		new->type[1] = old->type[1];
		new->type[2] = old->type[2];
	}
}

void					copy_sector(t_sec *new, t_sec *old)
{
	int					i;

	if (!old || !new || !(new->s_walls = ft_memalloc(sizeof(int) * old->n_w)))
		return ;
	if (!(new->v = ft_memalloc(sizeof(int) * old->n_v)))
		return ;
	if (!(new->items = ft_memalloc(sizeof(t_item) * old->n_it)))
		return ;
	i = -1;
	while (new->s_walls && ++i < old->n_w)
		new->s_walls[i] = old->s_walls[i];
	i = -1;
	while (new->v && ++i < old->n_v)
		new->v[i] = old->v[i];
	i = -1;
	while (new->items && ++i < old->n_it)
		new->items[i] = old->items[i];
	copy_sec_values(new, old);
	free_sector(old);
}

void					delete_sector(int id, t_world *world)
{
	t_sec				*new;
	int					i;
	int					j;

	if (!world || !world->sec || id < 0 || id >= world->n_s || !(new = \
	(t_sec *)ft_memalloc(sizeof(t_sec) * (world->n_s - 1))))
		return ;
	i = 0;
	j = 0;
	while (j < world->n_s)
	{
		if (j == id)
			free_sector(&world->sec[j++]);
		if (j < world->n_s)
			copy_sector(&new[i++], &world->sec[j++]);
	}
	free(world->sec);
	world->sec = new;
	world->n_s--;
}
