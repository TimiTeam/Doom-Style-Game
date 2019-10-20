/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_media.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:21:32 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/23 16:21:34 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					validate_textures(t_world *world, int n)
{
	int					i;

	if (!world)
		return ;
	i = 0;
	while (i < world->n_w)
	{
		if (within(world->walls[i].txtr, -1, n) == FALSE)
			world->walls[i].txtr = 0;
		i++;
	}
	i = 0;
	while (i < world->n_s)
	{
		if (within(world->sec[i].fl_t, -1, n) == FALSE)
			world->sec[i].fl_t = 0;
		if (within(world->sec[i].ceil_t, -1, n) == FALSE)
			world->sec[i].ceil_t = 0;
		i++;
	}
}

void					delete_item(t_sec *sector, int id)
{
	t_item				*items;
	int					i;
	int					j;

	if (!sector || !within(id, -1, sector->n_it) || !sector->items)
		return ;
	if (!(items = ft_memalloc(sizeof(t_item) * (sector->n_it - 1))))
		return ;
	i = 0;
	j = 0;
	while (i < sector->n_it)
	{
		if (i == id)
			i++;
		if (j < sector->n_it - 1 && i < sector->n_it)
			items[j++] = sector->items[i++];
	}
	free(sector->items);
	sector->items = items;
	sector->n_it--;
}

void					validate_items(t_world *w, int n)
{
	int					i;
	int					j;
	int					k;

	if (!w || !w->sec)
		return ;
	i = -1;
	while (++i < w->n_s)
	{
		j = -1;
		while (++j < w->sec[i].n_it)
		{
			if (within(w->sec[i].items[j].id, -1, n) == FALSE)
				w->sec[i].items[j].id = 0;
			k = -1;
			while (++k < j)
			{
				if (vec_same(w->sec[i].items[j].p, w->sec[i].items[k].p))
				{
					delete_item(&w->sec[i], j--);
					break ;
				}
			}
		}
	}
}

void					validate_sectors(t_world *world)
{
	int					i;
	int					control;

	if (!world)
		return ;
	upd_sec(world->sec, world->walls, world->vecs, world->n_s);
	delete_double_v(world);
	delete_double_walls(world);
	delete_unused_walls(world);
	delete_unused_v(world);
	i = 0;
	control = -1;
	while (i < world->n_s && ++control < MAX_N_SECS)
	{
		if (world->sec[i].status == SEC_OPEN)
		{
			delete_sector(i, world);
		}
		else
		{
			validate_clockwise(world, i);
			i++;
		}
	}
}

void					validate_media(t_media *media)
{
	int					i;

	if (!media)
		return ;
	i = 0;
	while (i < media->n_worlds)
	{
		validate_textures(&media->worlds[i], media->n_t);
		validate_items(&media->worlds[i], media->n_itf);
		validate_sectors(&media->worlds[i]);
		i++;
	}
}
