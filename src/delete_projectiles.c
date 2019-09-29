/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_projectiles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:08:50 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:08:52 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void				free_proj(t_projectile *proj)
{
	if (!proj)
		return ;
	SDL_FreeSurface(proj->sprite);
	free(proj);
}

void				delete_projectiles(t_projectile *head)
{
	t_projectile	*tmp;

	while (head)
	{
		tmp = head->next;
		free_proj(head);
		head = tmp;
	}
}

void				delete_projectile(t_projectile **head, t_projectile *proj)
{
	t_projectile	*curr;
	t_projectile	*prev;

	if (!(*head) || !proj || !head)
		return ;
	curr = (*head)->next;
	prev = *head;
	if (proj == *head)
	{
		*head = proj->next;
		free_proj(proj);
		return ;
	}
	while (curr)
	{
		if (proj == curr)
		{
			prev->next = curr->next;
			free_proj(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
