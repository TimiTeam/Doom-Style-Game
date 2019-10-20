/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:03:13 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 14:03:14 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			can_i_move(int *id, t_sec *sec, t_grid *g)
{
	if (!id || !sec || !g)
		return (FALSE);
	if (!within(*id, -1, sec->n_it))
	{
		g->p[0] = (t_vec){ -1, -1 };
		*id = -1;
		return (TRUE);
	}
	return (FALSE);
}

void					placing_item(t_grid *g, int id, t_vec *to_erase, \
t_sec *sector)
{
	if (g->nod[g->p[1].x][g->p[1].y] == NODE_EMPTY)
	{
		if (to_erase->x != -1)
			g->nod[to_erase->x][to_erase->y] = NODE_EMPTY;
		sector->items[id].p = g->p[1];
		g->nod[g->p[1].x][g->p[1].y] = (signed char)(-10 - id);
		*to_erase = g->p[1];
	}
}

unsigned short			can_move_item(t_vec click, t_vec *gp0, int *id)
{
	if (click.x || click.y)
		return (TRUE);
	*gp0 = (t_vec){ -1, -1 };
	*id = -1;
	return (FALSE);
}

void					move_item(t_prog *prog, t_vec ms, t_grid *g, \
t_sec *sector)
{
	static int			id = -1;
	static t_vec		to_erase = { -1, -1 };

	if (!prog || !g || !sector || !can_move_item(prog->click, &g->p[0], &id))
		return ;
	if (mouse_over(g->box, ms))
	{
		if (g->p[0].x == -1)
		{
			if (ingrid((g->p[0] = find_node(ms.x, ms.y, g))) &&
				g->nod[g->p[0].x][g->p[0].y] < -9)
				id = (g->nod[g->p[0].x][g->p[0].y] + 10) * (-1);
			if (can_i_move(&id, sector, g))
				move_grid_drag(prog, ms, g);
			select_it(0, i_select, id);
			to_erase = g->p[0];
		}
		else if (id >= 0 && ingrid(g->p[1] = find_node(ms.x, ms.y, g)))
			placing_item(g, id, &to_erase, sector);
		prog->click = ms;
		prog->redraw = 1;
	}
	else
		prog->click = (t_vec){ 0, 0 };
}
