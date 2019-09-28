#include "main_head.h"

void 				print_player_gun(t_sdl *sdl, t_player *pla)
{
	t_point			pos;
	t_point			size;
	SDL_Surface		*surf;

	if (!pla->current_gun->frame[(int)pla->current_gun->state])
	{
		pla->current_gun->state = 0;
		pla->current_gun->ammo--;
	}
	surf = pla->current_gun->frame[(int)pla->current_gun->state];
	if ((pla->shooting || pla->current_gun->state > 0) && pla->current_gun->ammo > 0)
		pla->current_gun->state += 0.44;
	pos.x = pla->half_win_size.x - surf->w / 2;
	pos.y = sdl->win_size.y - surf->h;
	draw_image(sdl->surf, surf, pos.x, pos.y, surf->w, surf->h);
}

void            draw_frame(SDL_Surface *surf, t_point pos, t_point size, int color)
{
	int	*pix;
	int i;
	int j;

	pix = (int*)surf->pixels;
	i = -1;
	j = -1;
	while (++j < size.x)
		if (pos.x + j < surf->w && pos.x + j >0 && pos.y >= 0 && pos.y < surf->h)
			pix[pos.x + j + surf->w * pos.y] = color;
	while (++i < size.y)
		if (pos.x + size.x - 1 < surf->w && pos.x + size.x >= 0 && (pos.y + i) >= 0 && (pos.y + i) < surf->h)
			pix[pos.x + size.x - 1 + surf->w * (pos.y + i)] = color;
	while (--j >= 0)
		if (pos.x + j < surf->w && pos.x + j >= 0 && (pos.y + size.y - 1) >= 0 && (pos.y + size.y - 1) < surf->h)
			pix[pos.x + j + surf->w * (pos.y + size.y - 1)] = color;
	while (--i >= 0)
		if (pos.x < surf->w && pos.x >= 0 && (pos.y + i) >= 0 && (pos.y + i) < surf->h)
			pix[pos.x + surf->w * (pos.y + i)] = color;
}

void			draw_rect(SDL_Surface *surf, t_point pos, t_point size, int color, Uint8 filled)
{
	int			*pix;
	int			i;
	int			j;

	pix = (int*)surf->pixels;
	i = -1;
	if (filled)
	{
		while (++i < size.y)
		{
			j = -1;
			while (++j < size.x)
				pix[pos.x + j + surf->w * (pos.y + i)] = color;
		}
	}
	else
        draw_frame(surf, pos, size, color);
}

void				draw_healthbar(SDL_Surface *surf, t_point pos, t_point size, int health)
{
	draw_rect(surf, pos, size, 0x00, 1);
	if (health > 0)
		draw_rect(surf, (t_point){pos.x + 4, pos.y + 4}, (t_point){(size.x - 8) * health / 100.0f, size.y - 8}, 0x00ff0000, 1);
}

void				draw_hud(t_sdl *sdl, t_player *player, TTF_Font *font)
{
	t_item			*curr_item;
	int				startx;
	SDL_Surface		*cur_text;

	startx = 20;
	curr_item = player->inventar;
	draw_healthbar(sdl->surf, (t_point){player->half_win_size.x - 125, 30}, (t_point){250, 30}, player->health);
	if(player->current_gun){
		print_player_gun(sdl, player);
		char	*ammo = ft_itoa(player->current_gun->ammo);
		SDL_Surface *ammo_surf = TTF_RenderText_Blended(font, ammo, (SDL_Color){255, 255, 255});
		draw_image(sdl->surf, ammo_surf, 0, 130, 50, 50);
		if (player->current_gun->icon)
			draw_image(sdl->surf, player->current_gun->icon, 0, 20, 200, 100);
		ft_strdel(&ammo);
		SDL_FreeSurface(ammo_surf);
	}
	while (curr_item)
	{
		cur_text = curr_item->states[0].texture[0];
		if (curr_item)
			draw_image(sdl->surf, cur_text, startx, H - 120,  100, 100);
		startx += 120;
		curr_item = curr_item->next;
	}
}