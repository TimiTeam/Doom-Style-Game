/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 21:05:21 by tbujalo           #+#    #+#             */
/*   Updated: 2019/10/15 21:05:23 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

int					has_key(t_item *items)
{
	t_item			*all;

	all = items;
	while (all)
	{
		if (all->type == key)
			return (1);
		all = all->next;
	}
	return (0);
}

void				get_gun_to_player(t_player *player,
						enum e_gun_type gun_type, SDL_Surface *icon)
{
	t_gun			*src;

	src = player->all_guns[gun_type];
	if (!player->gun[gun_type])
	{
		player->gun[gun_type] = src;
		player->current_gun = player->gun[gun_type];
		player->current_gun->icon = icon;
		player->gun[gun_type]->ammo = 15;
	}
	else
		player->gun[gun_type]->ammo += 10;
}

t_sector			*get_new_player_sector(t_vector player_pos,
										t_sector *intersect_sector)
{
	unsigned char	i;
	t_wall			*w;

	if (!intersect_sector)
		return (NULL);
	i = 0;
	while (i < MAX_PORTALS && (w = intersect_sector->portals[i]))
	{
		if (w->sectors[0] && dot_inside_sector(player_pos, w->sectors[0]->wall,
														w->sectors[0]->n_walls))
			return (w->sectors[0]);
		if (w->sectors[1] && dot_inside_sector(player_pos, w->sectors[1]->wall,
														w->sectors[1]->n_walls))
			return (w->sectors[1]);
		i++;
	}
	return (NULL);
}

t_sector			*get_near_sector(t_player *player)
{
	t_sector		*ret;

	ret = NULL;
	if ((ret = get_new_player_sector((t_vector)
	{player->pos.x + player->cos_angl * 2, player->pos.y +
	player->sin_angl * 2, player->pos.z}, player->curr_sector))
	&& ret->state == calm)
		return (ret);
	return (player->curr_sector);
}

t_sector			*get_sector_after_door(t_sector *door, t_sector *prev)
{
	int				i;
	t_wall			*wall;

	if (!door || !prev)
		return (NULL);
	i = 0;
	while (i < MAX_PORTALS && (wall = door->wall[i]))
	{
		if (wall->sectors[1] != door && wall->sectors[1] != prev &&
			wall->sectors[1])
			return (wall->sectors[1]);
		if (wall->sectors[0] != door && wall->sectors[0] != prev &&
			wall->sectors[0])
			return (wall->sectors[0]);
		i++;
	}
	return (NULL);
}
