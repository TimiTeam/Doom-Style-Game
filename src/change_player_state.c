#include "main_head.h"

static void				death_animation(t_sdl *sdl, t_player *player,
									SDL_Surface *text, int *run)
{
	player->dead++;
	apply_filter(sdl->surf, 1.0f - (1.0f / 50) * player->dead);
	draw_image(sdl->surf, text,
	(t_point){player->half_win_size.x - 200,
	player->half_win_size.y - 100}, (t_point){400, 200});
	player->yaw -= 0.1;
	player->pos.z -= 0.2;
	if (player->dead > 49)
	{
		player->dead = 1;
		*run = 0;
	}
}

static void				win_animation(t_sdl *sdl, t_player *player,
									SDL_Surface *text, int *run)
{
	player->win++;
	draw_image(sdl->surf, text,
	(t_point){player->half_win_size.x - 200,
	player->half_win_size.y - 100}, (t_point){400, 200});
	if (player->win > 40)
	{
		*run = 0;
		player->curr_map++;
	}
}

static short		count_enemies(t_sector *sectors)
{
	t_sector		*sect;
	t_item			*items;
	short			enemies;

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
	return (enemies);
}


void 				change_player_state(t_player *player, t_sdl *sdl, int *run)
{
	SDL_Surface		*dead_text;
	SDL_Surface 	*win_text;
	t_sector		*near_sect;

	near_sect = NULL;
	if (player->curr_sector->type == murderous)
		player->health -= 1;
	if ((near_sect = get_near_sector(player)) &&
		near_sect->type == lift && near_sect->state == calm)
		player->lift_near = 1;
	else
		player->lift_near = 0;
	if (near_sect && near_sect->type == door &&
		near_sect->state == calm && !near_sect->door_open)
		player->door_near = 1;
	else
		player->door_near = 0;
	if (player->health <= 0 && !player->dead)
		player->dead = 1;
	player->count_enemies = count_enemies(player->all);
	if (player->dead)
	{
		dead_text = txt_surf(sdl->font, "YOU DIED", (SDL_Color){255, 30, 30, 255});
		death_animation(sdl, player, dead_text, run);
		SDL_FreeSurface(dead_text);
	}
	else if(player->win && !player->count_enemies)
	{
		win_text = txt_surf(sdl->font, "You Win", (SDL_Color){30, 255, 30, 255});
		win_animation(sdl, player, win_text, run);
		SDL_FreeSurface(win_text);
	}
}