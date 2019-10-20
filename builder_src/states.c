/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:10:10 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:40:45 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					normal_st(t_prog *prog, t_vec mouse, t_grid *grid, \
																t_world *world)
{
	if (!prog || select_it(1, st_select, -1) != NORMAL)
		return ;
	select_it(0, w_select, -1);
	lit_it(0, w_select, -1);
	select_it(0, s_select, -1);
	lit_it(0, s_select, -1);
	if (prog->btn_on == DRAW_BTN)
	{
		drawing(world, prog, grid, mouse);
		upd_sec(world->sec, world->walls, world->vecs, world->n_s);
	}
	else if (prog->btn_on == DISTORT_BTN)
	{
		move_vector(prog, mouse, grid, world);
		upd_sec(world->sec, world->walls, world->vecs, world->n_s);
	}
	else if (prog->btn_on == PLR_BTN)
		move_player(prog, mouse, grid, world);
	else if (prog->btn_on == DRAG_BTN && (prog->click.x || prog->click.y))
		move_grid_drag(prog, mouse, grid);
	else if (prog->btn_on == ISO_BTN && (prog->click.x || prog->click.y))
		move_grid_drag(prog, mouse, grid);
}

void					setup_door(t_world *world)
{
	if (!world || world->n_s < 2)
		return ;
	if (world->sec[world->n_s - 1].type[0] == door &&
	world->sec[world->n_s - 1].n_w == 4)
	{
		if (within(world->sec[world->n_s - 1].s_walls[0], -1, world->n_w))
			world->walls[world->sec[world->n_s - 1].s_walls[0]].type = \
			empty;
		if (within(world->sec[world->n_s - 1].s_walls[2], -1, world->n_w))
			world->walls[world->sec[world->n_s - 1].s_walls[2]].type = \
			empty;
	}
}

void					wall_search_st(t_prog *prog, t_vec node, \
											t_grid *g, t_world *world)
{
	int					v1;
	int					v2;
	int					w;

	if (!prog || !world || !g || !(mouse_over((t_rec){ 0, 0, W_W, W_H }, node)))
		return ;
	w = prog->screen[node.x][node.y].is == screen_wall ? lit_it(0, w_select, \
	prog->screen[node.x][node.y].n) : -1;
	prog->redraw = 1;
	if (!((prog->click.x || prog->click.y) && within(w, -1, world->n_w)))
		return ;
	select_it(0, w_select, w);
	if (prog->btn_on == DOOR_ADD_BTN)
	{
		add_door(world, w, g);
		setup_door(world);
	}
	else
	{
		select_it(0, st_select, WALL_EDIT);
		if (within((v1 = world->walls[w].v1), -1, world->n_v) &&
			within((v2 = world->walls[w].v2), -1, world->n_v))
			zoom_to_box(g, (t_vec[2]){ world->vecs[v1], \
						world->vecs[v2] }, 2);
	}
}

void					sec_search_st(t_prog *prog, t_vec mouse, \
											t_grid *grid, t_world *world)
{
	int					sec;
	t_vec				*p;
	t_vec				*tab;

	if (!prog || !world)
		return ;
	sec = lit_it(0, s_select, mouse_in_stor(mouse, world, grid));
	if ((prog->click.x || prog->click.y) && within(sec, -1, world->n_s))
	{
		select_it(0, s_select, sec);
		select_it(0, st_select, SEC_EDIT);
		p = make_vec_tab(&world->sec[sec], world->vecs, world->n_v);
		if (p)
		{
			tab = make_vec_tab(&world->sec[sec], world->vecs, world->n_v);
			if (tab)
			{
				zoom_to_box(grid, tab, world->sec[sec].n_v);
				free(tab);
			}
			free(p);
		}
	}
	prog->redraw = 1;
}

void					sec_edit_st(t_prog *prog, t_vec mouse, \
												t_grid *grid, t_media *m)
{
	int					sector;

	if (!prog)
		return ;
	sector = select_it(1, s_select, -1);
	prog->redraw = 1;
	if (mouse_in_stor(mouse, &m->worlds[m->w], grid) == sector)
	{
		if (prog->btn_on == -1)
			move_item(prog, mouse, grid, &m->worlds[m->w].sec[sector]);
		else if ((prog->click.x || prog->click.y) && \
		check_for_light(m, prog->btn_on - B_COIN, sector))
			add_item(find_def_item(prog->btn_on - B_COIN, m->it_f, \
			m->n_itf), mouse, grid, &m->worlds[m->w].sec[sector]);
	}
	if (prog->btn_on != -1 && (prog->click.x || prog->click.y) &&
	!(within(prog->btn_on, F_UP_BTN - 1, C_DOWN_BTN + 1)))
	{
		turn_btns_off(prog);
		prog->click = (t_vec){ 0, 0 };
	}
	upd_sec(m->worlds[m->w].sec, m->worlds[m->w].walls,\
	m->worlds[m->w].vecs, m->worlds[m->w].n_s);
	light_sec_types(m->worlds[m->w].sec[sector], prog);
}
