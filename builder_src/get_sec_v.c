/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sec_v.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:45:37 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 16:45:38 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

int						exists_in_array(int const *array, int n, int number)
{
	int					i;

	i = 0;
	while (i < n)
	{
		if (array[i++] == number)
			return (TRUE);
	}
	return (FALSE);
}

void					sort_tmp(int *tmp, int n, t_sec *sec)
{
	int					i;
	int					j;

	if (!tmp)
		return ;
	pair_sort(tmp, n);
	sec->status = !sector_closed(tmp, n) ? SEC_OPEN : SEC_CONCAVE_CLOSED;
	i = -1;
	j = 0;
	while (++i < n)
	{
		if (exists_in_array(tmp, j, tmp[i]) == FALSE)
			tmp[j++] = tmp[i];
	}
	if (!(sec->v = (int *)ft_memalloc(sizeof(int) * j)))
		return ;
	ft_memset(sec->v, -1, sizeof(int) * (sec->n_v = j));
	i = 0;
	while (i < sec->n_v)
	{
		sec->v[i] = tmp[i];
		i++;
	}
}

int						fill_sector_v(t_sec *sec, t_wall *walls, int n, int i)
{
	int					j;
	int					tmp[n];

	if (!sec || !walls || !sec->s_walls)
		return (FAIL);
	ft_memset(tmp, -1, sizeof(int) * n);
	j = 0;
	while (++i < sec->n_w && j + 1 < n)
	{
		tmp[j++] = walls[sec->s_walls[i]].v1;
		tmp[j++] = walls[sec->s_walls[i]].v2;
	}
	sort_tmp(tmp, n, sec);
	return (SUCCESS);
}

int						get_sec_v(t_sec *sector, t_wall *walls)
{
	if (!sector || !walls)
		return (FAIL);
	return (fill_sector_v(sector, walls, sector->n_w * 2, -1));
}
