/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:09:24 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 20:09:26 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					bounding_box(t_vec *min, t_vec *max, t_vec *p, int n_p)
{
	int					i;

	if (!min || !max)
		return ;
	*min = (t_vec){ 0, 0 };
	*max = (t_vec){ W_W, W_H };
	if (!p)
		return ;
	*min = (t_vec){ W_W, W_H };
	*max = (t_vec){ 0, 0 };
	i = -1;
	while (++i < n_p)
		update_min_max(min, max, p[i]);
	min->x = clamp(min->x, 0, W_W);
	max->x = clamp(max->x, 0, W_W);
	min->y = clamp(min->y, 0, W_H);
	max->y = clamp(max->y, 0, W_H);
}

void					get_min_scl(float *res_min_scl)
{
	static int			min_size = -1;
	static float		min_scl = 1;

	if (min_size == -1)
	{
		if (W_H < W_W)
			min_size = W_H / 2;
		else
			min_size = W_W / 2;
		min_scl = (float)min_size / GRID_SIZE;
	}
	*res_min_scl = min_scl;
}

void					set_false(char *one, char *two)
{
	if (one)
		*one = FALSE;
	if (two)
		*two = FALSE;
}

void					swap_ints(int *one, int *two)
{
	int					swap;

	if (!one || !two)
		return ;
	swap = *one;
	*one = *two;
	*two = swap;
}

void					get_rgb(unsigned char *r, unsigned char *g, \
unsigned char *b, int color)
{
	if (!r || !g || !b)
		return ;
	*r = (unsigned char)((color >> 16) & 0xFF);
	*g = (unsigned char)((color >> 8) & 0xFF);
	*b = (unsigned char)(color & 0xFF);
}
