/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_lit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:18:39 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 12:18:41 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

int						select_it(char set_get_unset, unsigned short id, int v)
{
	static int			select[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

	if (id >= 10)
		return (-1);
	else if (set_get_unset == 0)
		select[id] = v;
	else if (set_get_unset == 2)
		select[id] = -1;
	return (select[id]);
}

int						lit_it(char set_get_unset, unsigned short id, int value)
{
	static int			select[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

	if (id >= 10)
		return (-1);
	else if (set_get_unset == 0)
		select[id] = value;
	else if (set_get_unset == 2)
		select[id] = -1;
	return (select[id]);
}
