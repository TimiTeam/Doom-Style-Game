/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enemy_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:54:20 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/29 17:54:39 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void			check_enemy_state(t_item *enemy, t_vector player_pos)
{
	if (enemy->health > 0)
	{
		enemy->speed = 0.2;
		if (enemy->is_dying)
			enemy->is_dying--;
		else if (enemy->dist_to_player < 40 && enemy->dist_to_player > 3)
		{
			enemy->curr_state = walk;
			enemy->speed = 0.3;
			move_enemy_to_player(enemy, player_pos);
		}
		else if (enemy->dist_to_player <= 4 || enemy->curr_state == taking_damage)
			enemy->curr_state = action;
		else
			enemy->curr_state = waiting;
	}
	else if (enemy->curr_state != die)
	{
		enemy->curr_state = die;
		enemy->curr_frame = 0;
		Mix_PlayChannel(-1, enemy->roar_sound, 0);
	}
}

t_item			*del_cur_item_and_get_next(t_item **it_list, t_item *curr)
{
	t_item		*tmp;

	tmp = NULL;
	if (curr)
	{
		tmp = curr->next;
		delete_item_by_ptr(it_list, curr);
	}
	return (tmp);
}

t_item			*change_item_animations(t_item **items,
t_player *player, t_item *it)
{
	if (!it)
		return (it);
	if (it->type == enemy)
		check_enemy_state(it, player->pos);
	if (it->curr_state == action && it->curr_frame == 0)
		Mix_PlayChannel(-1, it->hit_sound, 0);
	if ((it->curr_frame += it->speed) >=
	it->states[it->curr_state].max_textures)
	{
		if (it->curr_state == action && it->sector->floor + 10 >= player->pos.z)
		{
			player->health -= it->damage;
			Mix_PlayChannel(-1, player->damage_sound, 0);
		}
		it->curr_frame = 0;
		if (it->type == enemy && it->curr_state == die)
			return (del_cur_item_and_get_next(items, it));
	}
	return (it);
}
