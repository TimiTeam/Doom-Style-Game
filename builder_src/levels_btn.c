/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_btn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:10:58 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 20:10:59 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					get_lev_btn(t_btn *btn, int i, int n_worlds, \
t_world *worlds)
{
	char				*s;
	char				*tmp;

	s = NULL;
	if (!worlds || !btn)
		return ;
	btn->reg_i = TXTR_RECG;
	btn->lit_i = TXTR_RECG_L;
	btn->text = NULL;
	if (i == n_worlds)
	{
		btn->reg_i = TXTR_ADD_MAP;
		btn->lit_i = TXTR_ADD_MAP_L;
		btn->box.x += (btn->box.w - btn->box.h) / 2;
		btn->box.w = btn->box.h;
	}
	else if ((tmp = ft_itoa(i)))
	{
		if ((s = ft_strjoin(tmp, ". ")))
		{
			btn->text = ft_strjoin(s, worlds[i].name);
			free(s);
		}
		free(tmp);
	}
}

void					get_ed_del_btn(t_btn *btn, t_btn *btn1, t_btn *btnj)
{
	if (btn && btn1 && btnj)
	{
		btn->reg_i = TXTR_EDIT;
		btn->lit_i = TXTR_EDIT_L;
		btn1->reg_i = TXTR_DEL;
		btn1->lit_i = TXTR_DEL_L;
		btn->box = (t_rec){ btnj->box.x + btnj->box.w + 10, btnj->box.y, \
		30, 30 };
		btn1->box = (t_rec){ btnj->box.x + btnj->box.w + 50, \
		btnj->box.y, 30, 30 };
	}
}

unsigned short			levels_btn(t_btn *btn, t_world *worlds, int n_worlds)
{
	t_rec				box;
	int					i;
	int					j;
	int					n_levels;
	int					n_btn;

	if (!btn || !worlds)
		return (FAIL);
	n_levels = n_worlds + 1;
	n_btn = n_levels * 3 - 2;
	box.w = W_W / 4;
	box.h = (box.w + 20) * n_levels / 3;
	box.x = (W_W - box.w) / 2;
	box.y = (W_H - box.h) / 2;
	distribute_btn_v(btn, (t_vec){ 0, n_levels }, box, 20);
	i = -1;
	while (++i < n_levels)
		get_lev_btn(&btn[i], i, n_worlds, worlds);
	j = -1;
	while (i + 1 < n_btn && ++j < n_worlds)
	{
		get_ed_del_btn(&btn[i], &btn[i + 1], &btn[j]);
		i += 2;
	}
	return (SUCCESS);
}
