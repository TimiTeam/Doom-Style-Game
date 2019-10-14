/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:09:06 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:09:07 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

int				move_enemy(t_item *en, t_vector step)
{
	t_wall		**wall;
	int			i;
	t_sector	*next;

	wall = en->sector->wall;
	i = -1;
	next = NULL;
	while (++i < en->sector->n_walls)
	{
		if (box_intersection(en->pos, step, wall[i]->start, wall[i]->end)
		&& side_of_a_point(step, wall[i]->start, wall[i]->end) < 0)
		{
			if (wall[i]->type != empty_wall)
				return (0);
			if (wall[i]->sectors[0] && en->sector != wall[i]->sectors[0])
				next = wall[i]->sectors[0];
			else if (wall[i]->sectors[1] && en->sector != wall[i]->sectors[1])
				next = wall[i]->sectors[1];
			if (en->pos.z + 7 > next->ceil - en->sector->floor)
				return (0);
			from_list_to_another_list(&en->sector->items, &next->items, en);
			en->sector = next;
			break ;
		}
	}
	return (1);
}

void			move_enemy_to_player(t_item *enemy, t_vector player_pos)
{
	t_vector	step;
	t_vector	new_pos;
	float		dist;
	float		dx;

	if (!enemy)
		return ;
	step = (t_vector){enemy->pos.x - player_pos.x, enemy->pos.y - player_pos.y, 0};
	dist = enemy->dist_to_player;
	dx = (dist - enemy->speed) / dist;
	new_pos.x = step.x * dx + player_pos.x;
	new_pos.y = step.y * dx + player_pos.y;
	if (move_enemy(enemy, new_pos))
	{
		enemy->pos.x = new_pos.x;
		enemy->pos.y = new_pos.y;
	}
}
