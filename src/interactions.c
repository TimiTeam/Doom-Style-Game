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

static void			use_key(t_player *player)
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

static int			set_lift_max_up(t_sector *s_lift, t_sector *next)
{
	s_lift->max_up = next->floor;
	if ((int)next->floor > (int)s_lift->floor)
		s_lift->speed = 0.2f;
	else
		s_lift->speed = -0.2f;
	s_lift->state = action_sec;
	return (1);
}

void				activate_lift(t_player *player)
{
	t_wall			*w;
	t_sector		*s;
	t_sector		*next;
	unsigned		i;

	i = 0;
	next = NULL;
	if (!(s = get_near_sector(player)) || s->type != lift || s->state != calm)
		return ;
	while (s && i < MAX_PORTALS && (w = s->portals[i]))
	{
		if (w->sectors[0] != s && (int)w->sectors[0]->floor != (int)s->floor)
			next = w->sectors[0];
		if (w->sectors[1] != s && (int)w->sectors[1]->floor != (int)s->floor)
			next = w->sectors[1];
		if (next)
		{
			if (next->type == door)
				next = get_sector_after_door(next, s);
			if ((int)next->floor != (int)s->floor && set_lift_max_up(s, next))
				return ;
		}
		i++;
	}
}

static void			open_door(t_player *player, t_sector *sec)
{
	if (player && sec)
	{
		use_key(player);
		sec->state = action_sec;
		sec->max_up = sec->floor + 15;
		sec->speed = 0.2f;
		Mix_PlayChannel(-1, player->door_sound, 0);
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
				open_door(player, sec);
			else
				continue ;
			return ;
		}
	}
}
