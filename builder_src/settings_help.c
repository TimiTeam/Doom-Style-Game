/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:32:09 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:40:53 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

int						default_heights(char set_get, char of_what, int value)
{
	static int			t[2] = { 0 };

	if (set_get == 1 && within(of_what, -1, 2))
		return (t[(int)of_what]);
	else if (set_get == 0)
	{
		if (within(of_what, -1, 2))
		{
			t[(int)of_what] = value;
			return (t[(int)of_what]);
		}
		else
		{
			t[0] = 0;
			t[1] = 20;
		}
	}
	return (-1);
}

int						default_texture(char set_get, char of_what, int value)
{
	static int			t[5] = { 0 };

	if (set_get == 1 && within(of_what, -1, 5))
		return (t[(int)of_what]);
	else if (set_get == 0)
	{
		if (within(of_what, -1, 5))
		{
			t[(int)of_what] = value;
			return (t[(int)of_what]);
		}
		else
		{
			t[0] = def_wall_t;
			t[1] = def_floor_t;
			t[2] = def_ceil_t;
			t[3] = def_door_t;
			t[4] = def_tran_t;
		}
	}
	return (-1);
}

unsigned short			edit_def_texture(int n_t, t_texture *txtr)
{
	int					of_what;
	int					texture;

	if (!txtr)
		return (FAIL);
	if (within((texture = select_it(1, t_select, -1)), -1, n_t) &&
		within((of_what = select_it(1, def_t_select, -1)), -1, 5))
		default_texture(0, (char)of_what, texture);
	return (SUCCESS);
}

void					change_def_textures(t_prog *prog, int n_t)
{
	int					t;
	int					of_what;

	if (!prog || !prog->modes)
		return ;
	of_what = prog->btn_on - 1;
	select_it(0, def_t_select, of_what);
	t = default_texture(1, (char)of_what, -1);
	turn_btns_off(prog);
	prog->btn_lit = -1;
	prog->last = mode_settings;
	prog->m_id = mode_textures;
	if (within(t, -1, get_min(n_t, prog->modes[prog->m_id].n_btn)))
	{
		prog->modes[prog->m_id].btn[t].vis_lit_on[2] = TRUE;
		select_it(0, t_select, (prog->btn_on = t));
	}
}

void					change_def_heights(int b)
{
	int					f_shift;
	int					c_shift;
	int					floor;
	int					ceil;

	f_shift = 0;
	c_shift = 0;
	floor = default_heights(1, 0, -1);
	ceil = default_heights(1, 1, -1);
	if (b == S_F_UP_BTN)
		f_shift++;
	else if (b == S_F_DOWN_BTN)
		f_shift--;
	else if (b == S_C_UP_BTN)
		c_shift++;
	else if (b == S_C_DOWN_BTN)
		c_shift--;
	floor += f_shift;
	ceil += c_shift;
	floor = clamp(floor, MIN_HEIGHT, MAX_HEIGHT);
	ceil = clamp(ceil, MIN_HEIGHT, MAX_HEIGHT);
	default_heights(0, 0, floor);
	default_heights(0, 1, ceil);
}
