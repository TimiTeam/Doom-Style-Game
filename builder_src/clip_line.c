/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:38:22 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/07 13:38:24 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

int						get_code(t_vec v)
{
	int					code;

	code = REG_IN;
	if (v.x < 0)
		code = (code | REG_LEFT);
	else if (v.x > W_W)
		code = (code | REG_RIGHT);
	if (v.y < 0)
		code = (code | REG_BOTTOM);
	else if (v.y > W_H)
		code = (code | REG_TOP);
	return (code);
}

void					get_line_codes(t_line *l, int *code0, int *code1)
{
	if (l && code0 && code1)
	{
		*code0 = get_code(l->p0);
		*code1 = get_code(l->p1);
	}
}

int						get_code_tmp(t_vec *lp, t_vec_d v)
{
	int					code;

	*lp = (t_vec){ (int)v.x, (int)v.y };
	code = get_code(*lp);
	return (code);
}

void					get_v(int out, t_vec_d *v, t_line *l)
{
	t_vec_d				diff;

	if (!l || !v)
		return ;
	diff = (t_vec_d){ l->p1.x - l->p0.x, l->p1.y - l->p0.y };
	if (out & REG_TOP)
		*v = (t_vec_d){ l->p0.x + diff.x * (W_H - l->p0.y) / diff.y, W_H };
	else if (out & REG_BOTTOM)
		v->x = l->p0.x + diff.x * (-l->p0.y) / (l->p1.y - l->p0.y);
	else if (out & REG_RIGHT)
		*v = (t_vec_d){ W_W, l->p0.y + diff.y * (W_W - l->p0.x) / diff.x };
	else if (out & REG_LEFT)
		v->y = l->p0.y + diff.y * (-l->p0.x) / diff.x;
}

int						clip_line(t_line *l)
{
	t_vec_d				v;
	int					code[2];
	int					out;

	get_line_codes(l, &code[0], &code[1]);
	while (1)
	{
		if ((code[0] == REG_IN && code[1] == REG_IN) || code[0] & code[1])
			return (code[0] == REG_IN ? TRUE : FALSE);
		v = (t_vec_d){ 0, 0 };
		out = code[0] != 0 ? code[0] : code[1];
		get_v(out, &v, l);
		if (out == code[0])
			code[0] = get_code_tmp(&l->p0, v);
		else
			code[1] = get_code_tmp(&l->p1, v);
	}
}
