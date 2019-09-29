/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source_worker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 04:23:21 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/29 04:32:09 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

t_light			*new_t_light(t_vector pos, float max_dist, t_sector *cur_sec)
{
	t_light		*new;

	new = NULL;
	if ((new = (t_light*)malloc(sizeof(t_light))))
	{
		*new = (t_light){NULL};
		new->pos = pos;
		new->max_dist = max_dist;
		new->sector = cur_sec;
	}
	return (new);
}

t_light			**create_all_light_source(t_sector *sec, unsigned light_count)
{
	t_light		**light_source;
	t_item		*items;
	t_sector	*sectors;
	unsigned	i;

	sectors = sec;
	if (light_count < 1 || !sectors ||
		!(light_source = (t_light**)malloc(sizeof(t_light*) * light_count)))
		return (NULL);
	i = 0;
	while (sectors)
	{
		items = sectors->items;
		while (items)
		{
			if (items->type == light && i < light_count)
			{
				light_source[i] = new_t_light(items->pos, 8, items->sector);
				i++;
			}
			items = items->next;
		}
		sectors = sectors->next;
	}
	return (light_source);
}

int				light_catch_sector(t_wall **walls, unsigned arr_size,
		t_vector light_pos, float max_dist)
{
	int			i;
	t_wall		*w;

	i = 0;
	while (i < arr_size && (w = walls[i]))
	{
		if (find_dot_radius_intersect(light_pos, max_dist, w->start, w->end))
			return (1);
		i++;
	}
	return (0);
}

void			fill_sectors_light_source(t_sector *sec,
		t_light **light, unsigned array_size)
{
	unsigned	i;
	unsigned	j;
	t_light		*source;
	t_sector	*sectors;

	sectors = sec;
	if (!sec || !light)
		return ;
	while (sectors)
	{
		i = 0;
		j = 0;
		while (i < array_size && (source = light[i]))
		{
			if (j < MAX_LIGHT_SRC && (source->sector == sectors ||
				light_catch_sector(sectors->portals, MAX_PORTALS, source->pos,
					source->max_dist / 2)))
			{
				sectors->sector_light[j] = source;
				j++;
			}
			i++;
		}
		sectors = sectors->next;
	}
}

void			delete_light_source(t_light **light, unsigned array_size)
{
	t_light		*l;
	unsigned	i;

	if (!light || !*light)
		return ;
	i = 0;
	while (i < array_size && (l = light[i]))
	{
		ft_memdel((void**)&l);
		i++;
	}
	ft_memdel((void**)&light);
}
