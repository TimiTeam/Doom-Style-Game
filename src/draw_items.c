/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:47:30 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/29 17:54:06 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

static t_item	*get_item_to_player(t_item **items,
t_item *curr, t_player *player)
{
	Mix_Volume(2, 64);
	Mix_PlayChannel(2, player->get_item, 0);
	if (curr->type == jetpack)
		player->jetpack = 1;
	if (curr->type == gun)
	{
		get_gun_to_player(player, curr->gun_type,
		curr->states[waiting].texture[0]);
		return (del_cur_item_and_get_next(items, curr));
	}
	else if (curr->type == health && player->health < 100)
	{
		player->health += curr->health;
		player->health = player->health > 100 ? 100 : player->health;
		return (del_cur_item_and_get_next(items, curr));
	}
	else if (curr->type == ammo && player->gun[curr->gun_type])
	{
		player->gun[curr->gun_type]->ammo += curr->ammo;
		return (del_cur_item_and_get_next(items, curr));
	}
	else if (curr->type != ammo && curr->type != health)
		from_list_to_another_list(items, &player->inventar, curr);
	return (curr);
}

static void		is_player_hit(t_item *get_damege, t_player *player)
{
	if (get_damege && get_damege->type == enemy)
	{
		get_damege->health -= player->current_gun->damage;
		get_damege->curr_state = taking_damage;
		get_damege->is_dying = 4;
	}
}

static t_item	*change_enemy(t_item *enemy, float *prev_dist)
{
	enemy->players_hit = 0;
	*prev_dist = enemy->dist_to_player;
	return (enemy);
}

void			draw_sector_items(t_item **items, t_player *player,
		t_draw_data data, SDL_Surface *screen)
{
	t_item		*get_damege;
	float		closer;
	t_item		*it;

	closer = 1000.f;
	it = *items;
	get_damege = NULL;
	while ((it = change_item_animations(items, player, it)))
	{
		if (player->curr_sector == it->sector &&
			it->dist_to_player <= 1.2f && it->type != object
		&& it->type != enemy && it->type != light)
			it = get_item_to_player(items, it, player);
		if (it && it->dist_to_player >= 1.f)
		{
			draw_enemy_sprite(it, data, *player, screen);
			if (it->players_hit && closer > it->dist_to_player)
				get_damege = change_enemy(it, &closer);
		}
		if (it)
			it = it->next;
	}
	is_player_hit(get_damege, player);
}
