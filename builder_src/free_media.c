/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_media.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:42:38 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 18:42:39 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					free_media_txtr(t_media *media)
{
	int					i;

	if (media && media->txtr)
	{
		i = -1;
		while (++i < media->n_t)
		{
			if (media->txtr[i].full_p)
				free(media->txtr[i].full_p);
			if (media->txtr[i].name)
				free(media->txtr[i].name);
			if (media->txtr[i].sdl_t)
				SDL_DestroyTexture(media->txtr[i].sdl_t);
		}
		free(media->txtr);
	}
}

void					free_media_itf(t_media *media)
{
	int					i;

	if (media && media->it_f)
	{
		i = -1;
		while (++i < media->n_itf)
		{
			if (media->it_f[i].name)
			{
				free(media->it_f[i].name);
				media->it_f[i].name = NULL;
			}
			if (media->it_f[i].full_p)
			{
				free(media->it_f[i].full_p);
				media->it_f[i].full_p = NULL;
			}
		}
		free(media->it_f);
	}
}

void					free_media_worlds(t_media *media)
{
	int					j;

	if (media && media->worlds)
	{
		j = 0;
		while (j < media->n_worlds)
			free_world(&media->worlds[j++]);
		free(media->worlds);
	}
}

void					free_media(t_media *media)
{
	if (!media)
		return ;
	free_media_worlds(media);
	free_media_txtr(media);
	free_media_itf(media);
	ft_memdel((void **)&media);
}
