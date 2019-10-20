/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_btn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:10:58 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/15 13:49:06 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			main_menu_btn(t_btn *btn)
{
	t_rec				box;
	int					i;

	if (!btn)
		return (FAIL);
	box.w = W_W / 4;
	box.h = (box.w + 20) * N_MM_BTNS / 3;
	box.x = (W_W - box.w) / 2;
	box.y = (W_H - box.h) / 2 + W_H * 0.1;
	distribute_btn_v(btn, (t_vec){ 0, N_MM_BTNS }, box, 20);
	i = 0;
	while (i < N_MM_BTNS)
	{
		btn[i].reg_i = TXTR_RECG;
		btn[i].lit_i = TXTR_RECG_L;
		i++;
	}
	btn[0].text = ft_strdup("START");
	btn[1].text = ft_strdup("QUIT");
	return (SUCCESS);
}

unsigned short			textures_btn(t_btn *btn, int n_t)
{
	int					i;

	if (!btn || n_t < 1)
		return (FAIL);
	get_txtr_btn_boxes(btn, n_t, 0);
	i = -1;
	while (++i < n_t)
	{
		btn[i].vis_lit_on[0] = TRUE;
		btn[i].reg_i = TXTR_PANEL_GR;
		btn[i].lit_i = TXTR_RECG_L;
	}
	return (SUCCESS);
}

unsigned short			sel_item_btn(t_btn *btn, t_it_f *it_f, int n_itf)
{
	t_rec				button_box;
	int					i;

	if (!btn || !it_f)
		return (FAIL);
	button_box = n_itf > 25 ? (t_rec){ W_W * 0.1, W_H * 0.05, W_W * 0.4,\
	W_H * 0.9 / 25 } : (t_rec){ W_W * 0.3, (W_H - (W_H * 0.9 / 25) * n_itf)\
	/ 2, W_W * 0.4, W_H * 0.9 / 25 };
	i = -1;
	while (++i < n_itf)
	{
		btn[i].vis_lit_on[0] = TRUE;
		btn[i].reg_i = TXTR_RECG;
		btn[i].lit_i = TXTR_RECG_L;
		if (it_f[i].name)
			btn[i].text = ft_strdup(it_f[i].name);
		btn[i].box = button_box;
		button_box.y += button_box.h;
		if (i == 25)
		{
			button_box.x = W_W * 0.5;
			button_box.y = W_H * 0.05;
		}
	}
	return (SUCCESS);
}

t_rec					settings_boxes(int h_b_v_btn, int i)
{
	static t_rec		a = { W_W * 0.1, W_H * 0.3, W_W * 0.4, W_H * 0.6 };
	static t_rec		b = { W_W * 0.5, W_H * 0.3, W_W * 0.4, W_H * 0.6 };
	static t_vec		p[4] = { { W_W * 0.3, W_H * 0.1 }, { W_W * 0.32, W_H * \
	0.05 }, { W_H * 0.05, W_H * 0.05 }, { W_H * 0.025, W_H * 0.025 } };
	t_rec				r;

	r = (t_rec){ b.x + p[1].x, b.y + 56 + p[3].y * (i - 6), p[3].x, p[3].y };
	if (h_b_v_btn == 0)
	{
		r = (t_rec){ a.x, a.y, p[0].x, p[0].y };
		r.x = i == 2 ? b.x : a.x;
		r.y = i == 2 ? b.y : a.y;
		r.y -= i == 0 ? p[0].y * 2 : p[0].y;
	}
	else if (h_b_v_btn == 1)
		r = i == 0 ? a : b;
	else if (h_b_v_btn == 2 && i < 5)
		r = ((t_rec){ a.x + 5, a.y + 56 + p[1].y * i, p[1].x, p[1].y });
	else if (h_b_v_btn == 2 && (i -= 5) >= 0)
		r = (t_rec){ b.x + 5, b.y + 56 + p[1].y * i, p[1].x, p[1].y };
	else if (!i)
		r = (t_rec){ W_W * 0.9, W_H / 9, p[2].x, p[2].y };
	else if (i < 6 && --i >= 0)
		r = (t_rec){ a.x + p[1].x, a.y + 56 + p[2].y * i, p[2].x, p[2].y };
	return (r);
}

unsigned short			settings_btn(t_btn *btn, int n)
{
	int					i;
	static int			reg[10] = { TXTR_BACK, TXTR_EDIT, TXTR_EDIT, TXTR_EDIT,\
	TXTR_EDIT, TXTR_EDIT, TXTR_UP, TXTR_DOWN, TXTR_UP, TXTR_DOWN };
	static int			lit[10] = { TXTR_BACK_L, TXTR_EDIT_L, TXTR_EDIT_L, \
	TXTR_EDIT_L, TXTR_EDIT_L, TXTR_EDIT_L, TXTR_UP_L, TXTR_DOWN_L, TXTR_UP_L, \
	TXTR_DOWN_L };

	if (!btn)
		return (FAIL);
	i = -1;
	while (++i < n)
	{
		btn[i].box = settings_boxes(3, i);
		btn[i].vis_lit_on[0] = TRUE;
		btn[i].reg_i = reg[i];
		btn[i].lit_i = lit[i];
		btn[i].text = NULL;
	}
	return (SUCCESS);
}
