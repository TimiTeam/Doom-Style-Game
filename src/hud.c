/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:09:19 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:09:20 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void				draw_rect(SDL_Surface *surf, t_point pos,
								t_point size, int color)
{
	int				*pix;
	int				i;
	int				j;

	pix = (int*)surf->pixels;
	i = -1;
	while (++i < size.y)
	{
		j = -1;
		while (++j < size.x)
			pix[pos.x + j + surf->w * (pos.y + i)] = color;
	}
}

void				count_items(t_sdl *sdl, t_player *player,
										int *keys, int *coins)
{
	t_item			*curr_item;
	t_point			size;

	*coins = 0;
	*keys = 0;
	curr_item = player->inventar;
	size = (t_point){100, 100};
	while (curr_item)
	{
		if (curr_item->type == key)
		{
			(*keys)++;
			draw_image(sdl->surf, curr_item->states[0].texture[0],
									(t_point) {20, H - 120}, size);
		}
		else if (curr_item->type == coin)
		{
			(*coins)++;
			draw_image(sdl->surf, curr_item->states[0].texture[0],
									(t_point){140, H - 120}, size);
		}
		curr_item = curr_item->next;
	}
}

void				draw_items(t_sdl *sdl, t_player *player)
{
	int				items[2];
	SDL_Surface		*item_surface[2];
	char			*amount[2];
	int				i;

	i = -1;
	count_items(sdl, player, &items[0], &items[1]);
	while (++i < 2)
	{
		if (items[i])
		{
			amount[i] = ft_itoa(items[i]);
			item_surface[i] = TTF_RenderText_Blended(sdl->font, amount[i],
											(SDL_Color){255, 255, 255, 255});
			draw_image(sdl->surf, item_surface[i],
					(t_point){20 + 120 * i, H - 190}, (t_point){50, 50});
			free(amount[i]);
			SDL_FreeSurface(item_surface[i]);
		}
	}
}

void				draw_hud(t_sdl *sdl, t_player *player)
{
	char			*ammo;
	SDL_Surface		*ammo_surf;

	draw_rect(sdl->surf, (t_point){player->half_win_size.x - 150, 30}, (t_point){300, 30}, 0x00);
	if (player->health > 0)
		draw_rect(sdl->surf, (t_point){player->half_win_size.x - 150 + 4, 30 + 4},
		(t_point){(300 - 8) * player->health / 100.0f, 30 - 8}, 0x00ff0000);
	if (player->current_gun)
	{
		print_player_gun(sdl, player);
		ammo = ft_itoa(player->current_gun->ammo);
		ammo_surf = TTF_RenderText_Blended(sdl->font, ammo,
								(SDL_Color){255, 255, 255, 255});
		draw_image(sdl->surf, ammo_surf, (t_point){0, 130}, (t_point){50, 50});
		draw_image(sdl->surf, player->current_gun->icon, (t_point){0, 20},
													(t_point){200, 100});
		ft_strdel(&ammo);
		SDL_FreeSurface(ammo_surf);
	}
	draw_items(sdl, player);
}
