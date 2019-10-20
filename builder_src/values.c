/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:08:58 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:40:37 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					render_values(t_value *v, t_sdl *sdl, t_prog *p, \
t_media *m)
{
	int					i;
	t_rec				b;
	int					st;

	if (!v || !sdl || !p || !p->t || !m || !m->txtr)
		return ;
	i = -1;
	p->n = clamp(p->n, 0, 255);
	st = select_it(1, st_select, 0);
	while (++i < p->n)
	{
		if (!i && within(TXTR_RECG_L, -1, N_TXTR) && p->t[TXTR_RECG_L])
			rend_box((layout(2, (char)i)), p->t[TXTR_RECG_L], sdl->rend);
		else if (within(TXTR_RECG, -1, N_TXTR) && p->t[TXTR_RECG])
			rend_box((layout(2, (char)i)), p->t[TXTR_RECG], sdl->rend);
		write_txt(lines(st, i, select_it(1, w_select, 0) >= 0 ?\
		m->worlds[m->w].walls[select_it(1, w_select, 0)].type : 0), sdl, \
		(t_txtb){ layout(2, (char)i), 0, ED_CLR });
		write_txt(v[i].text, sdl, (t_txtb){ (b = layout(5, i)), 0, ED_CLR });
		b.w = b.h;
		if (!v[i].m_p && within(v[i].t, -1, m->n_t) && m->txtr[v[i].t].sdl_t)
			rend_box(b, m->txtr[v[i].t].sdl_t, sdl->rend);
		else if (v[i].m_p && within(v[i].t, -1, N_TXTR) && p->t[v[i].t])
			rend_box(b, p->t[v[i].t], sdl->rend);
	}
}

t_value					*init_values(int n)
{
	t_value				*new;
	int					i;

	new = ft_memalloc(sizeof(t_value) * n);
	if (!new)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new[i].text = NULL;
		new[i].t = -1;
		new[i].m_p = 0;
		i++;
	}
	return (new);
}

void					free_values(t_value *values, int n)
{
	int					i;

	i = 0;
	if (!values)
		return ;
	while (i < n)
	{
		if (values[i].text)
		{
			free(values[i].text);
			values[i].text = NULL;
		}
		i++;
	}
	free(values);
	values = NULL;
}
