/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:16:49 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:16:50 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

int					hit_enemy(t_projectile *curr,
						t_item *curr_enemy, Uint8 *is_hit)
{
	if (curr_enemy->type == enemy
		&& len_between_points(curr->pos, curr_enemy->pos) <= 2
		&& curr_enemy->curr_state != die
		&& curr->pos.z > curr_enemy->pos.z + curr_enemy->sector->floor
		&& curr->pos.z < curr_enemy->pos.z
		+ curr_enemy->size.x + curr_enemy->sector->floor)
	{
		curr_enemy->health -= curr->damage;
		*is_hit = 1;
		curr_enemy->players_hit = 1;
		return (1);
	}
	return (0);
}

void				draw_projectiles(t_projectile **projectiles, t_p_n_d p,
										SDL_Surface *screen, t_item *items)
{
	t_projectile	*tmp;
	t_projectile	*curr;
	t_item			*curr_enemy;
	Uint8			is_hit;

	curr_enemy = items;
	curr = *projectiles;
	while (curr)
	{
		is_hit = 0;
		draw_projectile(curr, p.data, p.player, screen);
		while (curr_enemy)
		{
			if (hit_enemy(curr, curr_enemy, &is_hit))
				break ;
			curr_enemy = curr_enemy->next;
		}
		if (is_hit || !move_projectile(curr)
			|| curr->pos.z < curr->curr_sector->floor - 2
			|| curr->pos.z > curr->curr_sector->ceil + 2)
			CON;
		curr = curr->next;
	}
}
