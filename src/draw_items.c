#include "main_head.h"

void 			check_enemy_state(t_item *enemy, t_vector player_pos)
{
	if (enemy->health > 0)
	{
		enemy->speed = 0.22;
		if (enemy->is_dying)
			enemy->is_dying--;
		else if (enemy->dist_to_player < 30 && enemy->dist_to_player > 5)
		{
			enemy->curr_state = walk;
			enemy->speed = 0.44;
			move_enemy_to_player(enemy, player_pos);
		}
		else if (enemy->dist_to_player <= 5)
			enemy->curr_state = action;
		else
			enemy->curr_state = waiting;
	}
	else if (enemy->curr_state != die)
	{
		enemy->curr_state = die;
		enemy->curr_frame = 0;
	}
}

void 			draw_sector_items(t_item **items, t_player *player, t_draw_data data, SDL_Surface *screen)
{
	t_item 	*tmp;
	t_item	*get_damege;
	float	closer;
	t_item	*it;

	closer = 1000.f;
	it = *items;
	get_damege = NULL;
	while (it)
	{
		if (it->type == enemy)
			check_enemy_state(it, player->pos);
		if ((it->curr_frame += it->speed) >= it->states[it->curr_state].max_textures)
		{
			if (it->curr_state == action)
				player->health -= it->damage;
			if (player->health <= 0 && !player->dead)
				player->dead = 1;
			it->curr_frame = 0;
			if (it->type == enemy && it->curr_state == die)
			{
				tmp = it->next;
				delete_item_by_ptr(items, it);
				it = tmp;
				continue ;
			}
		}
		if (it->dist_to_player <= 1.2f && it->type != object && it->type != enemy & it->type != light)
		{

			if (it->type == gun)
			{
				get_gun_to_player(player, it->gun_type, it->states[waiting].texture[0]);
				tmp = it->next;
				delete_item_by_ptr(items, it);
				it = tmp;
				continue ;
			}
			else if (it->type == health)
			{
				if(player->health < 100)
				{
					player->health += it->health;
					player->health = player->health > 100 ? 100 : player->health;
					tmp = it->next;
					delete_item_by_ptr(items, it);
					it = tmp;
					continue ;
				}
			}
			else if (it->type == ammo)
			{
				if (player->gun[it->gun_type])
				{
					player->gun[it->gun_type]->ammo += it->ammo;
					tmp = it->next;
					delete_item_by_ptr(items, it);
					it = tmp;
					continue ;
				}
			}
			else 
				from_list_to_another_list(items, &player->inventar, it);
		}
		else
		{
			draw_enemy_sprite(it, data, *player, screen);
			if (it->players_hit && closer > it->dist_to_player)
			{
				it->players_hit = 0;
				closer = it->dist_to_player;
				get_damege = it;
			}
		}
		it = it->next;
	}
	if (get_damege && get_damege->type == enemy)
	{
		get_damege->health -= player->current_gun->damage;
		get_damege->curr_state = taking_damage;
		get_damege->is_dying = 4;
	}
}