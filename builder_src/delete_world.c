/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 15:18:22 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/23 15:18:30 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					free_world(t_world *world)
{
	int					i;

	if (!world)
		return ;
	if (world->name)
		free(world->name);
	if (world->full_p)
		free(world->full_p);
	if (world->sec)
	{
		i = 0;
		while (i < world->n_s)
			free_sector(&world->sec[i++]);
		free(world->sec);
	}
	if (world->vecs)
		free(world->vecs);
	if (world->walls)
		free(world->walls);
}

void					copy_world(t_world *new, t_world *old)
{
	int					i;

	if (!old || !new || !(new->name = ft_strdup(old->name)) ||
	!(new->full_p = ft_strdup(old->full_p)))
		return ;
	new->sec = ft_memalloc(sizeof(t_sec) * old->n_s);
	new->walls = ft_memalloc(sizeof(t_wall) * old->n_w);
	new->vecs = ft_memalloc(sizeof(t_vec) * old->n_v);
	i = -1;
	while (new->walls && old->walls && ++i < old->n_w)
		new->walls[i] = old->walls[i];
	i = -1;
	while (new->vecs && old->vecs && ++i < old->n_v)
		new->vecs[i] = old->vecs[i];
	i = -1;
	while (new->sec && old->sec && ++i < old->n_s)
		copy_sector(&new->sec[i], &old->sec[i]);
	new->p_start = old->p_start;
	new->p_end = old->p_end;
	new->n_s = old->n_s;
	new->n_v = old->n_v;
	new->n_w = old->n_w;
	free_world(old);
}

void					delete_world(t_media *media, int id)
{
	t_world				*new;
	int					i;
	int					j;

	if (!media || !media->worlds || media->n_worlds < 2 ||
	!within(id, -1, media->n_worlds))
		return ;
	new = (t_world *)ft_memalloc(sizeof(t_world) * (media->n_worlds - 1));
	if (new)
	{
		i = 0;
		j = 0;
		while (j < media->n_worlds)
		{
			if (j == id)
				free_world(&media->worlds[j++]);
			if (j < media->n_worlds)
				copy_world(&new[i++], &media->worlds[j++]);
		}
		free(media->worlds);
		media->worlds = new;
		media->n_worlds--;
	}
}
