/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:10:24 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:10:25 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

int				box_intersection(t_vector p1, t_vector p2,
									t_vector p3, t_vector p4)
{
	if ((OVP(p1.x, p2.x, p3.x, p4.x) && OVP(p1.y, p2.y, p3.y, p4.y)))
		return (1);
	return (0);
}

float			side_of_a_point(t_vector p, t_vector s, t_vector end)
{
	return (VXS(end.x - s.x, end.y - s.y, p.x - s.x, p.y - s.y));
}

t_vector		point_of_intersec(t_vector p1, t_vector p2,
									t_vector p3, t_vector p4)
{
	return ((t_vector){
	VXS(VXS(p1.x, p1.y, p2.x, p2.y), p1.x - p2.x,
	VXS(p3.x, p3.x, p4.x, p4.y), p3.x - p4.x)
	/ VXS(p1.x - p2.x, p1.y - p2.y, p3.x - p4.x, p3.y - p4.y),
	VXS(VXS(p1.x, p1.y, p2.x, p2.y), p1.y - p2.y,
	VXS(p3.x, p3.y, p4.x, p4.y), p3.y - p4.y)
	/ VXS(p1.x - p2.x, p1.y - p2.y, p3.x - p4.x, p3.y - p4.y), 0
	});
}

t_scaler		init_scaler(int n, t_point curr, t_point dst)
{
	curr.y += curr.y == curr.x ? 1 : 0;
	return ((t_scaler){dst.x + (n - 1 - curr.x) * (dst.y - dst.x)
	/ ((curr.y - curr.x)), ((dst.y < dst.x) ^ (curr.y < curr.x)) ? -1 : 1,
	abs(dst.y - dst.x), abs(curr.y - curr.x), (int)((n - 1 - curr.x)
	* abs((int)(dst.y - dst.x))) % abs(curr.y - curr.x) });
}

void			quicksort(t_item **head, t_player *player)
{
	if (!head || !*head)
		return ;
	(*head)->dist_to_player = len_between_points((*head)->pos, player->pos);
	(*head) = quick_sort_recur(*head, tail_of(*head), player);
	return ;
}
