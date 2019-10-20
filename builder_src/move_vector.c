/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 15:25:45 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 15:25:47 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			can_move_vec(t_vec click, t_vec *gp0, int *id)
{
	if (click.x || click.y)
		return (TRUE);
	*gp0 = (t_vec){ -1, -1 };
	*id = -1;
	return (FALSE);
}

void					placing(t_grid *g, t_vec *to_erase, int id, \
t_world *world)
{
	if (g && to_erase && world && world->vecs &&
		g->nod[g->p[1].x][g->p[1].y] != NODE_FULL)
	{
		if (to_erase->x != -1)
			g->nod[to_erase->x][to_erase->y] = NODE_EMPTY;
		world->vecs[id] = g->p[1];
		g->nod[g->p[1].x][g->p[1].y] = NODE_FULL;
		*to_erase = g->p[1];
	}
}

void					move_vector(t_prog *prog, t_vec ms, t_grid *g,\
t_world *world)
{
	static int			id = -1;
	static t_vec		to_erase = { -1, -1 };

	if (!prog || !g || !world || !can_move_vec(prog->click, &g->p[0], &id) ||
	!mouse_over(g->box, ms))
	{
		prog->click = (t_vec){ 0, 0 };
		return ;
	}
	if (g->p[0].x == -1)
	{
		if (ingrid((g->p[0] = find_node(ms.x, ms.y, g))) &&
		g->nod[g->p[0].x][g->p[0].y] == NODE_FULL)
			id = find_vec(world->vecs, g->p[0], world->n_v);
		if (id == -1)
		{
			g->p[0] = (t_vec){ -1, -1 };
			move_grid_drag(prog, ms, g);
		}
		to_erase = g->p[0];
	}
	else if (id >= 0 && ingrid(g->p[1] = find_node(ms.x, ms.y, g)))
		placing(g, &to_erase, id, world);
	prog->click = ms;
	prog->redraw = 1;
}
