#include "main_head.h"

int 				load_game(t_player *player, t_read_holder *holder)
{
	t_sector		*sectors;

	if (holder->curr_map >= holder->maps_count)
		return (error_message("Invalid map"));
	delete_sectors(holder->all);
	delete_light_source(holder->light_source, holder->light_count);
	holder->light_count = 0;
	sectors = read_map(holder->maps_path[holder->curr_map], holder, &player->pos);
	if (!sectors)
		return(error_message(holder->maps_path[holder->curr_map]));
	holder->all = sectors;
	player->height = EyeHeight;
	if (!(player->curr_sector = get_player_sector(sectors, holder->player_sector_id)))
		return (error_message("Sector Not Found"));
	player->pos.z = player->curr_sector->floor + player->height;
	player->yaw = 0;
	player->curr_map = holder->curr_map;
	return (1);
}

int				render_menu(t_pr *m, t_sdl *sdl)
{
	SDL_Surface	*level_choice;

	level_choice = NULL;
	draw_image(sdl->surf, m->background, 0, 0, sdl->win_size.x, sdl->win_size.y);
	draw_image(sdl->surf, m->logo, m->logo_rect.x, m->logo_rect.y, m->logo_rect.w, m->logo_rect.h);
	draw_image(sdl->surf, m->play_button, m->play_rect.x, m->play_rect.y, m->play_rect.w, m->play_rect.h);
	draw_image(sdl->surf, m->choose_level_button, m->choose_level_rect.x,
		m->choose_level_rect.y, m->choose_level_rect.w, m->choose_level_rect.h);
	level_choice = get_text_surfcae(m, m->maps[m->i]);
	if (level_choice)
	{
		draw_image(sdl->surf, level_choice, m->font_rect.x, m->font_rect.y, m->font_rect.w, m->font_rect.h);
		SDL_FreeSurface(level_choice);
	}
	draw_image(sdl->surf, m->exit_button, m->exit_rect.x, m->exit_rect.y, m->exit_rect.w, m->exit_rect.h);
	return (1);
}

void 					free_menu(t_pr *menu)
{
	SDL_FreeSurface(menu->background);
	SDL_FreeSurface(menu->play_button);
	SDL_FreeSurface(menu->exit_button);
	SDL_FreeSurface(menu->logo);
	SDL_FreeSurface(menu->choose_level_button);
	TTF_CloseFont(menu->font);
}