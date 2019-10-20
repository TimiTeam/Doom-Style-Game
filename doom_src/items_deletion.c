/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_deletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:09:38 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:09:39 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sector_worker.h"

void					delete_item_animation(t_animation *anim)
{
	unsigned char		i;

	i = 0;
	while (i < anim->max_textures && anim->texture[i])
	{
		SDL_FreeSurface(anim->texture[i]);
		i++;
	}
}

void					delete_item(t_item **item)
{
	int					i;

	if (!*item)
		return ;
	i = 0;
	while (i < 5)
	{
		delete_item_animation(&(*item)->states[i]);
		i++;
	}
	ft_memdel((void**)item);
}

void					delete_items_list_with_animation(t_item *items)
{
	t_item				*next;

	if (!items)
		return ;
	next = items;
	while (items)
	{
		next = items;
		items = next->next;
		delete_item(&next);
	}
}

void					delete_items_list(t_item *items)
{
	t_item				*next;

	if (!items)
		return ;
	next = items;
	while (items)
	{
		next = items;
		items = next->next;
		ft_memdel((void**)&next);
	}
}

void					delete_item_by_ptr(t_item **head, t_item *item)
{
	t_item				*curr;
	t_item				*prev;

	curr = (*head)->next;
	prev = *head;
	if (item == *head)
	{
		*head = item->next;
		ft_memdel((void**)&item);
		return ;
	}
	while (curr)
	{
		if (item == curr)
		{
			prev->next = curr->next;
			ft_memdel((void**)&curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
