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
		i = -1;
		while (++i < sec->n_walls && sec->wall[i])
		{
			if (sec->wall[i]->type != transparent &&
					sec->wall[i]->type != empty_wall)
				continue ;
			if (!sec->wall[i]->sectors[0] || !sec->wall[i]->sectors[1])
			{
				return (print_error_message("Error map!",
						"The empty wall must be closed by all side"));
			}
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
