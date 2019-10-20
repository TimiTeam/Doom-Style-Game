/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_boxes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:49:29 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/11 16:59:18 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

t_rec					sec_descr_boxes(int row, int col)
{
	static t_vec		size = { W_W * 0.10, W_H * 0.03 };
	static int			x[3] = { W_W * 0.60, W_W * 0.60 + W_W * 0.11, \
	W_W * 0.60 + W_W * 0.22 };
	static int			y[3] = { W_H * 0.53, W_H * 0.57, W_H * 0.61 };

	return ((t_rec){ x[col % 3], y[row % 3], size.x, size.y });
}

void					get_sec_boxes(t_mode *m)
{
	t_rec				box;

	if (!m || !m->btn)
		return ;
	box = layout(0, 0);
	m->btn[DESELECT_BTN].box = (t_rec){ box.x + box.w, box.y, 30, 30 };
	m->btn[DEL_SEC_BTN].box = m->btn[DESELECT_BTN].box;
	m->btn[DEL_SEC_BTN].box.y += m->btn[DEL_SEC_BTN].box.h;
	m->btn[F_UP_BTN].box = layout(3, 1);
	m->btn[F_DOWN_BTN].box = layout(4, 1);
	m->btn[C_UP_BTN].box = layout(3, 2);
	m->btn[C_DOWN_BTN].box = layout(4, 2);
	m->btn[FT_EDIT_BTN].box = layout(6, 3);
	m->btn[CT_EDIT_BTN].box = layout(6, 4);
	m->btn[B_NORM].box = sec_descr_boxes(0, 0);
	m->btn[B_DSEC].box = sec_descr_boxes(0, 1);
	m->btn[B_ELEV].box = sec_descr_boxes(0, 2);
	m->btn[B_CEIL].box = sec_descr_boxes(1, 0);
	m->btn[B_SKY].box = sec_descr_boxes(1, 1);
	m->btn[B_FL_SAFE].box = sec_descr_boxes(2, 0);
	m->btn[B_FL_UNSAFE].box = sec_descr_boxes(2, 1);
	box = layout(2, 6);
	box.w *= 1.27;
	box.h *= 1.19;
	distribute_btn_h(m->btn, (t_vec){ B_COIN, B_LIGHT + 1 }, box, 8);
}
