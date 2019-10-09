/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:55:55 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/30 15:31:58 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void			move_player_vertically(t_player *player)
{
	if (player->pos.z + player->velocity >= player->curr_sector->ceil)
		player->velocity = 0;
	player->pos.z += player->velocity;
	if (player->pos.z - player->height > player->curr_sector->floor)
		player->velocity -= 0.1;
	else
		player->velocity = 0;
}

int				change_player(t_sector *new, t_player *player,
								t_vector *step, t_sector *next)
{
	if (!new || (int)(new->ceil - player->curr_sector->floor) <=
					(int)(player->height + player->sit))
		return (0);
	if (next->floor - player->pos.z + player->height > 3)
		return (0);
	if (player->pos.z - player->height < next->floor)
		step->z += next->floor - player->pos.z + player->height;
	player->curr_sector = new;
	return (1);
}

int				check_next_sec(t_wall *wall, t_player *player, t_sector **next)
{
	if (wall->type != empty_wall)
		return (0);
	if (wall->sectors[0] && player->curr_sector != wall->sectors[0])
		*next = wall->sectors[0];
	else if (wall->sectors[1] && player->curr_sector != wall->sectors[1])
		*next = wall->sectors[1];
	if (!*next || (int)((*next)->ceil - (*next)->floor) <=
								(int)(player->height + player->sit))
		return (0);
	return (1);
}

int				player_in_new_sector(t_player *player,
		t_wall *wall, t_vector *step)
{
	t_sector	*next;
	t_sector	*new;

	if (!check_next_sec(wall, player, &next))
		return (0);
	new = get_new_player_sector(*step, next);
	if (!change_player(new, player, step, next))
		return (0);
	return (1);
}

void			move_player(t_player *player, float sin_angle, float cos_angle)
{
	int			i;
	t_vector	step;
	t_wall		**wall;

	i = -1;
	step = (t_vector){player->pos.x + cos_angle * player->speed,
					player->pos.y + sin_angle * player->speed, player->pos.z};
	wall = player->curr_sector->wall;
	while (++i < player->curr_sector->n_walls)
	{
		if (box_intersection(player->pos, step, wall[i]->start, wall[i]->end)
		&& side_of_a_point(step, wall[i]->start, wall[i]->end) < 0)
		{
			if (!player_in_new_sector(player, wall[i], &step))
				return ;
			break ;
		}
	}
	player->pos = step;
	if (player->end_sec == player->curr_sector->sector
	&& len_between_points(player->pos, player->end_pos) < 3)
		player->win = 1;
}
