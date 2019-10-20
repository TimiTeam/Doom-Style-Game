/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 18:54:43 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/11 13:46:18 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

int						add_start_vec(t_grid *g, t_world *w, int *sector, \
int wall)
{
	int					id;

	id = -1;
	if (!can_place_v(g->p[0], *w, g, wall))
	{
		g->p[0] = (t_vec){ -1, -1 };
		return (-1);
	}
	if (g->nod[g->p[0].x][g->p[0].y] == -1 || (g->nod[g->p[0].x][g->p[0].y] == \
	-2 && (id = find_vec(w->vecs, g->p[0], w->n_v)) == -1))
	{
		if (add_vec(&w->vecs, (id = w->n_v++), g, 0) == FAIL)
			return (-1);
		if (wall != -1)
			break_wall(w, id, wall, -1);
	}
	if (id == -1 || add_sector(&w->sec, (*sector = w->n_s++)) == FAIL)
	{
		g->p[0] = (t_vec){ -1, -1 };
		return (-1);
	}
	if (add_sector_v(&w->sec[*sector].v, w->sec[*sector].n_v++, id) == FAIL)
		return (-1);
	return (id);
}

unsigned				get_walliddone(short *wall_id_done)
{
	wall_id_done[1] = -1;
	wall_id_done[2] = FALSE;
	wall_id_done[0] = -1;
	return (TRUE);
}

unsigned				place_start(int *f_s_l, t_grid *grid, t_world *world, \
int wall)
{
	f_s_l[2] = add_start_vec(grid, world, &f_s_l[1], wall);
	f_s_l[0] = f_s_l[2];
	return (TRUE);
}

void					add_to_media(t_grid *grid, t_world *w, int wall)
{
	static int			f_s_l[3] = { -1, -1, -1 };
	short				wall_id_done[3];

	if (!w || !grid || !get_walliddone(wall_id_done) || (grid->p[1].x != -1\
	&& !(within(f_s_l[1], -1, w->n_s) && f_s_l[0] != -1)) || (grid->p[1].x == -1
	&& place_start(f_s_l, grid, w, wall)))
		return ;
	if (grid->nod[grid->p[1].x][grid->p[1].y] == NODE_FULL)
		wall_id_done[1] = find_vec(w->vecs, grid->p[1], w->n_v);
	if (wall_id_done[1] != f_s_l[0] && !can_place_v(grid->p[1], *w, grid, wall))
	{
		grid->p[1] = (t_vec){ -1, -1 };
		return ;
	}
	if (!(wall_id_done[1] == -1 && grid->nod[grid->p[1].x][grid->p[1].y] == -1))
		existing_vec(wall_id_done, f_s_l, w, grid);
	else
	{
		if (add_vec(&w->vecs, (wall_id_done[1] = w->n_v++), grid, 1) == FAIL)
			return ;
		if (wall != -1)
			break_wall(w, wall_id_done[1], wall, f_s_l[1]);
	}
	if (add_media_elements(w, grid, wall_id_done, f_s_l) == SUCCESS)
		done_condition(grid, f_s_l, wall_id_done[2]);
}

void					drawing(t_world *world, t_prog *prog, t_grid *grid, \
t_vec mouse)
{
	unsigned short		vis;
	int					wall;

	wall = -1;
	if (!world || !prog || !prog->modes || !grid ||
	!mouse_over(grid->box, mouse))
		return ;
	prog->redraw = 1;
	if (!(prog->click.x || prog->click.y))
		return ;
	if (prog->screen[mouse.x][mouse.y].is == screen_wall)
		wall = prog->screen[mouse.x][mouse.y].n;
	if (grid->p[0].x == -1)
		grid->p[0] = find_node(mouse.x, mouse.y, grid);
	else if (grid->p[1].x == -1)
		grid->p[1] = find_node(mouse.x, mouse.y, grid);
	if (grid->p[0].x != -1)
		add_to_media(grid, world, wall);
	vis = grid->p[0].x != -1 ? FALSE : TRUE;
	wall = 0;
	while (wall < prog->modes[prog->m_id].n_btn && wall < TOT_EDIT_BTNS)
		prog->modes[prog->m_id].btn[wall++].vis_lit_on[0] = vis;
	prog->click = (t_vec){ 0, 0 };
}
