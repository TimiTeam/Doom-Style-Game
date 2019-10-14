/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:16:31 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:16:31 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

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

void				use_key(t_player *player)
{
	t_item			*all;
	t_item			*tmp;

	all = player->inventar;
	if (all->type == key)
	{
		player->inventar = all->next;
		ft_memdel((void**)&all);
		return ;
	}
	while ((all = all->next))
	{
		if (all->type == key)
		{
			tmp = player->inventar;
			while (tmp)
			{
				if (tmp->next == all)
					DELETE;
				tmp = tmp->next;
			}
		}
	}
}

t_sector			*get_sector_after_door(t_sector *door, t_sector *prev)
{
	int 			i;
	t_wall			*wall;

	if (!door || !prev)
		return (NULL);
	i = 0;
	while (i < MAX_PORTALS && (wall = door->wall[i]))
	{
		if (wall->sectors[1] != door && wall->sectors[1] != prev && wall->sectors[1])
			return (wall->sectors[1]);
		if (wall->sectors[0] != door && wall->sectors[0] != prev && wall->sectors[0])
			return (wall->sectors[0]);
		i++;
	}
	return (NULL);
}


t_sector 			*get_near_sector(t_player *player)
{
	t_sector		*ret;

	ret = NULL;
	if ((ret = get_new_player_sector((t_vector){player->pos.x + player->cos_angl * 2,
			player->pos.y + player->sin_angl * 2, player->pos.z}, player->curr_sector))
				&& ret->state == calm)
					return (ret);
	return (player->curr_sector);
}

void				activate_lift(t_player *player)
{
	t_wall			*wall;
	t_sector		*sect;
	t_sector		*next;
	unsigned		i;

	i = 0;
	next = NULL;
	if(!(sect = get_near_sector(player)) || sect->type != lift || sect->state != calm)
		return ;
	while (sect && i < MAX_PORTALS && (wall = sect->portals[i]))
	{
		if (wall->sectors[0] != sect && (int)wall->sectors[0]->floor != (int)sect->floor)
			next = wall->sectors[0];
		if (wall->sectors[1] != sect && (int)wall->sectors[1]->floor != (int)sect->floor)
			next = wall->sectors[1];
		if (next)
		{
			if (next->type == door)
				next = get_sector_after_door(next, sect);
			if ((int)next->floor != (int)sect->floor)
			{
				sect->max_up = next->floor;
				if ((int)next->floor > (int)sect->floor)
					sect->speed = 0.2f;
				else
					sect->speed = -0.2f;
				sect->state = action_sec;
				return ;
			}
		}
		i++;
	}
}

void				check_door(t_player *player)
{
	int				i;
	t_wall			**walls;
	t_sector		*sec;

	i = -1;
	if (!has_key(player->inventar))
		return ;
	walls = player->curr_sector->portals;
	while (++i < MAX_PORTALS && walls[i])
	{
		if (find_dot_radius_intersect(player->pos, 3,
						walls[i]->start, walls[i]->end))
		{
			sec = player->curr_sector == walls[i]->sectors[0] ?
			walls[i]->sectors[1] : walls[i]->sectors[0];
			if (sec->type == door && sec->state == calm && !sec->door_open)
			{
				use_key(player);
				sec->state = action_sec;
				sec->max_up = sec->floor + 15;
				sec->speed = 0.2f;
			}
			else
				continue ;
			return ;
		}
	}
}
