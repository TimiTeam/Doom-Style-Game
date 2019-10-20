/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:11:32 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 20:11:33 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

int						find_def_item(int type, t_it_f *it_f, int n)
{
	int					i;

	i = 0;
	if (!it_f)
		return (-1);
	while (i < n)
	{
		if (it_f[i].type == type)
			return (i);
		i++;
	}
	return (-1);
}

void					add_item(int default_id, t_vec mouse, t_grid *grid, \
t_sec *sector)
{
	t_vec				node;
	int					i;
	t_item				*new;

	if (!grid || !sector || sector->n_it >= MAX_SEC_ITEMS || default_id == -1)
		return ;
	node = find_node(mouse.x, mouse.y, grid);
	if (within(node.x, -1, GRID_SIZE) && within(node.y, -1, GRID_SIZE))
	{
		if (grid->nod[node.x][node.y] == NODE_EMPTY && (new = \
		(t_item *)ft_memalloc(sizeof(t_item) * (sector->n_it + 1))))
		{
			i = -1;
			while (++i < sector->n_it)
				new[i] = sector->items[i];
			new[sector->n_it] = (t_item){ node, default_id };
			if (sector->items)
				free(sector->items);
			sector->items = new;
			grid->nod[node.x][node.y] = (signed char)(-10 - sector->n_it);
			sector->n_it++;
		}
	}
}
