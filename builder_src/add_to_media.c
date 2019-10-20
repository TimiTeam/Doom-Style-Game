/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_media.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:13:17 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 20:13:19 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			add_vec(t_vec **vecs, short n_v, t_grid *grid,
		short i)
{
	if (!grid)
		return (FAIL);
	*vecs = (t_vec *)realloc_tab(*vecs, sizeof(t_vec) * (n_v + 1), \
	sizeof(t_vec) * n_v);
	if (!*vecs)
		return (FAIL);
	(*vecs)[n_v] = grid->p[i];
	grid->nod[grid->p[i].x][grid->p[i].y] = NODE_FULL;
	return (SUCCESS);
}

unsigned short			add_wall_door(t_wall **walls, short n_w, int one, \
int two)
{
	*walls = (t_wall *)realloc_tab(*walls, sizeof(t_wall) * (n_w + 1), \
	sizeof(t_wall) * n_w);
	if (!*walls)
		return (FAIL);
	(*walls)[n_w].type = filled;
	(*walls)[n_w].txtr = default_texture(1, def_door_t, -1);
	(*walls)[n_w].v1 = one;
	(*walls)[n_w].v2 = two;
	return (SUCCESS);
}

unsigned short			add_wall(t_wall **walls, short n_w, int one, int two)
{
	*walls = (t_wall *)realloc_tab(*walls, sizeof(t_wall) * (n_w + 1), \
	sizeof(t_wall) * n_w);
	if (!*walls)
		return (FAIL);
	(*walls)[n_w].type = filled;
	(*walls)[n_w].txtr = default_texture(1, def_wall_t, -1);
	(*walls)[n_w].v1 = one;
	(*walls)[n_w].v2 = two;
	return (SUCCESS);
}

unsigned short			add_world(t_world **worlds, short n_worlds, char *ext,
		char *path)
{
	static int			i = 0;

	*worlds = (t_world *)realloc_tab(*worlds, sizeof(t_world) * (n_worlds + 1),
			sizeof(t_world) * n_worlds);
	if (!*worlds || !path || !ext)
		return (FAIL);
	(*worlds)[n_worlds].name = get_name(i);
	(*worlds)[n_worlds].full_p = get_full_p((*worlds)[n_worlds].name,
			ext, path);
	if (!(*worlds)[n_worlds].name || !(*worlds)[n_worlds].full_p)
		return (FAIL);
	(*worlds)[n_worlds].sec = NULL;
	(*worlds)[n_worlds].n_s = 0;
	(*worlds)[n_worlds].walls = NULL;
	(*worlds)[n_worlds].n_w = 0;
	(*worlds)[n_worlds].vecs = NULL;
	(*worlds)[n_worlds].n_v = 0;
	(*worlds)[n_worlds].p_start = (t_vec){ 1, 1 };
	(*worlds)[n_worlds].p_end = (t_vec){ 1, 3 };
	i++;
	return (SUCCESS);
}
