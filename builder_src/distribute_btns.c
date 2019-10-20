/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute_btns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:10:58 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 20:10:59 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			distribute_btn_h(t_btn *btn, t_vec from_to, t_rec box,\
int padding)
{
	t_vec				b;
	int					x;
	unsigned short		i;

	if (!btn)
		return (FAIL);
	b = (t_vec){ box.w / (from_to.y - from_to.x) - padding, box.h };
	x = box.x;
	i = from_to.x;
	while (i < from_to.y)
	{
		btn[i].box.w = b.x;
		btn[i].box.h = b.y;
		btn[i].box.x = x;
		btn[i].box.y = box.y;
		x += b.x + padding;
		i++;
	}
	return (SUCCESS);
}

unsigned short			distribute_btn_v(t_btn *btn, t_vec from_to, t_rec box,\
int padding)
{
	t_vec				b;
	int					y;
	unsigned short		i;

	if (!btn || from_to.x >= from_to.y)
		return (FAIL);
	b = (t_vec){ box.w, box.h / (from_to.y - from_to.x) - padding };
	y = box.y;
	i = from_to.x;
	while (i < from_to.y)
	{
		btn[i].box.w = b.x;
		btn[i].box.h = b.y;
		btn[i].box.x = box.x;
		btn[i].box.y = y;
		y += b.y + padding;
		i++;
	}
	return (SUCCESS);
}

int						get_good_size(int w, int h, int n)
{
	t_vec_d				tmp;
	t_vec_d				size;
	double				w_h;
	double				h_w;

	if (!w || !h || !n)
		return (0);
	w_h = (double)w / h;
	h_w = (double)h / w;
	tmp = (t_vec_d){ ceil(sqrt(n * w_h)), ceil(sqrt(n * h_w)) };
	size.x = floor(tmp.x * h_w) * tmp.x < n ? h / ceil(tmp.x * h_w) : w / tmp.x;
	if (!tmp.y)
		return (0);
	size.y = floor(tmp.y * w_h) * tmp.y < n ? w / ceil(w * tmp.y / h) : \
	h / tmp.y;
	return (get_max((int)size.x, (int)size.y));
}

unsigned short			distribute_btn_grid(t_btn *btn, t_vec from_to, \
t_rec box)
{
	t_vec				b;
	int					y;
	unsigned short		i;
	int					x;

	if (!btn || from_to.x >= from_to.y)
		return (FAIL);
	b.x = get_good_size(box.w, box.h, from_to.y - from_to.x);
	b.y = b.x;
	y = box.y;
	i = from_to.x;
	while (i < from_to.y)
	{
		x = box.x;
		while (i < from_to.y && x + b.x < box.x + box.w)
		{
			btn[i].box.w = b.x;
			btn[i].box.h = b.y;
			btn[i].box.x = x;
			btn[i++].box.y = y;
			x += b.x;
		}
		y += b.y;
	}
	return (SUCCESS);
}
