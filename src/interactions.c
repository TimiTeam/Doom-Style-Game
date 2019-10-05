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
	t_gun			*dst;
	int				i;

	if (gun_type > 3)
		return ;
	src = player->all_guns[gun_type];
	if (player->gun[gun_type] == NULL)
	{
		dst = (t_gun*)malloc(sizeof(t_gun));
		*dst = (t_gun){0};
		i = 0;
		while (i < 10)
		{
			dst->frame[i] = src->frame[i];
			i++;
		}
		dst->damage = src->damage;
		dst->icon = src->icon;
		dst->type = src->type;
		player->current_gun = dst;
		player->gun[gun_type] = dst;
		player->gun[gun_type]->icon = icon;
	}
	player->gun[gun_type]->ammo += src->ammo;
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

void				activate_lift(t_player *player)
{
	t_wall			*wall;
	t_sector		*lift;
	t_sector		*next;
	unsigned		i;

	i = 0;
	next = NULL;
	lift = player->curr_sector;
	while (lift && i < MAX_PORTALS && (wall = lift->portals[i]))
	{
		if (wall->sectors[0] != lift)
			next = wall->sectors[0];
		if (wall->sectors[1] != lift)
			next = wall->sectors[1];
		if (next)
		{
			if (next->type == door)
				next = get_sector_after_door(next, lift);
			if ((int)next->floor != (int)lift->floor)
			{
				if ((int)next->floor > (int)lift->floor)
					lift->speed = 0.2f;
				else
					lift->speed = -0.2f;
				lift->max_up = next->floor;
				lift->state = action_sec;
				return ;
			}
		}
		i++;
	}
}

void				check_door(t_player *player, t_sector *sectors)
{
	int				i;
	t_wall			**walls;
	t_sector		*sec;
	t_sector		*after_door;

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
			if (sec->type == door && sec->state != action_sec)
			{
				use_key(player);
				sec->state = action_sec;
				after_door = get_sector_after_door(sec, player->curr_sector);
				sec->max_up = after_door->floor + 15;
				printf("Door #%d max up %d\n", sec->sector, sec->max_up);
				sec->speed = 0.2f;
			}
			else
				continue ;
			return ;
		}
	}
}
