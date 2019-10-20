/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_levels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:45:27 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:52:15 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					fill_values(t_world *world)
{
	if (!world)
		return ;
	world->sec = NULL;
	world->walls = NULL;
	world->vecs = NULL;
	world->n_s = 0;
	world->n_v = 0;
	world->n_w = 0;
	world->p_start = (t_vec){ 5, 10 };
	world->p_end = (t_vec){ 10, 10 };
}

unsigned				read_levels(t_media *m, t_section *s)
{
	short				i;

	if (!m || !s || !s->tab || !within(s->n_files, 0, MAX_LEVELS) ||
	!(m->worlds = (t_world *)ft_memalloc(sizeof(t_world) * s->n_files)))
		return (FAIL);
	ft_bzero(m->worlds, sizeof(t_world) * (m->n_worlds = s->n_files));
	i = -1;
	while (++i < s->n_files)
	{
		if (!s->tab[i] || !s->names[i])
			return (FAIL);
		ft_bzero(&m->worlds[i], sizeof(t_world));
		m->worlds[i].full_p = ft_strdup(s->tab[i]);
		m->worlds[i].name = ft_strdup(s->names[i]);
		fill_values(&m->worlds[i]);
		if (!m->worlds[i].full_p || !m->worlds[i].name ||
		get_map(&m->worlds[i], i) == FAIL)
		{
			ft_putstr("\x1b[32mMap \x1b[0m");
			ft_putnbr(i);
			ft_putstr("\x1b[32m is not valid.\x1b[0m\n");
			return (FAIL);
		}
	}
	return (SUCCESS);
}
