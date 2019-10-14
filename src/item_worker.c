/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_worker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:09:29 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:09:30 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sector_worker.h"

t_item					*new_item(void)
{
	t_item			*i;

	if (!(i = (t_item*)ft_memalloc(sizeof(t_item))))
		return (NULL);
	ft_memset(i, 0, sizeof(t_item));
	return (i);
}

t_item					*create_new_item(int x, int y)
{
	t_item				*i;

	if (!(i = new_item()))
		return (NULL);
	i->pos.x = x;
	i->pos.y = y;
	i->id = 0;
	return (i);
}

void					add_next_item(t_item **head, t_item *new)
{
	t_item				*m;
	unsigned			id;

	if (!*head)
	{
		*head = new;
		(*head)->id = 0;
		return ;
	}
	id = 1;
	m = *head;
	while (m->next)
	{
		m = m->next;
		id++;
	}
	new->id = id;
	m->next = new;
}

void					from_list_to_another_list(t_item **current_list,
										t_item **next_list, t_item *elem)
{
	t_item				*curr;
	t_item				*prev;

	if (*current_list == elem)
	{
		*current_list = elem->next;
		elem->next = NULL;
		add_next_item(next_list, elem);
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
			add_next_item(next_list, elem);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void					swap_items(t_item *elem1, t_item *elem2)
{
	t_item				*tmp;

	if (!elem1 || !elem2)
		return ;
	tmp = elem2->next;
	elem2->next = elem1;
	elem1->next = tmp;
}
