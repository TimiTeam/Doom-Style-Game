/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:09:35 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 20:09:37 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					get_txtr_btn_boxes(t_btn *btn, int n_t, int scroll)
{
	static char			init = FALSE;
	static t_rec		box = (t_rec){ 0, 0, 0, 0 };
	static t_rec		btn_box = (t_rec){ 0, 0, 0, 0 };
	static int			rows = 0;
	int					r_c_i[3];

	if (init == FALSE || scroll)
	{
		rows = n_t / 5;
		box = (t_rec){ W_W * 0.05, W_H * 0.05 + scroll * 25, W_W * 0.9, \
		W_W * 0.9 * rows };
		btn_box = (t_rec){ box.x, box.y, box.w / 5, box.w / 5 };
		init = TRUE;
	}
	if (!btn)
		return ;
	ft_memset(r_c_i, 0, sizeof(int) * 3);
	while (r_c_i[2] < n_t)
	{
		btn[r_c_i[2]++].box = (t_rec){ btn_box.x + btn_box.w * r_c_i[1], \
		btn_box.y + btn_box.h * r_c_i[0], btn_box.w, btn_box.h };
		if (r_c_i[1] == 4)
			r_c_i[0]++;
		r_c_i[1] = (r_c_i[1] + 1) % 5;
	}
}

void					render_texture_icons(t_btn *btn, t_sdl *sdl, int n_btn,\
t_texture *txtr)
{
	int					i;
	t_rec				text;
	SDL_Rect			rect;

	if (!btn || n_btn < 1 || !sdl || !txtr)
		return ;
	i = -1;
	while (++i < n_btn)
	{
		text = (t_rec){ btn[i].box.x + btn[i].box.w * 0.1, btn[i].box.y \
		+ btn[i].box.h * 0.03,\
		btn[i].box.w * 0.8, btn[i].box.h * 0.14 };
		text.w = clamp(text.h * 0.4 * ft_strlen(txtr[i].name), 1, text.w);
		rect = (SDL_Rect){ btn[i].box.x + btn[i].box.w * 0.1, \
		btn[i].box.y + btn[i].box.h * 0.15, btn[i].box.w * 0.8, btn[i].box.h * \
		0.8 };
		if (txtr[i].sdl_t)
			SDL_RenderCopy(sdl->rend, txtr[i].sdl_t, NULL, &rect);
		if (txtr[i].name)
			write_txt(txtr[i].name, sdl, (t_txtb){ text, TRUE, ED_CLR });
	}
}

void					r_textures(t_sdl *sdl, t_grid *grid, t_media *media, \
t_prog *prog)
{
	if (!sdl || !media || !grid || prog->redraw == 0)
		return ;
	SDL_SetRenderDrawColor(sdl->rend, 55, 55, 55, 255);
	SDL_RenderClear(sdl->rend);
	render_btns(prog, sdl);
	render_texture_icons(prog->modes[prog->m_id].btn, sdl, \
	prog->modes[prog->m_id].n_btn, media->txtr);
	SDL_RenderPresent(sdl->rend);
	prog->redraw = 1;
}

unsigned short			u_textures(t_sdl *sdl, t_grid *grid, t_media *media,\
t_prog *prog)
{
	if (!sdl || !grid || !media || !prog->modes || !prog->modes[prog->m_id].btn)
		return (FAIL);
	get_txtr_btn_boxes(prog->modes[prog->m_id].btn, \
	prog->modes[prog->m_id].n_btn, prog->zoom);
	if (btn_light(sdl->mouse, prog->modes[prog->m_id].btn, \
	prog->modes[prog->m_id].n_btn, prog) == SUCCESS)
		return (SUCCESS);
	prog->btn_lit = -1;
	return (SUCCESS);
}

int						i_textures(t_sdl *sdl, t_grid *grid, t_media *media,\
t_prog *prog)
{
	SDL_Event			event;

	if (!sdl || !media || !grid)
		return (TRUE);
	while (SDL_PollEvent(&event))
	{
		SDL_GetMouseState(&sdl->mouse.x, &sdl->mouse.y);
		if (event.type == SDL_QUIT || (event.type == SDL_KEYUP &&
		event.key.keysym.sym == SDLK_ESCAPE))
			return (TRUE);
		else if (event.type == SDL_MOUSEWHEEL && event.wheel.y)
			prog->zoom += event.wheel.y > 0 ? SCROLL_UP : SCROLL_DOWN;
		if (event.type == SDL_MOUSEBUTTONDOWN && prog->btn_lit != -1)
		{
			select_it(0, t_select, prog->btn_lit);
			turn_btns_off(prog);
			prog->zoom = 0;
			swap_ints(&prog->last, &prog->m_id);
			prog->click = (t_vec){ 0, 0 };
			break ;
		}
	}
	return (FALSE);
}
