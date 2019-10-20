/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btn_press_settings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:05:25 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:30:19 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					prep_settings(t_prog *prog, t_grid *grid, \
t_media *media)
{
	if (!prog || !grid || !media)
		return ;
	turn_btns_off(prog);
	prog->btn_lit = -1;
	prog->last = mode_editor;
	prog->m_id = mode_settings;
}

void					settings_mng_btn(t_prog *prog, t_media *media)
{
	if (!prog || !media)
		return ;
	if (within(prog->btn_on, S_F_UP_BTN - 1, S_C_DOWN_BTN + 1))
		change_def_heights(prog->btn_on);
	else if (within(prog->btn_on, S_WT_BTN - 1, S_TT_BTN + 1))
		change_def_textures(prog, media->n_t);
}
