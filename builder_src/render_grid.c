/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:10:32 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:40:45 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					render_grid_nod(t_scr **screen, t_grid *g)
{
	int					x;
	int					y;
	t_vec				n;
	int					radius;
	t_scr				s;

	radius = g->box.w * 0.001;
	y = -1;
	while (++y < GRID_SIZE)
	{
		n.y = (int)(g->box.y + (y * g->scl));
		x = -1;
		while (++x < GRID_SIZE)
		{
			if (!within((n.x = (int)(g->box.x + (x * g->scl))), -1, W_W) ||
			!within(n.y, -1, W_H))
				continue ;
			s = (t_scr){ FULL_COLOR, screen_node, 0 };
			if (g->nod[x][y] == NODE_SEC)
				s.color = SEC_NOD_COLOR;
			else if (g->nod[x][y] != NODE_FULL)
				s.color = EMPTY_COLOR;
			draw_node(n, radius, s, screen);
		}
	}
}

void					draw_walls(t_world world, t_grid *grid, \
t_scr **screen, int wall)
{
	int					i;
	t_vec				v1;
	t_vec				v2;
	t_scr				s;
	int					r;

	i = 0;
	r = (int)(0.2f * grid->scl);
	while (i < world.n_w)
	{
		v1 = transform_to_screen(world.vecs[world.walls[i].v1], grid);
		v2 = transform_to_screen(world.vecs[world.walls[i].v2], grid);
		s = (t_scr){ FULL_W_CLR, screen_wall, i };
		if (i == wall)
			s.color = LIT_WALL_CLR;
		else if (world.walls[i].type == empty)
			s.color = EMPTY_W_CLR;
		else if (world.walls[i].type == window)
			s.color = WINDOW_W_CLR;
		else if (world.walls[i].type == transparent)
			s.color = TRANSPARENT_W_CLR;
		thick_l((t_line){ v1, v2 }, s, r, screen);
		i++;
	}
}

unsigned short			fill_sector(t_world world, t_grid *grid, \
t_scr **screen, int sec)
{
	int					i;
	int					color;
	int					st;
	t_vec				p[MAX_SEC_WALLS];

	st = select_it(1, st_select, -1);
	if (world.sec[sec].n_v < 3 || world.sec[sec].n_v >= MAX_SEC_WALLS)
		return (FALSE);
	i = -1;
	while (++i < world.sec[sec].n_v)
		p[i] = transform_to_screen(world.vecs[world.sec[sec].v[i]], grid);
	color = world.sec[sec].status == SEC_CONVEX_CLOSED ? CONVEX_COLOR : \
	CONCAVE_COLOR;
	if ((st == SEC_SEARCH || st == SEC_EDIT) && sec == lit_it(1, s_select, 0))
		color = ACTIVE_SEC_COLOR;
	if (world.sec[sec].type[0] == door)
		color = DOOR_COLOR;
	else if (world.sec[sec].type[0] == elevator)
		color = ELEV_COLOR;
	return (fill_polygon(p, world.sec[sec].n_v, screen, color));
}

void					drawing_nodes(t_grid *grid, t_scr **screen, \
t_vec mouse)
{
	int					radius;
	t_vec				node;
	t_vec				node2;
	t_scr				s;

	if (!grid || !screen)
		return ;
	radius = grid->box.w * 0.001;
	s = (t_scr){ BABY_PINK, screen_empty, 0 };
	if (grid->p[0].x != -1 && grid->p[0].y != -1)
	{
		node = transform_to_screen(grid->p[0], grid);
		draw_node(node, radius, s, screen);
		if (grid->p[1].x != -1 && grid->p[1].y != -1)
		{
			node2 = transform_to_screen(grid->p[1], grid);
			draw_node(node2, radius, s, screen);
			draw_line2((t_line){ node, node2 }, s, screen);
		}
		else
			draw_line2((t_line){ node, mouse }, s, screen);
	}
}

void					render_grid(t_world world, t_grid *grid, t_prog *prog,\
t_vec mouse)
{
	int					radius;
	int					wall;
	int					k;
	unsigned short		overlay;

	if (!grid || !prog)
		return ;
	grid->box.w = GRID_SIZE * grid->scl;
	grid->box.h = GRID_SIZE * grid->scl;
	clean_screen(prog->screen);
	radius = grid->box.w * 0.001;
	if ((wall = select_it(1, w_select, -1)) == -1)
		wall = lit_it(1, w_select, -1);
	draw_walls(world, grid, prog->screen, wall);
	render_grid_nod(prog->screen, grid);
	place_player(world, grid, prog->screen, radius);
	if (select_it(1, st_select, -1) == NORMAL && prog->btn_on == DRAW_BTN)
		drawing_nodes(grid, prog->screen, mouse);
	k = -1;
	overlay = FALSE;
	while (++k < world.n_s)
	{
		if (world.sec[k].status != SEC_OPEN)
			overlay = fill_sector(world, grid, prog->screen, k) ? 1 : overlay;
	}
}
