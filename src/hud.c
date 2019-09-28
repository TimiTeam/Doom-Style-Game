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
		printf("current_gun->ammo : %d\n", pla->current_gun->ammo);
	}
	surf = pla->current_gun->frame[(int)pla->current_gun->state];
	if ((pla->shooting || pla->current_gun->state) && pla->current_gun->ammo > 0)
		pla->current_gun->state += 0.44;
	pos.x = pla->half_win_size.x - surf->w / 2;
	pos.y = sdl->win_size.y - surf->h;
	draw_image(sdl->surf, surf, pos, (t_point){surf->w, surf->h});
}

void			draw_rect(SDL_Surface *surf, t_point pos, t_point size, int color)
{
	int			*pix;
	int			i;
	int			j;

	pix = (int*)surf->pixels;
	i = -1;
	while (++i < size.y)
	{
		j = -1;
		while (++j < size.x)
			pix[pos.x + j + surf->w * (pos.y + i)] = color;
	}
}

void				draw_healthbar(SDL_Surface *surf, t_point pos, t_point size, int health)
{
	draw_rect(surf, pos, size, 0x00);
	if (health > 0)
		draw_rect(surf, (t_point){pos.x + 4, pos.y + 4}, (t_point){(size.x - 8) * health / 100.0f, size.y - 8}, 0x00ff0000);
}

void				count_items(t_sdl *sdl, t_player *player, int *keys, int *coins)
{
	t_item			*curr_item;
	t_item			*head;
	t_point			size;

	head = player->inventar;
	*coins = 0;
	*keys = 0;
	curr_item = player->inventar;
	size = (t_point){100, 100};
	while (curr_item)
	{
		if (curr_item->type == key){
			(*keys)++;
			draw_image(sdl->surf, curr_item->states[0].texture[0], (t_point) {20, H - 120}, size);
		}
		else if (curr_item->type == coin){
			(*coins)++;
			draw_image(sdl->surf, curr_item->states[0].texture[0], (t_point){140 , H - 120}, size);
		}
		curr_item = curr_item->next;
	}
	player->inventar = head;
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
			item_surface[i] = TTF_RenderText_Blended(sdl->font, amount[i], (SDL_Color){255, 255, 255});
			draw_image(sdl->surf, item_surface[i], (t_point){20 + 120 * i, H - 190}, (t_point){50, 50});
			free(amount[i]);
			SDL_FreeSurface(item_surface[i]);
		}
	}
}

void				draw_hud(t_sdl *sdl, t_player *player)
{
	int				startx;
	char			*ammo;
	SDL_Surface		*ammo_surf;

	startx = 20;
	draw_healthbar(sdl->surf, (t_point){W / 2 - 150, 30}, (t_point){300, 30}, player->health);
	if(player->current_gun){
		print_player_gun(sdl, player);
		ammo = ft_itoa(player->current_gun->ammo);
		ammo_surf = TTF_RenderText_Blended(sdl->font, ammo, (SDL_Color){255, 255, 255});
		draw_image(sdl->surf, ammo_surf, (t_point){0, 130}, (t_point){50, 50});
		draw_image(sdl->surf, player->current_gun->icon, (t_point){0, 20}, (t_point){200, 100});
		ft_strdel(&ammo);
		SDL_FreeSurface(ammo_surf);
	}
	draw_items(sdl, player);
}