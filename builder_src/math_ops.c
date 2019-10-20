/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 17:16:16 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/04 17:16:18 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			within(int value, int min, int max)
{
	if (value <= min)
		return (FALSE);
	if (value >= max)
		return (FALSE);
	return (TRUE);
}

t_vec					sub_one_from_two(t_vec one, t_vec two)
{
	return ((t_vec){ two.x - one.x, two.y - one.y });
}

t_vec					scl(t_vec vec, int scl)
{
	return ((t_vec){ vec.x * scl, vec.y * scl });
}

float					get_slope(t_vec p1, t_vec p2)
{
	if (p2.x == p1.x)
		return (20000);
	if (p2.y == p1.y)
		return (0);
	return ((float)(p2.y - p1.y) / (p2.x - p1.x));
}
