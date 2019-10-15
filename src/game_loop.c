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

static void			open_or_run_lift(t_sector *sec, t_player *player)
{
	if (!sec || !player)
		return ;
	if (sec->type == door)
		sec->ceil += sec->speed;
	else if (sec->type == lift)
	{
		sec->floor += sec->speed;
		sec->ceil += sec->speed;
		if (player->curr_sector == sec)
			player->pos.z += sec->speed;
	}
	if (((int)sec->ceil == (int)sec->max_up && sec->type == door) ||
		(sec->type == lift && (int)sec->floor == (int)sec->max_up))
	{
		sec->state = calm;
		sec->speed = 0;
		sec->max_up = 0;
		sec->door_open = 1;
	}
}

static void			change_sector_state(t_sector *sectors, t_player *player)
{
	t_sector		*sec;

	if (!(sec = sectors))
		return ;
	while (sec)
	{
		if (sec->floor > player->pos.z)
			sec->floor_visible = no_visible;
		else
			sec->floor_visible = visible;
		if (sec->state == action_sec &&
			(sec->type == door || sec->type == lift))
			open_or_run_lift(sec, player);
		sec = sec->next;
	}
}

static SDL_Surface	*get_text_surf(t_sdl *sdl, t_player player)
{
	if (player.lift_near)
		return (txt_surf(sdl->font, "F to run lift",
			(SDL_Color){255, 255, 255, 255}));
	else if (player.door_near)
		return (txt_surf(sdl->font, "E to open Door",
			(SDL_Color){255, 255, 255, 255}));
	else if (player.current_gun && player.current_gun->ammo <= 0)
		return (txt_surf(sdl->font, "No ammo",
			(SDL_Color){255, 50, 50, 255}));
	else
		return (NULL);
}

static void			print_text(t_player player, t_sdl *sdl)
{
	SDL_Surface		*text_surf;
	SDL_Surface		*enemies;
	char			*num_enemues;

	num_enemues = ft_itoa(player.count_enemies);
	text_surf = get_text_surf(sdl, player);
	enemies = txt_surf(sdl->font, num_enemues,
	(SDL_Color){255, 255, 255, 255});
	if (text_surf)
	{
		draw_image(sdl->surf, text_surf, (t_point){player.half_win_size.x + 100,
			player.half_win_size.y + 100},
		(t_point){150, 60});
		SDL_FreeSurface(text_surf);
	}
	draw_image(sdl->surf, enemies, (t_point)
		{sdl->win_size.x - 100, sdl->win_size.y - 100}, (t_point){80, 60});
	SDL_FreeSurface(enemies);
	ft_strdel(&num_enemues);
}

int					game_loop(t_sdl *sdl, t_player *player, t_sector *sectors)
{
	int				run;
	unsigned char	move[4];
	t_fps_counter	fps;

	ft_memset(move, 0, sizeof(move));
	run = 1;
	sectors = player->all;
	fpsinit(&fps);
	while (run > 0)
	{
		prepare_surf(sdl->ren, sdl->surf);
		run_with_buff(player, sdl, sdl->win_size.x);
		draw_hud(sdl, player);
		fpsthink(&fps);
		if (fps.framespersecond > 25)
			SDL_Delay(10);
		run = hook_event(player, move);
		move_player_vertically(player);
		change_sector_state(sectors, player);
		change_player_state(player, sdl, &run);
		print_text(*player, sdl);
		render_tex(sdl);
	}
	return (run);
}
