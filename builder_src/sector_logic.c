/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:10:03 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 20:10:05 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			dot_in_sector(int x, int y, t_vec *p, int n)
{
	int					i;
	int					j;
	unsigned short		odd;

	i = -1;
	j = n - 1;
	odd = FALSE;
	while (++i < n)
	{
		if ((p[i].y < y && p[j].y >= y) || (p[j].y < y && p[i].y >= y))
		{
			if (p[i].x + (float)(y - p[i].y) / (p[j].y - p[i].y) * (p[j].x - \
			p[i].x) < x)
				odd = odd == FALSE ? TRUE : FALSE;
		}
		j = i;
	}
	return (odd);
}

int						nod_in_sec(t_vec grid_p, t_world *w)
{
	int					id;
	t_vec				*v;
	int					i;
	int					j;

	if (!w || !w->sec)
		return (-1);
	set_min1(&id, &i);
	while (++i < w->n_s)
	{
		if (w->sec[i].status == SEC_OPEN)
			continue ;
		if (!(v = ft_memalloc(sizeof(t_vec) * w->sec[i].n_v)))
			return (-1);
		j = -1;
		while (++j < w->sec[i].n_v && within(w->sec[i].v[j], -1, w->n_v))
			v[j] = w->vecs[w->sec[i].v[j]];
		id = dot_in_sector(grid_p.x, grid_p.y, v, w->sec[i].n_v) ? i : id;
		free(v);
		if (j != w->sec[i].n_v)
			return (-1);
	}
	return (id);
}

int						mouse_in_stor(t_vec p, t_world *world, t_grid *grid)
{
	t_vec				map_p;

	if (!world || !grid || mouse_over(grid->box, p) == FALSE)
		return (-1);
	map_p = find_node(p.x, p.y, grid);
	return (nod_in_sec(map_p, world));
}

unsigned short			sec_is_convex(t_vec *vec, int *v, int n)
{
	char				pos_neg[2];
	t_vec_d				d[2];
	int					ijk[3];

	if (n < 4 || !vec || !v)
		return (TRUE);
	set_false(&pos_neg[0], &pos_neg[1]);
	ijk[0] = -1;
	while (++ijk[0] < n)
	{
		if (v[ijk[0]] == -2)
			continue ;
		ijk[1] = ijk[0] + 1;
		d[1].x = vec[v[ijk[0]]].x - vec[v[ijk[1] % n]].x;
		d[1].y = vec[v[ijk[0]]].y - vec[v[(ijk[1]) % n]].y;
		ijk[2] = ijk[1] + 1;
		d[0].x = vec[v[ijk[2] % n]].x - vec[v[ijk[1] % n]].x;
		d[0].y = vec[v[(ijk[2]) % n]].y - vec[v[ijk[1] % n]].y;
		d[0].x = d[0].x * d[1].y - d[0].y * d[1].x;
		pos_neg[0] = d[0].x > 0 ? TRUE : pos_neg[0];
		pos_neg[1] = d[0].x < 0 ? TRUE : pos_neg[1];
		if (pos_neg[0] == TRUE && pos_neg[1] == TRUE)
			return (FALSE);
	}
	return (TRUE);
}
