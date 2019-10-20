/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_door_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:51:33 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/12 20:51:33 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					get_new_p(t_vec *new, t_grid *grid, t_world *world)
{
	if (!world || !grid || !new || !within(new[0].x, -1, GRID_SIZE) ||
		!within(new[0].y, -1, GRID_SIZE) || !within(new[1].x, -1, GRID_SIZE) ||
		!within(new[1].y, -1, GRID_SIZE))
		return ;
	if (nod_in_sec(new[0], world) != -1 ||
		grid->nod[new[0].x][new[0].y] != NODE_EMPTY ||
		find_wall_inter(new[0], *world) != -1)
		new[0] = (t_vec){ -1, -1 };
	if (nod_in_sec(new[1], world) != -1 ||
		grid->nod[new[1].x][new[1].y] != NODE_EMPTY ||
		find_wall_inter(new[1], *world) != -1)
		new[1] = (t_vec){ -1, -1 };
}

unsigned short			will_inter(t_world *world, t_vec one, t_vec two)
{
	unsigned short		i;
	int					j;
	t_vec				v1;
	t_vec				v2;

	i = FALSE;
	j = -1;
	if (!world || !world->walls || !world->vecs)
		return (i);
	while (++j < world->n_w && i == FALSE)
	{
		if (within(world->walls[j].v1, -1, world->n_v) &&
			within(world->walls[j].v2, -1, world->n_v))
		{
			v1 = world->vecs[world->walls[j].v1];
			v2 = world->vecs[world->walls[j].v2];
			lines_intersect((t_line){ one, two }, (t_line){ v1, v2 }, &i);
		}
	}
	return (i);
}
