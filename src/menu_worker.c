/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_worker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:10:42 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/30 16:09:00 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void			clear_player(t_player *player)
{
	if (!player)
		return ;
	delete_items_list(player->inventar);
	ft_memset(player->gun, 0, sizeof(player->gun));
	player->health = 100;
	player->current_gun = NULL;
	player->dead = 0;
	player->shooting = 0;
	player->inventar = NULL;
}

int 		prepare_playear(t_player *player, t_read_holder *holder)
{
	player->pos = holder->player_start;
	player->end_pos = holder->player_end;
	player->end_sec = holder->player_end_sect;
	player->height = EYEHEIGHT;
	if (!(player->curr_sector = get_player_sector(holder->all,
					holder->player_sector_id)))
		return (error_message("Sector Not Found"));
	player->pos.z = player->curr_sector->floor + player->height;
	player->yaw = 0;
	player->win = 0;
	player->curr_map = holder->curr_map;
	player->all = holder->all;
	player->sky = holder->skyboxes[holder->curr_map] ?
		holder->skyboxes[holder->curr_map] : holder->skyboxes[0];
	return (1);
}

t_sector			*load_game(t_player *player, t_read_holder *holder)
{
	t_sector		*sectors;

	if (player->win)
		holder->curr_map++;
	if (holder->curr_map >= holder->maps_count && player->win)
		return (print_error_message_null("Player ","Win!!"));
	else if (holder->curr_map >= holder->maps_count)
		return (print_error_message_null("Invalid map","Exit"));
	delete_sectors(holder->all);
	holder->all = NULL;
	delete_light_source(holder->light_source, holder->light_count);
	holder->light_source = NULL;
	holder->light_count = 0;
	if ((player->curr_map != holder->curr_map || player->dead)
		&& !player->win)
		clear_player(player);
	if(!(sectors = read_map(holder->maps_path[holder->curr_map],
										holder)))
		return (print_error_message_null(holder->maps_path[holder->curr_map],"Wrong map"));
	if (!prepare_playear(player, holder))
		return (print_error_message_null("Player info is","Broken"));
	return (sectors);
}

int				render_menu(t_pr *m, t_sdl *sdl)
{
	SDL_Surface	*level;

	level = NULL;
	draw_image(sdl->surf, m->background, (t_point){0, 0}, sdl->win_size);
	draw_image(sdl->surf, m->logo,
				(t_point){m->logo_rect.x, m->logo_rect.y},
				(t_point){m->logo_rect.w, m->logo_rect.h});
	draw_image(sdl->surf, m->play_button,
				(t_point){m->play_rect.x, m->play_rect.y},
				(t_point){m->play_rect.w, m->play_rect.h});
	draw_image(sdl->surf, m->choose_level_button,
				(t_point){m->choose_level_rect.x, m->choose_level_rect.y},
				(t_point){m->choose_level_rect.w, m->choose_level_rect.h});
	level = txt_surf(m->font, m->maps[m->i], (SDL_Color){255, 255, 255, 255});
	if (level)
	{
		draw_image(sdl->surf, level,
				(t_point){m->font_rect.x, m->font_rect.y},
				(t_point){m->font_rect.w, m->font_rect.h});
		SDL_FreeSurface(level);
	}
	draw_image(sdl->surf, m->exit_button,
				(t_point){m->exit_rect.x, m->exit_rect.y},
				(t_point){m->exit_rect.w, m->exit_rect.h});
	return (1);
}

void			free_menu(t_pr *menu)
{
	if (menu->background)
		SDL_FreeSurface(menu->background);
	if (menu->play_button)
		SDL_FreeSurface(menu->play_button);
	if (menu->exit_button)
		SDL_FreeSurface(menu->exit_button);
	if (menu->logo)
		SDL_FreeSurface(menu->logo);
	if (menu->choose_level_button)
		SDL_FreeSurface(menu->choose_level_button);
	if (menu->font)
		TTF_CloseFont(menu->font);
}
