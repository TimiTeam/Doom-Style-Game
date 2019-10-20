/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:18:24 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 16:18:25 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					fill_grid(int n_v, t_vec *vecs, t_grid *grid)
{
	int					i;

	if (!vecs || !grid || n_v < 1)
		return ;
	i = 0;
	while (i < n_v)
	{
		if (ingrid(vecs[i]))
			grid->nod[vecs[i].x][vecs[i].y] = NODE_FULL;
		i++;
	}
}

void					fill_grid_items(t_sec *sector, t_grid *grid)
{
	int					i;
	t_vec				p;

	if (!grid || !sector || !sector->items)
		return ;
	i = 0;
	while (i < sector->n_it)
	{
		p = sector->items[i].p;
		if (within(p.x, -1, GRID_SIZE) && within(p.y, -1, GRID_SIZE) &&
		(grid->nod[p.x][p.y] == NODE_EMPTY || grid->nod[p.x][p.y] == \
		(signed char)(-10 - i)))
			grid->nod[p.x][p.y] = (signed char)(-10 - i);
		else
			delete_item(sector, i--);
		i++;
	}
}
