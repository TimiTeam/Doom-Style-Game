/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source_worker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 04:23:21 by tbujalo           #+#    #+#             */
/*   Updated: 2019/10/28 16:23:26 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

t_light			*new_t_light(t_vector pos, float max_dist, t_sector *cur_sec)
{
	t_light		*new;

	new = NULL;
	if ((new = (t_light*)malloc(sizeof(t_light))))
	{
		ft_memset(new, 0, sizeof(t_light));
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
	unsigned	i;
	t_wall		*w;

	i = -1;
	while (++i < arr_size && (w = walls[i]))
	{
		if (w->type == filled_wall)
			continue;
		if (find_dot_radius_intersect(light_pos, max_dist, w->start, w->end))
			return (1);
	}
	return (0);
}

int				its_new_light(t_light *new, t_light **array)
{
	int 		i;

	i = 0;
	while (i < MAX_LIGHT_SRC && array[i])
	{
		if (array[i] == new)
			return (0);
		i++;
	}
	return (1);
}

void			fill_sectors_light_source(t_sector *sec,
		t_light **light, unsigned array_size)
{
	unsigned	i;
	unsigned	j;
	t_light		*l;
	t_sector	*s;

	s = sec;
	if (!sec || !light)
		return ;
	while (s)
	{
		i = 0;
		j = 0;
		while (i < array_size && (l = light[i]) && j < MAX_LIGHT_SRC)
		{
			if (l->sector == s)
			{
				s->sector_light[j] = l;
				j++;
			}
			i++;
		}
		i = 0;
		while (i < array_size && (l = light[i]) && j < MAX_LIGHT_SRC
			&& its_new_light(l, s->sector_light))
		{
			if (light_catch_sector(s->wall, s->n_walls, l->pos, l->max_dist / 2))
			{
				s->sector_light[j] = l;
				j++;
			}
			i++;
		}
		s = s->next;
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
