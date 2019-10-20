/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:31:59 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 20:32:00 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					done_condition(t_grid *grid, int *tab, short done)
{
	if (done == TRUE)
	{
		vec_set(grid->p, -1, -1, 2);
		tab[2] = -1;
		tab[1] = -1;
		tab[0] = -1;
	}
}

void					existing_vec(short *wall_id_done, int *f_s_l, \
t_world *world, t_grid *grid)
{
	if (wall_id_done[1] == f_s_l[0])
		wall_id_done[2] = TRUE;
	else if (wall_id_done[1] == -1 || already_in_sector(wall_id_done[1], \
	world->sec[f_s_l[1]].v, world->sec[f_s_l[1]].n_v))
	{
		grid->p[1] = (t_vec){ -1, -1 };
		return ;
	}
	else if (grid->nod[world->vecs[f_s_l[2]].x][world->vecs[f_s_l[2]].y] == \
	NODE_FULL && grid->nod[world->vecs[wall_id_done[1]].x][world->vecs[\
	wall_id_done[1]].y] == NODE_FULL)
		wall_id_done[0] = find_wall(f_s_l[2], wall_id_done[1], world->walls, \
		world->n_w);
}

unsigned short			add_media_elements(t_world *world, t_grid *grid, \
short *wall_id_done, int *f_s_l)
{
	if (wall_id_done[0] == -1 && add_wall(&world->walls, \
	(wall_id_done[0] = world->n_w++), f_s_l[2], wall_id_done[1]) == FAIL)
		return (FAIL);
	if (add_secwall(&world->sec[f_s_l[1]].s_walls, world->sec[f_s_l[1]].n_w++, \
	wall_id_done[0]) == FAIL ||
		add_sector_v(&world->sec[f_s_l[1]].v, world->sec[f_s_l[1]].n_v++, \
		wall_id_done[1]) == FAIL)
		return (FAIL);
	grid->p[0] = grid->p[1];
	grid->p[1] = (t_vec){ -1, -1 };
	f_s_l[2] = wall_id_done[1];
	return (SUCCESS);
}
