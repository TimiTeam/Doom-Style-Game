/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_edit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:25:30 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:40:53 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			edit_texture(int fl_ceil, int n_t, t_texture *txtr,
		t_world *world)
{
	int					sector;
	int					wall;
	int					texture;
	int					state;

	if (!txtr)
		return (FAIL);
	state = select_it(1, st_select, -1);
	sector = select_it(1, s_select, -1);
	wall = select_it(1, w_select, -1);
	if (within((texture = select_it(1, t_select, -1)), -1, n_t))
	{
		if (state == SEC_EDIT && within(sector, -1, world->n_s))
		{
			if (fl_ceil == 0)
				world->sec[sector].fl_t = texture;
			else
				world->sec[sector].ceil_t = texture;
		}
		else if (state == WALL_EDIT && within(wall, -1, world->n_w))
			world->walls[wall].txtr = texture;
	}
	return (SUCCESS);
}

void					prep_texture_edit(t_world *w, t_prog *prog,\
int n_t)
{
	int					t;
	int					fc;
	int					sec;
	int					wall;

	if (!w || !prog)
		return ;
	t = -1;
	if (select_it(1, st_select, 1) == SEC_EDIT && within((sec = \
	select_it(1, s_select, 1)), -1, w->n_s))
	{
		fc = prog->btn_on == FT_EDIT_BTN ? 0 : 1;
		t = !select_it(0, fc_select, fc) ? w->sec[sec].fl_t :\
		w->sec[sec].ceil_t;
	}
	else if (within((wall = select_it(1, w_select, 0)), -1, w->n_w))
		t = w->walls[wall].txtr;
	turn_btns_off(prog);
	prog->btn_lit = -1;
	prog->m_id = mode_textures;
	if (within(t, -1, get_min(n_t, prog->modes[prog->m_id].n_btn)))
	{
		prog->modes[prog->m_id].btn[t].vis_lit_on[2] = TRUE;
		select_it(0, t_select, (prog->btn_on = t));
	}
}
