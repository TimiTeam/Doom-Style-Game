/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:16:41 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/27 17:16:43 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

t_vec_f					lines_intersect(t_line a, t_line b, unsigned short *i)
{
	t_vec_f				res;
	t_vec				s1;
	t_vec				s2;
	float				s;
	float				t;

	*i = FALSE;
	res = (t_vec_f){ -1.f, -1.f };
	s1 = sub_one_from_two(a.p0, a.p1);
	s2 = sub_one_from_two(b.p0, b.p1);
	s = (-s2.x * s1.y + s1.x * s2.y);
	t = (float)(s2.x * (float)(a.p0.y - b.p0.y) - s2.y *
			(float)(a.p0.x - b.p0.x)) / s;
	s = (float)(-s1.y * (float)(a.p0.x - b.p0.x) + s1.x *
			(float)(a.p0.y - b.p0.y)) / s;
	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		res.x = a.p0.x + (t * s1.x);
		res.y = a.p0.y + (t * s1.y);
		*i = TRUE;
	}
	return (res);
}

float					get_perp_slope(t_vec p1, t_vec p2)
{
	float				slope;

	slope = get_slope(p1, p2);
	if (slope > 10000)
		return (0);
	if (slope == 0)
		return (20000);
	return (-1 / slope);
}

unsigned short			intersects(t_vec p, t_vec l1, t_vec l2)
{
	float				slope;
	float				intercept;

	if ((l2.x == l1.x && p.x == l2.x) || (l2.y == l1.y && p.y == l2.y))
	{
		if (p.x <= get_max(l1.x, l2.x) && p.x >= get_min(l1.x, l2.x) &&
			p.y <= get_max(l1.y, l2.y) && p.y >= get_min(l1.y, l2.y))
			return (TRUE);
	}
	if (l2.x != l1.x && l2.y != l1.y)
	{
		slope = get_slope(l1, l2);
		intercept = l1.y - slope * l1.x;
		if (p.x * slope + intercept == p.y)
		{
			if (p.x <= get_max(l1.x, l2.x) && p.x >= get_min(l1.x, l2.x) &&
				p.y <= get_max(l1.y, l2.y) && p.y >= get_min(l1.y, l2.y))
				return (TRUE);
		}
	}
	return (FALSE);
}

int						find_wall_inter(t_vec p, t_world world)
{
	int					i;

	i = 0;
	while (i < world.n_w)
	{
		if (intersects(p, world.vecs[world.walls[i].v1],
				world.vecs[world.walls[i].v1]))
			return (i);
		i++;
	}
	return (-1);
}

t_vec					*get_point_at_d(t_vec origin, int dist, int slope)
{
	t_vec				*res;

	res = ft_memalloc(sizeof(t_vec) * 2);
	if (!res)
		return (NULL);
	if (!slope)
	{
		res[0] = (t_vec){ origin.x + dist, origin.y };
		res[1] = (t_vec){ origin.x - dist, origin.y };
	}
	else if (slope > 10000)
	{
		res[0] = (t_vec){ origin.x, origin.y + dist };
		res[1] = (t_vec){ origin.x, origin.y - dist };
	}
	else
	{
		res[0] = (t_vec){ origin.x + 1, origin.y + slope };
		res[1] = (t_vec){ origin.x - 1, origin.y - slope };
	}
	return ((t_vec *)res);
}
