/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:54:35 by atabala           #+#    #+#             */
/*   Updated: 2019/09/18 14:54:37 by atabala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_head.h"

void	readdirec(t_pr *m, t_sdl *sdl, char **maps)
{
	//m->dir = opendir("./maps");
	//m->maps = (char**)malloc(sizeof(char*) * 4096);
	m->maps = maps;
	// while ((m->dent = readdir(m->dir)) != NULL)
	// {
	// 	if (m->i > 1)
	// 	{
	// 		m->maps[m->i] = (char*)malloc(sizeof(char*) * 4096);
	// 		m->maps[m->i] = m->dent->d_name;
	// 		printf("Loaded %s\n", m->dent->d_name);
	// 	}
	// 	m->i++;
	// }
	m->maxi = m->i - 1;
	m->i = 0;
	set_text(m, m->maps[m->i], sdl);
}

// void	renderallshit(t_pr *m)
// {
// 	SDL_RenderClear(m->rend);
// 	SDL_RenderCopy(m->rend, m->background, NULL, NULL);
// 	SDL_RenderCopy(m->rend, m->logo, NULL, &m->logo_rect);
// 	SDL_RenderCopy(m->rend, m->play_button, NULL, &m->play_rect);
// 	SDL_RenderCopy(m->rend, m->choose_level_button, NULL,
// 		&m->choose_level_rect);
// 	SDL_RenderCopy(m->rend, m->font_texture, NULL, &m->font_rect);
// 	SDL_RenderCopy(m->rend, m->exit_button, NULL, &m->exit_rect);
// 	SDL_RenderPresent(m->rend);
// }

// void	load_textures(t_pr *m)
// {
// 	TTF_Init();
// 	m->done = SDL_FALSE;
// 	if (!(m->texture = IMG_Load("textures/background1.jpg")))
// 	m->background = SDL_CreateTextureFromSurface(m->rend, m->texture);
// 	m->texture = IMG_Load("textures/play_button.png");
// 	m->play_button = SDL_CreateTextureFromSurface(m->rend, m->texture);
// 	m->texture = IMG_Load("textures/exit_button.png");
// 	m->exit_button = SDL_CreateTextureFromSurface(m->rend, m->texture);
// 	m->texture = IMG_Load("textures/logo.png");
// 	m->logo = SDL_CreateTextureFromSurface(m->rend, m->texture);
// 	m->texture = IMG_Load("textures/choose_level_button.png");
// 	m->choose_level_button = SDL_CreateTextureFromSurface(m->rend, m->texture);
// 	m->font = TTF_OpenFont("amazdoom/AmazDooMLeft.ttf", 256);
// 	m->font_color.r = 255;
// 	m->font_color.g = 255;
// 	m->font_color.b = 255;
// 	m->font_color.a = 255;
// }
