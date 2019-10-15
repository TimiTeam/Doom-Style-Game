/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:16:07 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:16:08 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

int				movement_events(SDL_Keycode code,
				unsigned char move[4], SDL_EventType type)
{
	if (code == SDLK_w || code == SDLK_UP)
		move[0] = type == SDL_KEYDOWN;
	else if (code == SDLK_s || code == SDLK_DOWN)
		move[1] = type == SDL_KEYDOWN;
	else if (code == SDLK_a)
		move[2] = type == SDL_KEYDOWN;
	else if (code == SDLK_d)
		move[3] = type == SDL_KEYDOWN;
	return (1);
}

void			change_gun(t_player *player, SDL_Keycode code)
{
	t_gun		*new_gun;

	new_gun = NULL;
	if (code == SDLK_1 && player->gun[pistol])
		new_gun = player->gun[pistol];
	else if (code == SDLK_2 && player->gun[shotgun])
		new_gun = player->gun[shotgun];
	else if (code == SDLK_3 && player->gun[plasmagun])
		new_gun = player->gun[plasmagun];
	if (new_gun && player->current_gun->type != new_gun->type)
	{
		new_gun->state = 0;
		player->current_gun = new_gun;
	}
}

int				guess_event(SDL_Keycode code,
			t_player *player, unsigned char move[4], SDL_EventType type)
{
	movement_events(code, move, type);
	if (code == SDLK_LSHIFT && type == SDL_KEYDOWN && !player->sit)
		player->speed *= 2;
	else if (code == SDLK_LSHIFT && type == SDL_KEYUP)
		player->speed = 0.5;
	else if (code == SDLK_SPACE && type == SDL_KEYDOWN
			&& (player->pos.z - player->height <= player->curr_sector->floor
			|| player->jetpack || player->curr_sector->type == uncovered))
		player->velocity += 0.8f;
	else if ((code == SDLK_1 || code == SDLK_2 || code == SDLK_3) && type == SDL_KEYDOWN)
		change_gun(player, code);
	else if (type == SDL_KEYDOWN && code == SDLK_e)
		check_door(player);
	else if (type == SDL_KEYDOWN && code == SDLK_f)
			activate_lift(player);		
	if (type == SDL_KEYDOWN && code == SDLK_LCTRL)
		player->sit = -3;
	if (type == SDL_KEYUP && code == SDLK_LCTRL)
		player->sit = 0;
	return (1);
}

void			update_player(t_player *player, unsigned char move[4])
{
	int			x;
	int			y;

	if (move[0] && !player->dead)
		move_player(player, player->sin_angl, player->cos_angl);
	if (move[1] && !player->dead)
		move_player(player, -player->sin_angl, -player->cos_angl);
	if (move[2] && !player->dead)
		move_player(player, -player->cos_angl, player->sin_angl);
	if (move[3] && !player->dead)
		move_player(player, player->cos_angl, -player->sin_angl);
	SDL_GetRelativeMouseState(&x, &y);
	y = -y;
	player->angle += x * 0.01;
	player->sky_w += x * (player->sky->w / 360.0f);
	player->cos_angl = cos(player->angle);
	player->sin_angl = sin(player->angle);
	player->yaw = CLAMP(player->yaw - y * 0.05f, -5, 5);
	if (player->current_gun && player->current_gun->type == plasmagun
			&& player->current_gun->state == 1.1f && player->current_gun->ammo > 0) 
	{
		player->current_gun->ammo--;
		add_projectile(&player->curr_sector->projectiles,
										create_projectile(*player));
		Mix_PlayChannel(1, player->current_gun->shot_sound, 0);
	}
}

int				hook_event(t_player *player,
				unsigned char move[4])
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN
		&& e.key.keysym.sym == SDLK_ESCAPE))
			return (-1);
		else if (e.type == SDL_KEYDOWN &&
			e.key.keysym.sym == SDLK_BACKSPACE)
			return (0);
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			if (!player->dead)
				guess_event(e.key.keysym.sym, player, move, e.type);
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN
			&& player->current_gun && e.button.button == SDL_BUTTON_LEFT
			&& player->current_gun->ammo > 0 && !player->dead)
			player->shooting = 1;
		else if (e.type == SDL_MOUSEBUTTONUP
			&& e.button.button == SDL_BUTTON_LEFT)
			player->shooting = 0;
	}
	update_player(player, move);
	return (1);
}
