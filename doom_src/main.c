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

static void			draw_menu(t_sdl *sdl, t_pr *m, SDL_Texture *tex,
								int finish)
{
	SDL_Surface		*end;

	end = NULL;
	if (sdl && m)
	{
		prepare_surf(sdl->ren, sdl->surf);
		render_menu(m, sdl);
		if (finish)
		{
			end = txt_surf(sdl->font, "Well Done",
					(SDL_Color){50, 255, 100, 255});
			draw_image(sdl->surf, end,
			(t_point){(sdl->win_size.x >> 1) - 400,
			(sdl->win_size.y >> 1) - 300},
			(t_point){700, 250});
		}
		tex = SDL_CreateTextureFromSurface(sdl->ren, sdl->surf);
		if (end)
			SDL_FreeSurface(end);
		sdl_render(sdl->ren, tex, NULL, NULL);
		SDL_DestroyTexture(tex);
		SDL_RenderPresent(sdl->ren);
	}
}

static int			run_game(t_sdl *sdl, t_player *player,
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
		if (!player->win && !player->dead &&
			(in_game = menu_hooks(m, holder)) < 0)
			break ;
		draw_menu(sdl, m, tex, holder->f);
		if (in_game > 0 || player->win || player->dead)
		{
			if (player->curr_map != holder->curr_map
				|| player->win || player->dead)
				if (!(ret = load_game(player, holder)) && !holder->f)
					return (error_message("Can't create game"));
			if (!holder->f)
				in_game = game_loop(sdl, player, ret);
		}
	}
	SDL_DestroyTexture(tex);
	return (0);
}

static int			init_holder_data(t_read_holder *holder)
{
	if (!(holder->skyboxes[0] = load_jpg_png("textures/dark_matter.jpg")))
	{
		return (print_error_message("Can't load menu ",
				"textures/dark_matter.jpg"));
	}
	if (!(holder->skyboxes[1] = load_jpg_png("textures/hell.jpg")))
		return (print_error_message("Can't load menu ", "textures/hell.jpg"));
	if (!(holder->skyboxes[2] = load_jpg_png("textures/night.jpg")))
		return (print_error_message("Can't load menu ", "textures/night.jpg"));
	holder->hit_sound = Mix_LoadWAV("sounds/monster_roar.wav");
	holder->roar_sound = Mix_LoadWAV("sounds/monster_bite.wav");
	if ((holder->all_guns = (t_gun**)malloc(sizeof(t_gun*) * 3)))
		if (!load_guns(holder->all_guns))
			return (print_error_message("Problame with loading guns", "exit"));
	return (1);
}

static int			init(t_sdl **sdl, t_pr *m, t_read_holder *holder)
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
	if (!init_holder_data(holder))
		return (print_error_message("Can't load main data", ""));
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
	m.win_h = H;
	m.win_w = W;
	if (init_sound() && read_game_config_file(&holder, "game_info.txt")
	&& init(&sdl, &m, &holder))
	{
		sdl->font = m.font;
		player = new_t_player(3, 3, sdl->win_size);
		player->all_guns = holder.all_guns;
		Mix_PlayChannel(0, player->ambient, -1);
		Mix_Volume(0, 64);
		run_game(sdl, player, &m, &holder);
	}
	free_all(&player, &sdl, &holder, &m);
	free_data_holder(&holder);
	system("leaks -q doom-nukem");
	return (0);
}
