/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_items_loader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 04:56:35 by tbujalo           #+#    #+#             */
/*   Updated: 2019/09/29 05:01:05 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

void				copy_all_t_iteam_states(t_item *dst, t_item *src)
{
	unsigned		i;

	if (!dst || !src)
		return ;
	i = 0;
	while (i < 5)
	{
		dst->states[i] = src->states[i];
		i++;
	}
}

int					copy_t_item_value_by_id(t_item *dst, t_item *all,
		unsigned src_item_id)
{
	int				finde;

	finde = 0;
	if (!dst || !all)
		return (print_error_message("Error source items", ""));
	while (all)
	{
		if (src_item_id == all->id)
		{
			finde = 1;
			copy_all_t_iteam_states(dst, all);
			dst->ammo = all->ammo;
			dst->health = all->health;
			dst->speed = all->speed;
			dst->type = all->type;
			dst->damage = all->damage;
			dst->gun_type = all->gun_type;
			dst->size = all->size;
			dst->speed = 0.4;
			break ;
		}
		all = all->next;
	}
	return (finde);
}

t_item				*create_item(char *data, t_item *all_items)
{
	t_item			*item;
	unsigned		i;
	float			x;
	float			y;
	int				index;

	i = get_numbers(&x, &y, ',', data);
	if (!(item = create_new_item((int)x, (int)y)))
		return (0);
	index = ft_atoi(&data[i]);
	if (!copy_t_item_value_by_id(item, all_items, index))
	{
		index = print_error_message("Use default val 0! Wrong item:", &data[i]);
		copy_t_item_value_by_id(item, all_items, index);
	}
	item->size.x = item->states[0].texture[0]->w;
	item->size.y = item->states[0].texture[0]->h;
	if (item->size.x > 150 && item->size.y > 150)
	{
		item->size.x = item->size.x / 5;
		item->size.y = item->size.y / 5;
	}
	return (item);
}

t_item				*make_items(char *data, t_item *all_items,
		t_read_holder *holder)
{
	t_item			*list;
	t_item			*next;
	enum item_type	type;
	int				i;

	i = 0;
	list = NULL;
	while (data[i] && data[i] != '\'')
		i++;
	while (data[i])
	{
		if (data[i] == '(')
		{
			if ((next = create_item(&data[i], all_items)))
				add_next_item(&list, next);
			if (next && next->type == light)
				holder->light_count++;
		}
		i++;
	}
	return (list);
}
