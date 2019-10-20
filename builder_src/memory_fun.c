/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:04:23 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/07 16:58:44 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					*realloc_tab(void *old_tab, size_t new_size, \
size_t old_size)
{
	size_t				i;
	size_t				n;
	unsigned char		*new;
	unsigned char		*old;

	if ((new = (void *)ft_memalloc(new_size)))
	{
		ft_bzero(new, new_size);
		old = (unsigned char *)old_tab;
		i = 0;
		n = get_min(old_size, new_size);
		while (i < n)
		{
			new[i] = old[i];
			i++;
		}
	}
	if (old_tab)
		free(old_tab);
	if (new)
		return ((void *)new);
	return (NULL);
}

void					free_tab(void **tab, int size)
{
	int					i;

	if (!tab)
		return ;
	i = 0;
	while (i < size && tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}
