/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:53:07 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/07 13:53:08 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					get_len(double *diff, int *long_l, int *i, t_line line)
{
	int					short_l;

	if (!diff || !long_l || !i)
		return ;
	*i = 0;
	short_l = line.p1.y - line.p0.y;
	*long_l = line.p1.x - line.p0.x;
	if (abs(short_l) > abs(*long_l))
	{
		swap_ints(&short_l, long_l);
		*i = 1;
	}
	*diff = short_l == 0 ? *long_l : (double)*long_l / (double)short_l;
}

void					draw_line2(t_line l, t_scr s, t_scr **screen)
{
	int				len;
	int				i_value;
	double			d;
	int				i;

	if (!clip_line(&l))
		return ;
	get_len(&d, &len, &i, l);
	i_value = len < 0 ? -1 : 1;
	if (!screen || d == 0)
		return ;
	if (i)
	{
		i = -i_value;
		while ((i += i_value) != len)
			draw_dot2(l.p0.x + (int)(i / d), l.p0.y + i, s, screen);
		return ;
	}
	i = -i_value;
	while ((i += i_value) != len)
		draw_dot2(l.p0.x + i, l.p0.y + (int)(i / d), s, screen);
}

void					thick_l(t_line l, t_scr s, int r, t_scr **screen)
{
	int				len;
	int				i_value;
	double			d;
	int				i;

	if (!clip_line(&l) || !screen)
		return ;
	get_len(&d, &len, &i, l);
	i_value = len < 0 ? -1 : 1;
	if (d == 0)
		return ;
	if (i)
	{
		i = -i_value;
		while ((i += i_value) != len)
			draw_circle_fill2((t_vec){ l.p0.x + (int)(i / d), l.p0.y + i }, r, \
			s, screen);
		return ;
	}
	i = -i_value;
	while ((i += i_value) != len)
		draw_circle_fill2((t_vec){ l.p0.x + i, l.p0.y + (int)(i / d) }, r, s, \
		screen);
}
