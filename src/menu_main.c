/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:55:25 by atabala           #+#    #+#             */
/*   Updated: 2019/09/18 14:55:26 by atabala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void			set_text(t_pr *m, char *text)
{
	SDL_Color color = {255, 255, 255, 100};
	m->font_texture = TTF_RenderText_Blended(m->font, text, color);
}

SDL_Rect		change_size(SDL_Rect rect)
{
	rect.x -= 60;
	rect.y -= 20;
	rect.w += 120;
	rect.h += 40;
	return (rect);
}

SDL_Rect		reset_size(SDL_Rect rect)
{
	rect.x += 60;
	rect.y += 20;
	rect.w -= 120;
	rect.h -= 40;
	return (rect);
}

void			initialize_sdl_win(t_pr *m)
{
	m->play_rect.x = m->win_w / 2 - 250;
	m->play_rect.y = m->win_h / 2 - 150;
	m->play_rect.w = 500;
	m->play_rect.h = 170;
	m->exit_rect.x = m->win_w / 2 - 250;
	m->exit_rect.y = m->win_h / 2 + 150;
	m->exit_rect.w = 500;
	m->exit_rect.h = 170;
	m->logo_rect.w = 900;
	m->logo_rect.h = 450;
	m->logo_rect.x = m->win_w / 2 - m->logo_rect.w / 2;
	m->logo_rect.y = -80;
	m->choose_level_rect.x = m->win_w / 2 - 250;
	m->choose_level_rect.y = m->win_h / 2;
	m->choose_level_rect.w = 500;
	m->choose_level_rect.h = 170;
	m->font_rect.x = m->choose_level_rect.x + 75;
	m->font_rect.y = m->choose_level_rect.y + 120;
	m->font_rect.w = 350;
	m->font_rect.h = 70;
	m->play_rect = change_size(m->play_rect);
	m->sw = 0;
}
