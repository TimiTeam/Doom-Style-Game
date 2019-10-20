/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:32:09 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:35:51 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					render_defaults(t_sdl *sdl, t_media *media)
{
	int					i;
	t_rec				tmp;
	char				*str;

	if (!sdl || !media)
		return ;
	i = -1;
	while (++i < 5)
	{
		tmp = settings_boxes(3, i + 1);
		tmp.x -= tmp.w * 1.1;
		SDL_RenderCopy(sdl->rend, media->txtr[default_texture(1, i, -1)].sdl_t,\
		NULL, &(SDL_Rect){ tmp.x, tmp.y, tmp.w, tmp.h });
	}
	while (i < 7)
	{
		tmp = settings_boxes(2, i++);
		tmp.x += tmp.w * 0.8;
		tmp.w = tmp.h;
		if ((str = ft_itoa(default_heights(1, i - 6, -1))))
		{
			write_txt(str, sdl, (t_txtb){ tmp, TRUE, ED_CLR });
			free(str);
		}
	}
}

void					render_settings_layout(t_sdl *sdl, t_prog *prog)
{
	int					i;
	static char			h[3][20] = { "DEFAULT VALUES", "TEXTURES", "HEIGHTS" };
	static char			v[7][20] = { "wall", "floor", "ceiling", "door", \
	"transparent wall", "floor", "ceiling" };
	t_rec				tmp;

	tmp = settings_boxes(1, 0);
	SDL_RenderCopy(sdl->rend, prog->t[TXTR_PANEL_GR], NULL, \
	&(SDL_Rect){ tmp.x, tmp.y, tmp.w, tmp.h });
	tmp = settings_boxes(1, 1);
	SDL_RenderCopy(sdl->rend, prog->t[TXTR_PANEL_GR], NULL, \
	&(SDL_Rect){ tmp.x, tmp.y, tmp.w, tmp.h });
	i = -1;
	while (++i < 3)
		write_txt(h[i], sdl, (t_txtb){ settings_boxes(0, i), FALSE, WHITE });
	i = -1;
	while (++i < 7)
		write_txt(v[i], sdl, (t_txtb){ settings_boxes(2, i), FALSE, ED_CLR });
}

void					r_settings(t_sdl *sdl, t_grid *grid, t_media *media, \
t_prog *prog)
{
	if (!sdl || !grid || !media || !prog)
		return ;
	SDL_SetRenderDrawColor(sdl->rend, 55, 55, 55, 255);
	SDL_RenderClear(sdl->rend);
	render_settings_layout(sdl, prog);
	render_defaults(sdl, media);
	render_btns(prog, sdl);
	SDL_RenderPresent(sdl->rend);
}

unsigned short			u_settings(t_sdl *sdl, t_grid *grid, t_media *media, \
t_prog *prog)
{
	int					tmp2;

	if (!sdl || !grid || !media || !prog->modes || !prog->modes[prog->m_id].btn)
		return (FAIL);
	if (prog->last == mode_textures)
		edit_def_texture(media->n_t, media->txtr);
	if (prog->m_id != prog->last)
	{
		prog->click = (t_vec){ 0, 0 };
		prog->btn_lit = -1;
		prog->last = prog->m_id;
		return (SUCCESS);
	}
	if ((tmp2 = manage_btn(media, prog, grid, sdl->mouse)) < 2)
		return (tmp2);
	prog->last = prog->m_id;
	prog->btn_lit = -1;
	return (SUCCESS);
}

int						i_settings(t_sdl *sdl, t_grid *grid, t_media *media, \
t_prog *prog)
{
	int					quit;
	SDL_Event			event;

	quit = FALSE;
	if (!sdl || !media || !grid || !prog)
		return (TRUE);
	while (SDL_PollEvent(&event))
	{
		SDL_GetMouseState(&sdl->mouse.x, &sdl->mouse.y);
		if (event.type == SDL_QUIT || (event.type == SDL_KEYUP &&
		event.key.keysym.sym == SDLK_ESCAPE))
			return (TRUE);
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			prog->click = sdl->mouse;
		else if (event.type == SDL_MOUSEBUTTONUP && prog->btn_on == S_BACK_BTN)
		{
			turn_btns_off(prog);
			prog->last = prog->m_id;
			prog->m_id = mode_editor;
			prog->click = (t_vec){ 0, 0 };
			return (quit);
		}
	}
	return (quit);
}
