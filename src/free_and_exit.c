/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:04:57 by tbujalo           #+#    #+#             */
/*   Updated: 2019/10/16 14:32:20 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void			free_all(t_player **player, t_sdl **sdl,
								t_read_holder *holder, t_pr *m)
{
	free_player(*player);
	*player = NULL;
	delete_light_source(holder->light_source, holder->light_count);
	holder->light_source = NULL;
	free_t_sdl(sdl);
	*sdl = NULL;
	free_menu(m);
	ft_memset(m, 0, sizeof(t_pr));
}

static void		free_holder_texture_and_maps(t_read_holder *holder)
{
	int			i;

	if (holder)
	{
		i = -1;
		while (++i < 5 && holder->maps_path[i])
		{
			if (holder->skyboxes[i])
				SDL_FreeSurface(holder->skyboxes[i]);
			ft_strdel(&holder->maps_path[i]);
			holder->maps_path[i] = NULL;
		}
		i = -1;
		if (holder->textures)
		{
			while (++i < holder->text_count && holder->textures[i])
			{
				SDL_FreeSurface(holder->textures[i]);
				holder->textures[i] = NULL;
			}
			ft_memdel((void**)&holder->textures);
		}
	}
}

void			free_data_holder(t_read_holder *holder)
{
	if (!holder)
		return ;
	if (holder->all_guns)
		delete_guns(holder->all_guns);
	holder->all_guns = NULL;
	if (holder->roar_sound)
		Mix_FreeChunk(holder->roar_sound);
	if (holder->hit_sound)
		Mix_FreeChunk(holder->hit_sound);
	delete_items_list_with_animation(holder->all_items);
	holder->all_items = NULL;
	delete_sectors(holder->all);
	holder->all = NULL;
	free_holder_texture_and_maps(holder);
}
