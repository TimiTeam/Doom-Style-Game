/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 06:25:35 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/29 06:29:05 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

t_sector			*new_sector(void)
{
	t_sector		*sec;

	sec = (t_sector*)malloc(sizeof(t_sector));
	ft_memset(sec, 0, sizeof(t_sector));
	return (sec);
}

t_sector			*crate_new_sector(float floor, float ceil)
{
	t_sector		*sec;

	sec = new_sector();
	sec->floor = floor;
	sec->ceil = ceil;
	return (sec);
}

void				add_next_sector(t_sector **main, t_sector *next)
{
	t_sector		*head;
	int				i;

	if (!*main)
	{
		*main = next;
		return ;
	}
	head = *main;
	i = 1;
	while (head->next)
	{
		head = head->next;
		i++;
	}
	next->sector = i;
	head->next = next;
}

void				*delete_walls(t_wall **wall, unsigned size)
{
	unsigned		i;
	t_wall			*ptr;

	if (!wall)
		return (NULL);
	i = 0;
	while (i < size && wall)
	{
		if (wall[i] && (ptr = wall[i]))
		{
			ft_memdel((void**)&ptr);
			wall[i] = NULL;
		}
		i++;
	}
	ft_memdel((void**)&wall);
	return (NULL);
}

void				*delete_sectors(t_sector *sectors)
{
	t_sector		*next;

	if (!sectors)
		return (NULL);
	next = sectors;
	while (sectors)
	{
		next = sectors;
		sectors = next->next;
		if (next->wall)
		{
			delete_walls(next->wall, next->n_walls);
		}
		next->wall = NULL;
		delete_items_list(next->items);
		next->items = NULL;
		delete_projectiles(next->projectiles);
		next->projectiles = NULL;
		ft_memdel((void**)&next);
	}
	return (NULL);
}
