/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 13:08:56 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 13:08:58 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					draw_item(int type, t_rec box, SDL_Renderer *rend, \
SDL_Texture **t)
{
	int					txtr;

	if (!rend || !t)
		return ;
	txtr = type + TXTR_COIN;
	if (within(type, -1, TOTAL_TYPES) && within(txtr, -1, N_TXTR) && t[txtr])
	{
		if (type == KEY || type == HEALTH)
		{
			box.x += box.w * 0.2;
			box.w *= 0.8;
		}
		rend_box(box, t[txtr], rend);
	}
}

unsigned short			ingrid(t_vec p)
{
	if (within(p.x, -1, GRID_SIZE) && within(p.y, -1, GRID_SIZE))
		return (TRUE);
	return (FALSE);
}

t_vec					get_p(t_grid *g, t_vec items_p)
{
	t_vec				p;

	p.x = (int)(g->box.x + (items_p.x * g->scl));
	p.y = (int)(g->box.y + (items_p.y * g->scl));
	return (p);
}

t_rec					get_it_box(t_rec b, t_vec p)
{
	t_rec				b1;

	b1 = (t_rec){ p.x - b.w / 2, p.y - b.h / 2, b.w, b.h };
	return (b1);
}

void					draw_itms(SDL_Renderer *r, t_media *m, t_grid *g, \
SDL_Texture **t)
{
	int					s_i_id[3];
	t_vec				p;
	t_rec				b;

	if (!m || !m->worlds || !m->it_f || !g)
		return ;
	s_i_id[0] = -1;
	while (++s_i_id[0] < m->worlds[m->w].n_s)
	{
		b = (t_rec){ 0, 0, g->box.w * 0.009, g->box.w * 0.009 };
		s_i_id[1] = -1;
		while (++s_i_id[1] < m->worlds[m->w].sec[s_i_id[0]].n_it)
		{
			if (ingrid((p = m->worlds[m->w].sec[s_i_id[0]].items[s_i_id[1]].p))
			&& nod_in_sec(p, &m->worlds[m->w]) == s_i_id[0] && g->nod[p.x][p.y]\
			== (signed char)(-10 - s_i_id[1]) && within((s_i_id[2] = \
			m->worlds[m->w].sec[s_i_id[0]].items[s_i_id[1]].id), -1, m->n_itf))
			{
				p = get_p(g, m->worlds[m->w].sec[s_i_id[0]].items[s_i_id[1]].p);
				draw_item(m->it_f[s_i_id[2]].type, get_it_box(b, p), r, t);
			}
			else
				delete_item(&m->worlds[m->w].sec[s_i_id[0]], s_i_id[1]--);
		}
	}
}
