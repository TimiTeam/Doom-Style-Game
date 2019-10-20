/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:16:36 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:16:37 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

unsigned short		dot_inside_sector(t_vector player_pos,
								t_wall **walls, unsigned arr_size)
{
	unsigned		i;
	unsigned char	odd;
	t_wall			*curr;

	i = -1;
	odd = 0;
	while (++i < arr_size && walls && walls[i])
	{
		curr = walls[i];
		if ((curr->start.y < player_pos.y && curr->end.y >= player_pos.y)
			|| (curr->end.y < player_pos.y && curr->start.y >= player_pos.y))
		{
			if (curr->start.x + (float)(player_pos.y - curr->start.y)
			/ (curr->end.y - curr->start.y)
			* (curr->end.x - curr->start.x) < player_pos.x)
				odd = odd == 0 ? 1 : 0;
		}
	}
	return (odd);
}

void				make_intersect(t_wall *wall)
{
	t_vector		i1;
	t_vector		i2;

	i1 = point_of_intersec(wall->start, wall->end,
				(t_vector){-1e-5f, 1e-4f, 0}, (t_vector){-1000.f, 5, 0});
	i2 = point_of_intersec(wall->start, wall->end,
				(t_vector){1e-5f, 1e-4f, 0}, (t_vector){1000.f, 5, 0});
	if (wall->start.y < 1e-4f)
	{
		if (i1.y > 0)
			wall->start = i1;
		else
			wall->start = i2;
	}
	if (wall->end.y < 1e-4f)
	{
		if (i1.y > 0)
			wall->end = i1;
		else
			wall->end = i2;
	}
}
