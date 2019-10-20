/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:07:04 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/12 21:00:52 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					get_door_points(t_vec *p, t_grid *grid, \
													t_world *world, float slope)
{
	t_vec				*q[2];

	if (fabs(slope) != 1 && p[0].x != p[1].x && p[0].y != p[1].y)
		return ;
	if (!(q[0] = get_point_at_d(p[0], 1, (int)slope)))
		return ;
	get_new_p(q[0], grid, world);
	if (!(q[1] = get_point_at_d(p[1], 1, (int)slope)))
	{
		free(q[0]);
		return ;
	}
	get_new_p(q[1], grid, world);
	if (q[0][0].x > 0 && q[1][0].x > 0 && !will_inter(world, q[0][0], q[1][0]))
	{
		p[2] = q[0][0];
		p[3] = q[1][0];
	}
	if (q[0][1].x > 0 && q[1][1].x > 0 && !will_inter(world, q[0][1], q[1][1]))
	{
		p[2] = q[0][1];
		p[3] = q[1][1];
	}
	free(q[1]);
	free(q[0]);
}

unsigned short			add_dsec(t_sec **sec, short n_s, int wall)
{
	*sec = (t_sec *)realloc_tab(*sec, sizeof(t_sec) * (n_s + 1), \
	sizeof(t_sec) * n_s);
	if (!*sec)
		return (FAIL);
	(*sec)[n_s].s_walls = NULL;
	(*sec)[n_s].items = NULL;
	(*sec)[n_s].fl = default_heights(1, 0, -1);
	(*sec)[n_s].ceil = default_heights(1, 0, -1);
	(*sec)[n_s].fl_t = (short)default_texture(1, def_door_t, -1);
	(*sec)[n_s].ceil_t = (short)default_texture(1, def_door_t, -1);
	(*sec)[n_s].n_w = 4;
	(*sec)[n_s].n_it = 0;
	(*sec)[n_s].n_v = 4;
	(*sec)[n_s].type[0] = door;
	(*sec)[n_s].type[1] = ceiling;
	(*sec)[n_s].type[2] = safe;
	(*sec)[n_s].status = SEC_CONVEX_CLOSED;
	if (!((*sec)[n_s].s_walls = ft_memalloc(sizeof(int) * (*sec)[n_s].n_w)))
		return (FAIL);
	(*sec)[n_s].s_walls[0] = wall;
	return (SUCCESS);
}

void					fill_dsec(t_world *w, int wall, t_grid *g, t_vec p[4])
{
	unsigned short		v[4];

	if (!w || !g || !w->walls || !w->vecs || !w->sec)
		return ;
	g->p[0] = p[2];
	g->p[1] = p[3];
	v[1] = w->walls[wall].v2;
	w->walls[wall].txtr = default_texture(1, def_door_t, -1);
	if (add_vec(&w->vecs, w->n_v, g, 0) || add_vec(&w->vecs, w->n_v + 1, g, 1))
		return ;
	v[2] = w->n_v++;
	v[3] = w->n_v++;
	if (add_wall(&w->walls, w->n_w, v[1], v[3]) == FAIL)
		return ;
	w->sec[w->n_s].s_walls[1] = w->n_w++;
	if (add_wall_door(&w->walls, w->n_w, v[3], v[2]) == FAIL)
		return ;
	w->sec[w->n_s].s_walls[2] = w->n_w++;
	v[0] = w->walls[wall].v1;
	if (add_wall(&w->walls, w->n_w, v[2], v[0]) == FAIL)
		return ;
	w->sec[w->n_s].s_walls[3] = w->n_w++;
	get_sec_v(&w->sec[w->n_s++], w->walls);
	w->walls[w->n_w - 1].txtr = (short)default_texture(1, def_door_t, -1);
	w->walls[w->n_w - 3].txtr = (short)default_texture(1, def_door_t, -1);
}

void					add_door(t_world *w, int wall, t_grid *g)
{
	t_vec				p[4];

	if (!w || !w->walls || !w->vecs || !g || !within(wall, -1, w->n_w) ||
		!within(w->walls[wall].v1, -1, w->n_v) ||
		!within(w->walls[wall].v2, -1, w->n_v))
		return ;
	vec_set(p, -1, -1, 4);
	p[0] = w->vecs[w->walls[wall].v1];
	p[1] = w->vecs[w->walls[wall].v2];
	get_door_points((t_vec *)p, g, w, get_perp_slope(p[0], p[1]));
	if (p[2].x == -1 || p[3].x == -1 || add_dsec(&w->sec, w->n_s, wall) == FAIL)
		return ;
	fill_dsec(w, wall, g, p);
}
