#include "main_head.h"


void				draw_sectors(t_sector *sec, t_player *player,
									t_sdl *sdl, t_draw_data data)
{
	int				i;
	int				p;
	t_wall			*w;

	i = -1;
	p = -1;
	data.diff_ceil = sec->ceil - data.player_current_height;
	data.diff_floor = sec->floor - data.player_current_height;
	data.floor_calc = data.diff_floor * H * player->m_vfov;
	data.ceil_calc = data.diff_ceil * H * player->m_vfov;
	if (data.diff_ceil < 0)
		player->fall = 1;
	data.calc_one = H * player->m_vfov * player->yaw;
	while (++i < MAX_PORTALS && (w = sec->only_walls[i]))
		draw_world((t_world){sec, *w, player, sdl, data, &thread_draw_sector});
	while (++p < MAX_PORTALS && (w = sec->portals[p]))
		draw_world((t_world){sec, *w, player, sdl, data, &thread_draw_sector});
	quicksort(&sec->items, player);
	draw_sector_items(&sec->items, player, data, sdl->surf);
	draw_projectiles(&sec->projectiles,
				(t_p_n_d){*player, data}, sdl->surf, sec->items);
}

void				run_with_buff(t_player *player,
					t_sdl *sdl, unsigned int win_x)
{
	unsigned		x;
	t_draw_data		draw_data;

	x = 0;
	while (x < win_x)
	{
		draw_data.ybottom[x] = sdl->win_size.y - 1;
		draw_data.ytop[x] = 0;
		x++;
	}
	draw_data.recursion_deep = 0;
	draw_data.start = 0;
	draw_data.end = win_x;
	draw_data.player_current_height = (player->pos.z
	+ (player->curr_sector->ceil - player->curr_sector->floor
	<= player->height + player->sit ? -3 : player->sit));
	draw_sectors(player->curr_sector, player, sdl, draw_data);
}