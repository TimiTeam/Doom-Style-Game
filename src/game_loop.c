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
	player->yaw -= 0.1/*3.0f / 50.0f*/;
	player->pos.z -= 0.2/*6.0f / 50*/;
	if (player->dead > 49)
	{
		player->dead = 1;
		*run = 0;
	}
}

void				win_animation(t_sdl *sdl, t_player *player,
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

void 				change_sector_state(t_sector *sectors, t_player *player)
{
	t_sector		*sec;

	if (!(sec = sectors))
		return ;
	while (sec)
	{
		if (sec->state == action_sec && (sec->type == door || sec->type == lift))
		{
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
		sec = sec->next;
	}
}

#define FRAME_VALUES 10
Uint32				frametimes[FRAME_VALUES];
Uint32				frametimelast;
Uint32				framecount;
float 				framespersecond;
void 				fpsinit()
{
    ft_memset(frametimes, 0, sizeof(frametimes));
    framecount = 0;
    framespersecond = 0;
    frametimelast = SDL_GetTicks();
}

void				fpsthink()
{
    Uint32			frametimesindex;
    Uint32			getticks;
    Uint8			count;
    Uint8 			i;

    frametimesindex = framecount % FRAME_VALUES;
    getticks = SDL_GetTicks();
    frametimes[frametimesindex] = getticks - frametimelast;
    frametimelast = getticks;
    framecount++;
    if (framecount < FRAME_VALUES)
        count = framecount;
    else
        count = FRAME_VALUES;
    framespersecond = 0;
    for (i = 0; i < count; i++) {
        framespersecond += frametimes[i];
    }
    framespersecond /= count;
    framespersecond = 1000.f / framespersecond;
}

static void			print_text(t_player player, t_sdl *sdl)
{
	SDL_Surface 	*text_surf;

	text_surf = NULL;
	if (player.lift_near)
		text_surf = txt_surf(sdl->font, "F to run lift", (SDL_Color){255, 255, 255, 255});
	else if (player.door_near)
		text_surf = txt_surf(sdl->font, "E to open Door", (SDL_Color){255, 255, 255, 255});
	else if (player.current_gun && player.current_gun->ammo <= 0)
		text_surf = txt_surf(sdl->font, "No ammo", (SDL_Color){255, 50, 50, 255});
	if (text_surf)
	{
		draw_image(sdl->surf, text_surf,(t_point){player.half_win_size.x + 100, player.half_win_size.y + 100},
		(t_point){150, 60});
		SDL_FreeSurface(text_surf);
	}
}

void 				change_player_state(t_player *player)
{
	t_sector		*near_sect;

	near_sect = NULL;
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
}

int					game_loop(t_sdl *sdl, t_player *player, t_sector *sectors)
{
	int				run;
	unsigned char	move[4];
	SDL_Surface		*dead_text;
	SDL_Surface 	*win_text;
	float			max_fps = 0;
	float			min_fps = 20;
	ft_memset(move, 0, sizeof(move));
	player->cos_angl = cos(player->angle);
	player->sin_angl = sin(player->angle);
	run = 1;
	dead_text = txt_surf(sdl->font, "YOU DIED", (SDL_Color){255, 30, 30, 255});
	win_text = txt_surf(sdl->font, "You Win", (SDL_Color){30, 255, 30, 255});
	sectors = player->all;
	fpsinit();
	if (!sectors)
		printf("NO sectors!!\n");
	while (run > 0)
	{
		prepare_surf(sdl);
		run_with_buff(player, sdl, sdl->win_size.x);
		draw_hud(sdl, player);
		fpsthink();
		max_fps = MAX(max_fps, framespersecond);
		min_fps = MIN(min_fps, framespersecond);
		printf("fps %f\n", framespersecond);
		if (framespersecond > 25)
			SDL_Delay(10);
		run = hook_event(player, move);
		move_player_vertically(player);
		if (player->dead)
			death_animation(sdl, player, dead_text, &run);
		if(player->win && all_death(sectors))
			win_animation(sdl, player, win_text, &run);
		print_text(*player, sdl);
		render_tex(sdl);
		change_sector_state(sectors, player);
		change_player_state(player);
	}
	SDL_FreeSurface(win_text);
	SDL_FreeSurface(dead_text);
	printf("\n\tFPS %f  -   %f\n\n", min_fps, max_fps);
	return (run);
}
