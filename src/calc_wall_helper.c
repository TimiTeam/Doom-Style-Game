/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:57:00 by tbujalo           #+#    #+#             */
/*   Updated: 2019/10/15 14:58:34 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void			map_wall_text(int *u0, int *u1,
					t_vector diff, float scaled_tex)
{
	*u0 = diff.x * scaled_tex;
	*u1 = diff.y * scaled_tex;
}

int				compare_two_int_array(short *arr_one, short *arr_two,
		int from, int to)
{
	int			i;

	i = from;
	if (!arr_one || !arr_two)
		return (0);
	while (i < to)
	{
		if (arr_one[i] != arr_two[i])
			return (0);
		i++;
	}
	return (1);
}
