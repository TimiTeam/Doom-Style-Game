/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:12:29 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/07 13:12:30 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			check_for_light(t_media *media, int id, int sec)
{
	int					i;
	int					n;

	i = 0;
	n = 0;
	if (id != LIGHT)
		return (TRUE);
	while (i < media->worlds[media->w].sec[sec].n_it)
	{
		if (within(media->worlds[media->w].sec[sec].items[i].id, -1, \
		media->n_itf))
		{
			if (media->it_f[media->worlds[media->w].sec[sec].items[i].id].type \
			== LIGHT)
				n++;
			if (n > 1)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
