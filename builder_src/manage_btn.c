/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_btn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:05:25 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:41:46 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			btn_refresh(t_prog *prog, int state)
{
	int					on;

	if (!prog)
		return (FAIL);
	on = prog->btn_on;
	on = select_it(1, last_select, -1) == WALL_EDIT ? WALL_BTN : on;
	get_btn(state, &prog->modes[prog->m_id]);
	turn_btns_off(prog);
	if (state == SEC_SEARCH)
		prog->btn_on = SEC_BTN;
	else if (state == WALL_SEARCH)
		prog->btn_on = on;
	else if (state == NORMAL)
		prog->btn_on = DRAG_BTN;
	if (within(prog->btn_on, -1, prog->modes[prog->m_id].n_btn))
		prog->modes[prog->m_id].btn[prog->btn_on].vis_lit_on[2] = TRUE;
	select_it(0, last_select, state);
	prog->redraw = 1;
	return (SUCCESS);
}

unsigned short			btn_light(t_vec mouse, t_btn *btn, int n_btn, \
t_prog *prog)
{
	unsigned short		res;
	unsigned short		i;

	if (!btn || !prog)
		return (FAIL);
	i = -1;
	res = FAIL;
	prog->btn_lit = -1;
	while (++i < n_btn)
	{
		if (btn[i].vis_lit_on[0] && mouse_over(btn[i].box, mouse) == TRUE)
		{
			btn[i].vis_lit_on[1] = TRUE;
			prog->btn_lit = i;
			prog->redraw = 1;
			res = SUCCESS;
		}
		else
		{
			if (btn[i].vis_lit_on[1] == TRUE)
				prog->redraw = 1;
			btn[i].vis_lit_on[1] = FALSE;
		}
	}
	return (res);
}

void					turn_btns_off(t_prog *prog)
{
	int					i;

	if (prog->modes && prog->modes[prog->m_id].btn && \
	prog->modes[prog->m_id].n_btn > 0)
	{
		i = 0;
		while (i < prog->modes[prog->m_id].n_btn)
		{
			prog->modes[prog->m_id].btn[i].vis_lit_on[1] = FALSE;
			prog->modes[prog->m_id].btn[i].vis_lit_on[2] = FALSE;
			i++;
		}
	}
	prog->btn_on = -1;
}

void					turn_btn_on(t_prog *prog, t_grid *grid)
{
	if (!prog || !grid)
		return ;
	if (within(prog->btn_on, -1, prog->modes[prog->m_id].n_btn) == TRUE)
		prog->modes[prog->m_id].btn[prog->btn_on].vis_lit_on[2] = FALSE;
	prog->btn_on = prog->btn_lit;
	if (!(prog->m_id == mode_editor &&
	select_it(1, st_select, -1) == SEC_EDIT &&
	within(prog->btn_on, F_UP_BTN - 1, C_DOWN_BTN + 1)))
		prog->click = (t_vec){ 0, 0 };
	prog->modes[prog->m_id].btn[prog->btn_on].vis_lit_on[2] = TRUE;
	vec_set(grid->p, -1, -1, 2);
	prog->redraw = 1;
}

unsigned short			manage_btn(t_media *media, t_prog *prog, t_grid *grid, \
t_vec mouse)
{
	int					state;

	state = select_it(1, st_select, -1);
	if (prog->m_id == mode_editor &&
	select_it(1, last_select, -1) != state)
		return (btn_refresh(prog, state));
	if (prog->btn_lit != -1 && (prog->click.x || prog->click.y))
		return (btn_press(prog, grid, media, state));
	if (btn_light(mouse, prog->modes[prog->m_id].btn, \
	prog->modes[prog->m_id].n_btn, prog) == SUCCESS)
	{
		prog->redraw = 1;
		if (prog->m_id == mode_editor || prog->m_id == mode_settings)
			return (SUCCESS);
	}
	return (3);
}
