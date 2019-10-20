/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:12:33 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:40:45 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

t_rec					layout(char i, char n)
{
	static t_rec		o = { W_W * 0.6, W_H / 10, W_W * 0.34, W_W * 0.34 };
	static t_rec		l = { W_W * 0.62, W_H * 0.12, W_W * 0.24, W_H * 0.03 };
	static t_rec		v = { W_W * 0.87, W_H * 0.12, W_W * 0.04, W_H * 0.03 };
	int					arrow;

	arrow = i == 3 ? -10 : 10;
	if (i == 0)
		return (o);
	else if (i == 2)
	{
		if (n != 0)
			return ((t_rec){ l.x, l.y + n * (l.h + 20) + 10, l.w, l.h });
		return ((t_rec){ l.x, l.y + n * (l.h + 20), W_W * 0.3, W_H * 0.05 });
	}
	else if (i == 5)
	{
		if (n == 0)
			return ((t_rec){ v.x, (v.y + n * (v.h + 20)), v.w, W_H * 0.05 });
		return ((t_rec){ v.x, (v.y + n * (v.h + 20) + 10), v.w, v.h });
	}
	arrow = i == 6 ? 0 : arrow;
	return ((t_rec){ o.x + o.w * 0.9, (l.y + n * (l.h + 20) + 10) + arrow,\
	l.h * 0.9, l.h * 0.9 });
}

char					*lines(int id, int i, int w_type)
{
	static short		n_s_lines = 6;
	static short		n_w_lines = 4;
	static char			s_lines[6][20] = { "SECTOR ", "Floor height ", \
	"Ceiling height ", "Floor texture ", "Ceiling texture ", "Items" };
	static char			w_lines[3][20] = { "WALL ", "Texture ", "Portal " };

	if (id == SEC_EDIT && within(i, -1, n_s_lines))
		return (s_lines[i]);
	else if (id == WALL_EDIT && within(i, -1, n_w_lines))
	{
		if (i == 2)
		{
			if (w_type == filled)
				return ("FILLED");
			if (w_type == empty)
				return ("EMPTY");
			if (w_type == window)
				return ("WINDOW");
			if (w_type == transparent)
				return ("TRANSPARENT");
		}
		return (w_lines[i]);
	}
	else
		return (NULL);
}

t_value					*get_sec_values(int *n, t_sec *sector)
{
	static int			nb = 6;
	t_value				*new;

	if (!sector)
		return (NULL);
	if (!(new = init_values(nb)))
		return (NULL);
	*n = nb;
	new[1].text = ft_itoa(sector->fl);
	new[2].text = ft_itoa(sector->ceil);
	new[3].t = sector->fl_t;
	new[4].t = sector->ceil_t;
	new[5].text = ft_itoa(sector->n_it);
	new[3].m_p = 0;
	new[4].m_p = 0;
	if (!new[1].text || !new[2].text || !new[5].text)
		return (NULL);
	return (new);
}

t_value					*get_wall_val(int *n, t_wall *wall)
{
	static int			nb = 3;
	t_value				*new;

	if (!wall)
		return (NULL);
	if (!(new = init_values(nb)))
		return (NULL);
	*n = nb;
	new[1].t = wall->txtr;
	new[2].t = -1;
	new[1].m_p = 0;
	new[2].m_p = 1;
	return (new);
}

void					render_edit_menu(t_sdl *sdl, t_media *m, t_prog *p, \
t_world *w)
{
	t_value				*val;
	int					i;
	int					s;

	if (!w || !p || !sdl || !m || !m->txtr || !m->worlds ||
	((s = select_it(1, st_select, 0)) != 1 && s != 5))
		return ;
	val = NULL;
	p->n = 0;
	i = s == SEC_EDIT ? select_it(1, s_select, -1) : select_it(1, w_select, -1);
	if (s == 1 && within(i, -1, w->n_s) && within(w->sec[i].fl_t, -1, m->n_t)
	&& within(w->sec[i].ceil_t, -1, m->n_t))
	{
		if (!(val = get_sec_values(&p->n, &w->sec[i])))
			return ;
	}
	else if (s == 5 && (!within(i, -1, w->n_w) || !within(w->walls[i].txtr, -1,\
	m->n_t) || !(val = get_wall_val(&p->n, &w->walls[i]))))
		return ;
	if (val)
		val[0].text = ft_itoa(i);
	if (within(TXTR_PANEL_GR, -1, N_TXTR) && p->t && p->t[TXTR_PANEL_GR])
		rend_box(layout(0, 0), p->t[TXTR_PANEL_GR], sdl->rend);
	render_values(val, sdl, p, m);
	free_values(val, p->n);
}
