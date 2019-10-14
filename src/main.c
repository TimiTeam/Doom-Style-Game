/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:17:21 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:17:22 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void				map_wall_text(int *u0, int *u1,
					t_vector diff, float scaled_tex)
{
	*u0 = diff.x * scaled_tex;
	*u1 = diff.y * scaled_tex;
}

int					run_game(t_sdl *sdl, t_player *player,
							t_pr *m, t_read_holder *holder)
{
	int				in_game;
	SDL_Texture		*tex;
	t_sector		*ret;

	in_game = 0;
	ret = NULL;
	tex = NULL;
	while (in_game >= 0)
	{
		if (!player->win && !player->dead && (in_game = menu_hooks(m, holder)) < 0)
			break ;
		render_menu(m, sdl);
		SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, 255);
		SDL_RenderClear(sdl->ren);
		tex = SDL_CreateTextureFromSurface(sdl->ren, sdl->surf);
		sdl_render(sdl->ren, tex, NULL, NULL);
		SDL_DestroyTexture(tex);
		SDL_RenderPresent(sdl->ren);
		if (in_game > 0 || player->win || player->dead)
		{
			if (player->curr_map != holder->curr_map || player->win || player->dead)
				if (!(ret = load_game(player, holder)))
					return (error_message("Can't create game"));
			in_game = game_loop(sdl, player, ret);
		}
	}
	SDL_DestroyTexture(tex);
	return (0);
}

void				free_all(t_player **player, t_sdl **sdl,
								t_read_holder *holder, t_pr *m)
{
	if (*player && (*player)->all_guns)
		delete_guns((*player)->all_guns);
	free_player(*player);
	*player = NULL;
	delete_light_source(holder->light_source, holder->light_count);
	holder->light_source = NULL;
	free_t_sdl(sdl);
	*sdl = NULL;
	free_menu(m);
	ft_memset(m, 0, sizeof(t_pr));
}

int					init(t_sdl **sdl, t_pr *m, t_read_holder *holder)
{
	*sdl = new_t_sdl(W, H, "doom-nukem");
	if (!sdl)
		return (print_error_message("Error initializing sdl\n", ""));
	if (!init_sdl(*sdl))
		return (0);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (!load_menu_textures(m, holder))
		return (print_error_message("Can't load menu resourses\n", ""));
	holder->hit_sound = Mix_LoadWAV("sounds/monster_roar.wav");
	holder->roar_sound = Mix_LoadWAV("sounds/monster_bite.wav");
	initialize_menu(m);
	return (1);
}

int					main(void)
{
	t_read_holder	holder;
	t_player		*player;
	t_sdl			*sdl;
	t_pr			m;
		
	ft_memset(&holder, 0, sizeof(t_read_holder));
	ft_memset(&m, 0, sizeof(t_pr));
	m.i = 0;
	m.win_h = H;
	m.win_w = W;
	player = NULL;
	if (init_sound() && read_game_config_file(&holder, "game_info.txt")
	&& init(&sdl, &m, &holder))
	{
		sdl->font = m.font;
		player = new_t_player(3, 3, sdl->win_size);
		player->sky = load_jpg_png("textures/dark_matter.jpg");
		player->all_guns = (t_gun**)malloc(sizeof(t_gun*) * 3);
		load_guns(player->all_guns);
		run_game(sdl, player, &m, &holder);
	}
	free_all(&player, &sdl, &holder, &m);
	free_data_holder(&holder);
	return (0);
}
