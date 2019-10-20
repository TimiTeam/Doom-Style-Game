/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:31:04 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 16:31:05 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					bubble_sort(int *tab, int n)
{
	int					i;
	int					lim;
	int					swap;

	if (!tab)
		return ;
	lim = n - 1;
	i = 0;
	while (i < lim)
	{
		if (tab[i] > tab[i + 1])
		{
			swap = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = swap;
			if (i)
				i--;
		}
		else
			i++;
	}
}

void					pair_sort(int *a, int n)
{
	int					one;
	int					prev;
	int					next;
	int					count;

	count = -1;
	while (++count < n)
	{
		one = 0;
		prev = n - 1;
		next = 2;
		while (one < n - 1)
		{
			if (next >= n)
				next = 0;
			if (a[one] != a[prev] && a[one + 1] != a[next])
				swap_ints(&a[one], &a[one + 1]);
			if (next == 0)
				break ;
			prev = one + 1;
			one = next;
			next = one + 2;
		}
	}
}
