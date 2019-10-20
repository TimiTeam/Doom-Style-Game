/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_grid_iso.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 15:56:13 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/15 14:11:14 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

t_vec_d					make_iso(t_vec v, int z)
{
	t_vec_d				res;
	static double		cos_iso = 0;
	static double		sin_iso = 0;

	if (!cos_iso)
	{
		cos_iso = cos(0.523599);
		sin_iso = cos(0.523599);
	}
	res.x = (v.x - v.y) * cos_iso;
	res.y = -z + (v.x + v.y) * sin_iso;
	return (res);
}

unsigned short			fill_sector_iso(t_world world, t_grid *grid, \
t_scr **screen, int sec)
{
	int					i;
	int					j;
	int					color;
	t_vec_d				tmp;
	t_vec				p[MAX_SEC_WALLS];

	i = 0;
	j = sec;
	if (world.sec[j].n_v < 3)
		return (FALSE);
	while (i < world.sec[j].n_v)
	{
		tmp = make_iso(world.vecs[world.sec[j].v[i]], world.sec[j].fl);
		p[i].x = (int)(grid->box.x + tmp.x * grid->scl);
		p[i].y = (int)(grid->box.y + tmp.y * grid->scl);
		i++;
	}
	color = world.sec[j].status == SEC_CONVEX_CLOSED ? \
	CONVEX_COLOR : CONCAVE_COLOR;
	return (fill_polygon(p, world.sec[j].n_v, screen, color));
}

t_vec					t_op(int onex, int oney, t_vec_d two, float three)
{
	int					x;
	int					y;

	x = (int)(onex + two.x * three);
	y = (int)(oney + two.y * three);
	return ((t_vec){ x, y });
}

void					draw_walls_iso(t_world w, t_grid *g, t_scr **s,\
t_sec *sec)
{
	int					i;
	t_vec				v[4];
	int					c;
	int					r;

	i = -1;
	r = (int)(0.1f * g->scl);
	while (++i < sec->n_w)
	{
		v[0] = t_op(g->box.x, g->box.y, \
		make_iso(w.vecs[w.walls[sec->s_walls[i]].v1], sec->fl), g->scl);
		v[1] = t_op(g->box.x, g->box.y, \
		make_iso(w.vecs[w.walls[sec->s_walls[i]].v2], sec->fl), g->scl);
		v[2] = t_op(g->box.x, g->box.y, \
		make_iso(w.vecs[w.walls[sec->s_walls[i]].v1], sec->ceil), g->scl);
		v[3] = t_op(g->box.x, g->box.y, \
		make_iso(w.vecs[w.walls[sec->s_walls[i]].v2], sec->ceil), g->scl);
		c = w.walls[sec->s_walls[i]].type == 0 ? EMPTY_W_CLR : FULL_W_CLR;
		thick_l((t_line){ v[0], v[1] }, (t_scr){ c, screen_wall, i }, r, s);
		thick_l((t_line){ v[2], v[3] }, (t_scr){ c, screen_wall, i }, r, s);
		thick_l((t_line){ v[0], v[2] }, (t_scr){ c, screen_wall, i }, r, s);
		thick_l((t_line){ v[1], v[3] }, (t_scr){ c, screen_wall, i }, r, s);
		thick_l((t_line){ v[0], v[3] }, (t_scr){ GRAY, screen_wall, i }, r, s);
		thick_l((t_line){ v[1], v[2] }, (t_scr){ GRAY, screen_wall, i }, r, s);
	}
}

void					render_grid_iso(t_world world, t_grid *grid, \
t_prog *prog)
{
	t_vec				tab[world.n_s];
	int					k;
	unsigned short		overlay;

	if (!grid || !prog)
		return ;
	clean_screen(prog->screen);
	overlay = FALSE;
	k = -1;
	while (++k < world.n_s)
	{
		tab[k].x = k;
		tab[k].y = world.sec[k].fl;
	}
	k = -1;
	while (++k < world.n_s)
	{
		if (world.sec[tab[k].x].status != SEC_OPEN)
		{
			draw_walls_iso(world, grid, prog->screen, &world.sec[tab[k].x]);
			overlay = fill_sector_iso(world, grid, prog->screen, tab[k].x) \
			== TRUE ? TRUE : overlay;
		}
	}
}
