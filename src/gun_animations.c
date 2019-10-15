#include "main_head.h"

static void			change_frame_state(t_gun *current_gun)
{
	if (current_gun)
	{
		if (current_gun->ammo > 0)
		{
			current_gun->state += 0.35f;
			if (current_gun->type == plasmagun)
				current_gun->state += 0.75f;
		}
		else
			current_gun->state = 0;
	}
}

void				print_player_gun(t_sdl *sdl, t_player *pla)
{
	t_point			pos;
	SDL_Surface		*surf;

	if (!pla->current_gun->frame[(int)pla->current_gun->state])
		pla->current_gun->state = 0;
	surf = pla->current_gun->frame[(int)pla->current_gun->state];
	if ((pla->shooting || pla->current_gun->state))
		change_frame_state(pla->current_gun);
	if (pla->current_gun->state == 0.35f
		&& pla->current_gun->type != plasmagun && pla->current_gun->ammo > 0)
	{
		Mix_PlayChannel(-1, pla->current_gun->shot_sound, 0);
		pla->current_gun->ammo--;
	}
	pos.x = pla->half_win_size.x - surf->w / 2;
	pos.y = sdl->win_size.y - surf->h;
	draw_image(sdl->surf, surf, pos, (t_point){surf->w, surf->h});
}