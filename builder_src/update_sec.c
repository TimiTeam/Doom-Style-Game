/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 15:36:57 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 15:36:58 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

char					get_status(int *tmp, int j, t_vec *vecs, t_sec *sec)
{
	char				status;
	int					*w;
	int					i;

	if (!tmp || !vecs || !sec)
		return (SEC_OPEN);
	if (!(w = (int *)ft_memalloc(sizeof(int) * j)))
	{
		free(tmp);
		return (SEC_OPEN);
	}
	i = -1;
	while (++i < j)
		w[i] = tmp[i];
	free(tmp);
	pair_sort(w, j);
	status = SEC_CONVEX_CLOSED;
	if (sector_closed(w, j) == FALSE)
		status = SEC_OPEN;
	else if (sec_is_convex(vecs, sec->v, sec->n_v) == FALSE)
		status = SEC_CONCAVE_CLOSED;
	free(w);
	return (status);
}

char					sector_status(t_sec sector, t_wall *walls, \
t_vec *vecs, int n)
{
	int					i;
	int					j;
	int					*tmp;
	char				status;

	if (!walls || !vecs || !(tmp = (int *)ft_memalloc(sizeof(int) * n)))
		return (SEC_OPEN);
	ft_memset(tmp, -1, sizeof(int) * n);
	i = -1;
	j = 0;
	while (++i < sector.n_w && j + 1 < n)
	{
		tmp[j++] = walls[sector.s_walls[i]].v1;
		tmp[j++] = walls[sector.s_walls[i]].v2;
	}
	i = -1;
	j = 0;
	while (++i < n && j < n)
	{
		if (tmp[i] >= 0)
			tmp[j++] = tmp[i];
	}
	status = get_status(tmp, get_min(j, n), vecs, &sector);
	return (status);
}

void					upd_sec(t_sec *sec, t_wall *walls, t_vec *vecs, \
int n_s)
{
	int					i;

	i = -1;
	if (!sec || !walls || !vecs)
		return ;
	while (++i < n_s)
		sec[i].status = sector_status(sec[i], walls, vecs, sec[i].n_w * 2);
}
