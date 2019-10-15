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
			dst->speed = 0.3;
			break ;
		}
		all = all->next;
	}
	return (finde);
}

t_item				*create_item(char *data, t_item *all_items)
{
	t_item			*item;
	int				i;
	int				index;

	if (!data || !*data || !(item = create_new_item(0, 0)))
		return (0);
	if (!(i = get_numbers(&item->pos.x, &item->pos.y, ',', data)))
	{
		ft_memdel((void**)&item);
		return (print_error_message_null("Failed to read item", data));
	}
	index = ft_atoi(&data[i]);
	if (!copy_t_item_value_by_id(item, all_items, index))
	{
		ft_memdel((void**)&item);
		return (print_error_message_null("Failed to create item", &data[i]));
	}
	if (!item->size.x && !item->size.y)
	{
		item->size.x = 50;
		item->size.y = 50;
	}
	return (item);
}

t_item				*make_items(char *data, t_item *all_items,
		t_read_holder *holder)
{
	t_item				*list;
	t_item				*next;

	list = NULL;
	while (*data && *data != '\'')
		data++;
	while (*data)
	{
		if (*data == '(')
		{
			if ((next = create_item(data, all_items)))
				add_next_item(&list, next);
			if (next && next->type == light)
				holder->light_count++;
			if (next && next->type == enemy)
			{
				next->roar_sound = holder->roar_sound;
				next->hit_sound = holder->hit_sound;
			}
			while (*data && *data != ')')
				data++;
		}
		data++;
	}
	return (list);
}
