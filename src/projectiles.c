/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:10:55 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:10:56 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

t_projectile		*create_projectile(t_player player)
{
	t_projectile	*projectile;

	if (!(projectile = (t_projectile*)ft_memalloc(sizeof(t_projectile))))
		return (NULL);
//	*projectile = (t_projectile){0};
	ft_memset(projectile, 0, sizeof(t_projectile));
	projectile->pos.x = player.pos.x + 1 * player.cos_angl;
	projectile->pos.y = player.pos.y + 1 * player.sin_angl;
	projectile->pos.z = player.pos.z - player.yaw - 3;
	projectile->anglecos = player.cos_angl;
	projectile->anglesin = player.sin_angl;
	projectile->yaw = player.yaw;
	projectile->curr_sector = player.curr_sector;
	projectile->speed = 3.0f;
	projectile->damage = 20;
	projectile->sprite = load_jpg_png("textures/plasma_raw.png");
	return (projectile);
}

void				add_projectile(t_projectile **head, t_projectile *new)
{
	t_projectile	*m;

	if (!*head)
	{
		*head = new;
		return ;
	}
	m = *head;
	while (m->next)
		m = m->next;
	m->next = new;
}

void				swap_proj_sectors(t_projectile **current_list,
							t_projectile **next_list, t_projectile *elem)
{
	t_projectile	*curr;
	t_projectile	*prev;

	if (*current_list == elem)
	{
		*current_list = elem->next;
		elem->next = NULL;
		add_projectile(next_list, elem);
		return ;
	}
	curr = (*current_list)->next;
	prev = *current_list;
	while (curr)
	{
		if (curr == elem)
		{
			prev->next = elem->next;
			elem->next = NULL;
			add_projectile(next_list, elem);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int					proj_collisions(t_projectile *proj,
							t_wall **wall, t_vector step)
{
	int				i;
	t_sector		*next;

	i = -1;
	next = NULL;
	while (++i < proj->curr_sector->n_walls)
	{
		if (box_intersection(proj->pos, step, wall[i]->start, wall[i]->end)
		&& side_of_a_point(step, wall[i]->start, wall[i]->end) < 0)
		{
			if (wall[i]->type != empty_wall)
				return (0);
			if (wall[i]->sectors[0]
				&& proj->curr_sector->sector != wall[i]->sectors[0]->sector)
				next = wall[i]->sectors[0];
			else if (wall[i]->sectors[1]
					&& proj->curr_sector->sector != wall[i]->sectors[1]->sector)
				next = wall[i]->sectors[1];
			swap_proj_sectors(&proj->curr_sector->projectiles,
									&next->projectiles, proj);
			proj->curr_sector = next;
			break ;
		}
	}
	return (1);
}

Uint8				move_projectile(t_projectile *proj)
{
	t_wall			**wall;
	t_vector		step;

	if (!proj)
		return (0);
	step = (t_vector){proj->pos.x + proj->speed * proj->anglecos,
						proj->pos.y + proj->speed * proj->anglesin,
						proj->pos.z - proj->yaw * proj->speed};
	wall = proj->curr_sector->wall;
	if (!proj_collisions(proj, wall, step))
		return (0);
	proj->pos = step;
	return (1);
}
