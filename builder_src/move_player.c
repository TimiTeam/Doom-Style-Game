/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 15:13:31 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 15:13:33 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			can_move_pl(t_vec click, t_vec *gp0, int *id)
{
	if (click.x || click.y)
		return (TRUE);
	*gp0 = (t_vec){ -1, -1 };
	*id = -1;
	return (FALSE);
}

unsigned short			can_place(t_vec *p, t_vec mouse, t_grid *grid)
{
	*p = find_node(mouse.x, mouse.y, grid);
	if (grid->nod[p->x][p->y] == NODE_EMPTY)
		return (TRUE);
	return (FALSE);
}

void					edit_player(t_vec *st, t_vec *e, int id, t_vec p)
{
	if (!st || !e)
		return ;
	*st = id == 0 ? p : *st;
	*e = id == 1 ? p : *e;
}

void					move_player(t_prog *prog, t_vec ms, t_grid *gr, \
t_world *w)
{
	static int			id = -1;

	if (!prog || !gr || !w || !can_move_pl(prog->click, &gr->p[0], &id))
		return ;
	if (!mouse_over(gr->box, ms))
		prog->click = (t_vec){ 0, 0 };
	else
	{
		if (gr->p[0].x == -1)
		{
			if (vec_same((gr->p[0] = find_node(ms.x, ms.y, gr)), w->p_start))
				id = 0;
			else if (vec_same(gr->p[0], w->p_end))
				id = 1;
			else
			{
				gr->p[0] = (t_vec){ -1, -1};
				move_grid_drag(prog, ms, gr);
			}
		}
		else if (id >= 0 && can_place(&gr->p[1], ms, gr))
			edit_player(&w->p_start, &w->p_end, id, gr->p[1]);
		prog->click = ms;
		prog->redraw = 1;
	}
}
