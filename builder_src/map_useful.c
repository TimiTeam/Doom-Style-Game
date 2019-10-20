/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_useful.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:09:24 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 20:09:26 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			already_in_sector(int id, int *vecs, int n_v)
{
	int					i;

	if (!vecs)
		return (FALSE);
	i = 0;
	while (i < n_v)
	{
		if (vecs[i++] == id)
			return (TRUE);
	}
	return (FALSE);
}

unsigned short			can_place_v(t_vec v, t_world world, t_grid *grid, \
int wall)
{
	if (!within(v.x, -1, GRID_SIZE) || !within(v.y, -1, GRID_SIZE))
		return (FALSE);
	if (grid->nod[v.x][v.y] != NODE_FULL && nod_in_sec(v, &world) != -1
		&& wall == -1)
		return (FALSE);
	return (TRUE);
}

unsigned short			mouse_over(t_rec box, t_vec mouse)
{
	if (mouse.x <= box.x || mouse.x >= box.x + box.w)
		return (FALSE);
	if (mouse.y <= box.y || mouse.y >= box.y + box.h)
		return (FALSE);
	return (TRUE);
}

void					highlight_sec_nod(t_vec *p, int n_w, t_grid *grid)
{
	int					i;

	i = -1;
	if (!p && !grid)
		return ;
	while (++i < n_w)
	{
		if (ingrid(p[i]))
			grid->nod[p[i].x][p[i].y] = NODE_SEC;
	}
}

float					get_scl_to_sector(int size, int max_w, int max_h)
{
	float				scl;
	int					box;

	box = get_min(max_w, max_h);
	scl = (float)box / size;
	return (scl);
}
