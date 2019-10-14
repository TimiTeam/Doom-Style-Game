/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sector_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 04:55:13 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/29 04:56:03 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

int				check_sectors(t_sector *sector)
{
	int			i;
	t_sector	*sec;

	sec = sector;
	while (sec)
	{
		i = 0;
		while (i < MAX_PORTALS && sec->portals[i])
		{
			if (!sec->portals[i]->sectors[0] || !sec->portals[i]->sectors[1])
			{
				printf("sector %d, wall %d\n", sec->sector, sec->portals[i]->id);
				return (print_error_message("Error map!",
						"The empty wall must be closed by all side"));
			}
			i++;
		}
		sec = sec->next;
	}
	return (1);
}

void			set_sector_ptr_to_items(t_item *items, t_sector *sector)
{
	t_item		*all;

	all = items;
	while (all)
	{
		all->sector = sector;
		all = all->next;
	}
}

void			sort_walls(t_sector *sec, t_wall **all)
{
	t_wall		*wall;
	t_vector	tmp;
	int			i;
	int			p;
	int			w;

	i = -1;
	p = 0;
	w = 0;
	while (++i < sec->n_walls)
	{
		wall = all[sec->wall[i]->id];
		if (wall->sectors[0]->sector != sec->sector)
		{
			tmp = sec->wall[i]->start;
			sec->wall[i]->start = sec->wall[i]->end;
			sec->wall[i]->end = tmp;
		}
		sec->wall[i]->sectors[0] = wall->sectors[0];
		sec->wall[i]->sectors[1] = wall->sectors[1];
		if (sec->wall[i]->type == empty_wall && p < MAX_PORTALS)
			sec->portals[p++] = sec->wall[i];
		else if (sec->wall[i]->type != empty_wall && w < MAX_PORTALS)
			sec->only_walls[w++] = sec->wall[i];
	}
}

void			mark_all_neighbors(t_sector *sec, t_wall **all)
{
	while (sec)
	{
		sort_walls(sec, all);
		set_sector_ptr_to_items(sec->items, sec);
		sec = sec->next;
	}
}
