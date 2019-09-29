#include "main_head.h"

int				movement_events(SDL_Keycode code,
			t_player *player, unsigned char move[4], SDL_EventType type)
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

int				guess_event(SDL_Keycode code,
			t_player *player, unsigned char move[4], SDL_EventType type)
{
	movement_events(code, player, move, type);
	if (code == SDLK_LSHIFT && type == SDL_KEYDOWN && !player->sit)
		player->speed = 1.2f;
	else if (code == SDLK_LSHIFT && type == SDL_KEYUP)
		player->speed = 0.6;
	else if (code == SDLK_SPACE && type == SDL_KEYDOWN)
		player->velocity += 0.8f;
	else if (code == SDLK_1 && type == SDL_KEYDOWN && player->gun[pistol])
		player->current_gun = player->gun[pistol];
	else if (code == SDLK_2 && type == SDL_KEYDOWN && player->gun[shotgun])
		player->current_gun = player->gun[shotgun];
	else if (code == SDLK_3 && type == SDL_KEYDOWN && player->gun[plasmagun])
		player->current_gun = player->gun[plasmagun];
	else if (type == SDL_KEYDOWN && code == SDLK_e)
		check_door(player, player->curr_sector);
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
	player->skyW += x * (player->sky->w / 360.0f);
	player->cos_angl = cos(player->angle);
	player->sin_angl = sin(player->angle);
	player->yaw = clamp(player->yaw - y * 0.05f, -5, 5);
	if (player->current_gun && player->current_gun->state
	== 0.44f && player->current_gun->type == plasmagun)
		add_projectile(&player->curr_sector->projectiles,
										create_projectile(*player));
}

int				hook_event(t_player *player,
				unsigned char move[4], t_sector *sectors)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN
		&& e.key.keysym.sym == SDLK_ESCAPE))
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