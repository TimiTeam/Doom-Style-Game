/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 19:31:29 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 19:31:31 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			init_walls(char *line, t_world *world)
{
	if (!world)
		return (FAIL);
	if (!(world->n_w = get_n(line, MIN_N_WALLS, MAX_N_WALLS)))
		world->walls = NULL;
	else
	{
		if (!(world->walls = (t_wall *)malloc(sizeof(t_wall) * world->n_w)))
			return (FAIL);
		ft_bzero(world->walls, sizeof(t_wall) * world->n_w);
	}
	return (SUCCESS);
}

unsigned short			init_sec(char *line, t_world *world)
{
	if (!world)
		return (FAIL);
	if (!(world->n_s = get_n(line, MIN_N_SECS, MAX_N_SECS)))
		world->sec = NULL;
	else
	{
		if (!(world->sec = (t_sec *)malloc(sizeof(t_sec) * world->n_s)))
			return (FAIL);
		ft_bzero(world->sec, sizeof(t_sec) * world->n_s);
	}
	return (SUCCESS);
}

unsigned short			init_vec(char *line, t_world *world)
{
	if (!world)
		return (FAIL);
	world->n_v = get_n(line, 0, MAX_VERTEX_ID);
	if (world->n_v == 0)
		world->vecs = NULL;
	else
	{
		if (!(world->vecs = (t_vec *)malloc(sizeof(t_vec) * world->n_v)))
			return (FAIL);
		ft_bzero(world->vecs, sizeof(t_vec) * world->n_v);
	}
	return (SUCCESS);
}
