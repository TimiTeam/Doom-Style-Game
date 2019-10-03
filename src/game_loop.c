/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:16:16 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/30 16:10:45 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void				run_with_buff(t_player *player,
					t_sdl *sdl, unsigned int win_x)
{
	unsigned		x;
	int				ytop[win_x];
	int				ybottom[win_x];
	t_draw_data		draw_data;

	x = 0;
	while (x < win_x)
	{
		draw_data.ybottom[x] = sdl->win_size.y - 1;
		draw_data.ytop[x] = 0;
		x++;
	}
	draw_data.start = 0;
	draw_data.end = win_x;
	draw_data.player_current_height = (player->pos.z
	+ (player->curr_sector->ceil - player->curr_sector->floor
	<= player->height + player->sit ? -3 : player->sit));
	draw_sectors(player->curr_sector, player, sdl, draw_data);
}

void				death_animation(t_sdl *sdl, t_player *player,
									SDL_Surface *text, int *run)
{
	player->dead++;
	apply_filter(sdl->surf, 1.0f - (1.0f / 50) * player->dead);
	draw_image(sdl->surf, text,
	(t_point){player->half_win_size.x - 200,
	player->half_win_size.y - 100}, (t_point){400, 200});
	player->yaw -= 3.0f / 50.0f;
	player->pos.z -= 6.0f / 50;
	if (player->dead > 49)
	{
		player->dead = 0;
		*run = 0;
		player->curr_map = -1;
	}
}

void				win_animation(t_sdl *sdl, t_player *player,
									SDL_Surface *text, int *run)
{
	player->win++;
	draw_image(sdl->surf, text,
	(t_point){player->half_win_size.x - 200,
	player->half_win_size.y - 100}, (t_point){400, 200});
	if (player->win > 30)
	{
		*run = 0;
		player->curr_map++;
	}
}

unsigned			all_death(t_sector *sectors)
{
	t_sector		*sect;
	t_item			*items;
	unsigned		enemies;

	sect = sectors;
	enemies = 0;
	while (sect)
	{
		items = sect->items;
		while (items)
		{
			if (items->type == enemy)
				enemies++;
			items = items->next;
		}
		sect = sect->next;
	}
	return (enemies == 0 ? 1 : 0);
}

void				prepare_surf(t_sdl *sdl)
{
	
	SDL_SetRenderDrawColor(sdl->ren, 0, 200, 0, 255);
	SDL_RenderClear(sdl->ren);
	SDL_FillRect(sdl->surf, NULL, 0x00);
}

void				render_tex(t_sdl *sdl)
{
	SDL_Texture		*tex;

	tex = SDL_CreateTextureFromSurface(sdl->ren, sdl->surf);
	sdl_render(sdl->ren, tex, NULL, NULL);
	SDL_DestroyTexture(tex);
	SDL_RenderPresent(sdl->ren);
}

int					game_loop(t_sdl *sdl, t_player *player, t_sector *sectors)
{
	int				run;
	char			str[100];
	unsigned char	move[4];
	SDL_Surface		*dead_text;
	SDL_Surface 	*win_text;
	ft_memset(move, 0, sizeof(move) * 4);
	player->cos_angl = cos(player->angle);
	player->sin_angl = sin(player->angle);
	run = 1;
	dead_text = txt_surf(sdl->font, "YOU DIED", (SDL_Color){255, 30, 30, 255});
	win_text = txt_surf(sdl->font, "You Win", (SDL_Color){30, 255, 30, 255});
	if (!sectors)
		printf("NO sectors!!\n");
	while (run > 0)
	{
		prepare_surf(sdl);
		run_with_buff(player, sdl, sdl->win_size.x);
		draw_hud(sdl, player);
		run = hook_event(player, move);
		move_player_vertically(player);
		if (player->dead)
			death_animation(sdl, player, dead_text, &run);
		if(player->win && all_death(sectors))
			win_animation(sdl, player, win_text, &run);
		render_tex(sdl);
	}
	SDL_FreeSurface(win_text);
	SDL_FreeSurface(dead_text);
	return (run);
}
