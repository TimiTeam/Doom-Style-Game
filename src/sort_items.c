/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:11:31 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:11:32 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

t_item		*tail_of(t_item *cur)
{
	while (cur != NULL && cur->next != NULL)
		cur = cur->next;
	return (cur);
}

void		swap_tail(t_item **cur, t_item **prev, t_item **tmp, t_item **tail)
{
	if (*prev)
		(*prev)->next = (*cur)->next;
	*tmp = (*cur)->next;
	(*cur)->next = NULL;
	(*tail)->next = *cur;
	*tail = *cur;
	*cur = *tmp;
}

void		proceed(t_item **cur, t_item **prev, t_item **new_head)
{
	if (*new_head == NULL)
		*new_head = *cur;
	*prev = *cur;
	*cur = (*cur)->next;
}

t_item		*partition(t_item *head, t_item **new_head,
						t_item **new_end, t_player *player)
{
	t_item	*pivot;
	t_item	*prev;
	t_item	*cur;
	t_item	*tail;
	t_item	*tmp;

	pivot = tail_of(head);
	prev = NULL;
	cur = head;
	tail = pivot;
	while (cur != pivot)
	{
		if ((cur->dist_to_player = len_between_points(player->pos, cur->pos))
	> (pivot->dist_to_player = len_between_points(player->pos, pivot->pos)))
			proceed(&cur, &prev, new_head);
		else
			swap_tail(&cur, &prev, &tmp, &tail);
	}
	if (*new_head == NULL)
		*new_head = pivot;
	*new_end = tail;
	return (pivot);
}

t_item		*quick_sort_recur(t_item *head, t_item *end, t_player *player)
{
	t_item	*new_head;
	t_item	*new_end;
	t_item	*pivot;
	t_item	*tmp;

	if (!head || head == end)
		return (head);
	new_head = NULL;
	new_end = NULL;
	pivot = partition(head, &new_head, &new_end, player);
	if (new_head != pivot)
	{
		tmp = new_head;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = NULL;
		new_head = quick_sort_recur(new_head, tmp, player);
		tmp = tail_of(new_head);
		tmp->next = pivot;
	}
	pivot->next = quick_sort_recur(pivot->next, new_end, player);
	head->dist_to_player = len_between_points(head->pos, player->pos);
	return (new_head);
}
