/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor_buttons.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:49:29 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/11 16:59:18 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					init_sec_btn(t_mode *m)
{
	static int			reg[TOT_EDIT_BTNS] = { TXTR_BACK, TXTR_DEL, TXTR_UP, \
	TXTR_DOWN, TXTR_UP, TXTR_DOWN, TXTR_EDIT, TXTR_EDIT, TXTR_EDIT, TXTR_DEL, \
	TXTR_COIN, TXTR_KEY, TXTR_OBJECT, TXTR_ENEMY, TXTR_SUPER, TXTR_HEALTH, \
	TXTR_AMMO, TXTR_WEAPON, TXTR_LIGHT, TXTR_NORM, TXTR_DSEC, TXTR_ELEV, \
	TXTR_CEIL, TXTR_SKY, TXTR_FL_SAFE, TXTR_FL_UNSAFE };
	static int			lit[TOT_EDIT_BTNS] = { TXTR_BACK_L, TXTR_DEL_L, \
	TXTR_UP_L, TXTR_DOWN_L, TXTR_UP_L, TXTR_DOWN_L, TXTR_EDIT_L, TXTR_EDIT_L, \
	TXTR_EDIT_L, TXTR_DEL_L, TXTR_COIN, TXTR_KEY, TXTR_OBJECT, TXTR_ENEMY, \
	TXTR_SUPER, TXTR_HEALTH, TXTR_AMMO, TXTR_WEAPON, TXTR_LIGHT, TXTR_NORM_L, \
	TXTR_DSEC_L, TXTR_ELEV_L, TXTR_CEIL_L, TXTR_SKY_L, TXTR_FL_SAFE_L, \
	TXTR_FL_UNSAFE_L };
	int					i;

	if (!m || !m->btn)
		return ;
	i = -1;
	while (++i < TOT_EDIT_BTNS)
	{
		m->btn[i].reg_i = reg[i];
		m->btn[i].lit_i = lit[i];
		m->btn[i].vis_lit_on[0] = TRUE;
	}
	get_sec_boxes(m);
	m->btn[B_ITEM_EDIT].vis_lit_on[0] = FALSE;
	m->btn[B_ITEM_DEL].vis_lit_on[0] = FALSE;
}

void					init_wall_btn(t_mode *m)
{
	static int			reg[TOT_EDIT_BTNS] = { TXTR_BACK, TXTR_EDIT, TXTR_EDIT,\
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	static int			lit[TOT_EDIT_BTNS] = { TXTR_BACK_L, TXTR_EDIT, \
	TXTR_EDIT_L, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
	0, 0 };
	int					i;
	int					n;

	if (!m || !m->btn)
		return ;
	n = 3;
	i = -1;
	while (++i < m->n_btn)
	{
		m->btn[i].reg_i = reg[i];
		m->btn[i].lit_i = lit[i];
		m->btn[i].vis_lit_on[0] = i < n ? TRUE : FALSE;
	}
	m->btn[DESELECT_BTN].box = layout(0, 0);
	m->btn[DESELECT_BTN].box = (t_rec){ m->btn[DESELECT_BTN].box.x +\
	m->btn[DESELECT_BTN].box.w, m->btn[DESELECT_BTN].box.y, 30, 30 };
	m->btn[WT_EDIT_BTN].box = layout(6, 1);
	m->btn[PORT_BTN].box = layout(6, 2);
}

void					init_regular_btn(t_mode *m)
{
	static t_rec		box = { 10, 0, W_H * 0.07 * 11, W_H * 0.07};
	static int			reg[TOT_EDIT_BTNS] = { TXTR_MOVE, TXTR_DISTORT, \
	TXTR_DRAW, TXTR_SEC, TXTR_WALL, TXTR_DOOR_ADD, TXTR_DOOR_DEL, TXTR_PLR, \
	TXTR_ISO, TXTR_SAVE, TXTR_EXIT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
	0 };
	static int			lit[TOT_EDIT_BTNS] = { TXTR_MOVE_L, TXTR_DISTORT_L, \
	TXTR_DRAW_L, TXTR_SEC_L, TXTR_WALL_L, TXTR_DOOR_ADD_L, TXTR_DOOR_DEL_L, \
	TXTR_PLR_L, TXTR_ISO_L, TXTR_SAVE_L, TXTR_EXIT_L, 0, 0, 0, 0, 0, 0, 0, 0,\
	0, 0, 0, 0, 0, 0, 0 };
	int					i;
	int					n;

	if (!m || !m->btn)
		return ;
	distribute_btn_h(m->btn, (t_vec){ 0, (n = 11) }, box, 3);
	i = -1;
	while (++i < m->n_btn)
	{
		m->btn[i].reg_i = reg[i];
		m->btn[i].lit_i = lit[i];
		m->btn[i].vis_lit_on[0] = i < n ? TRUE : FALSE;
	}
}

void					get_btn(int state, t_mode *mode)
{
	if (!mode)
		return ;
	if (state == SEC_EDIT)
		init_sec_btn(mode);
	else if (state == WALL_EDIT)
		init_wall_btn(mode);
	else
		init_regular_btn(mode);
}
