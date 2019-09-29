#include "main_head.h"

void 				free_data_holder(t_read_holder *holder)
{
	int				i;
	
	if(!holder)
		return ;
	delete_sectors(holder->all);
	delete_items_list_with_animation(holder->all_items);
	i = 0;
	while (i < 5 && holder->maps_path[i])
	{
		ft_strdel(&holder->maps_path[i]);
		i++;
	}
	i = 0;
	while(holder->textures && i < holder->text_count && holder->textures[i])
	{
		SDL_FreeSurface(holder->textures[i]);
		i++;
	}
	ft_memdel((void**)&holder->textures);
}

void			maping_wall_texture(int *u0, int *u1, float diff_start, float diff_end, float scaled_tex)
{
	*u0 = diff_start * scaled_tex;
	*u1 = diff_end * scaled_tex;
}

int				run_game(t_sdl *sdl, t_player *player, t_pr *m, t_read_holder *holder)
{
	int				in_game;
	SDL_Texture		*tex;

	in_game = 0;
	while (1)
	{
		if ((in_game = menu_hooks(m, holder)) < 0)
			break ;
		if (in_game > 0)
		{
			if (player->curr_map != holder->curr_map)
				if (!load_game(player, holder))
					return(error_message("Can't create game"));
			in_game = game_loop(sdl, player, holder->all);
		}
		render_menu(m, sdl);
		SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, 255);
		SDL_RenderClear(sdl->ren);
		tex = SDL_CreateTextureFromSurface(sdl->ren, sdl->surf);
		sdl_render(sdl->ren, tex, NULL, NULL);
		SDL_DestroyTexture(tex);
		SDL_RenderPresent(sdl->ren);
	}
	SDL_DestroyTexture(tex);
	return (0);
}

void				free_all(t_player *player, t_sdl *sdl,
								t_read_holder holder, t_pr m)
{
	delete_guns(player->all_guns);
	free_player(player);
	delete_light_source(holder.light_source, holder.light_count);
	free_t_sdl(&sdl);
	free_menu(&m);
}

void				init(t_sdl **sdl, t_pr *m, t_read_holder *holder)
{
	*sdl = new_t_sdl(W, H, "doom-nukem");
	init_sdl(*sdl);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	load_textures(m, *sdl, holder);
	initialize_sdl_win(m);
}

int					main(void)
{
	t_read_holder	holder;
	t_player		*player;
	t_sdl			*sdl;
	t_vector		player_pos;
	t_pr			m;

	holder = (t_read_holder){NULL};
	m = (t_pr){NULL};
	m.i = 0;
	m.win_h = H;
	m.win_w = W;
	if (read_game_config_file(&holder, "game_info.txt"))
	{
		init(&sdl, &m, &holder);
		sdl->font = m.font;
		player = new_t_player(3, 3, sdl->win_size);
		player->sky = load_jpg_png("textures/skybox.png");
		player->all_guns = (t_gun**)malloc(sizeof(t_gun*) * 3);
		load_guns(player->all_guns);
		run_game(sdl, player, &m, &holder);
		free_all(player, sdl, holder, m);
	}
	free_data_holder(&holder);
	system("leaks -q doom-nukem");
}