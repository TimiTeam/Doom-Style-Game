/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:04:56 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:41:16 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					sdl_render_prep(SDL_Renderer *rend)
{
	if (!rend)
		return ;
	SDL_SetRenderDrawColor(rend, 55, 55, 55, 255);
	SDL_RenderClear(rend);
}

void					r_editor(t_sdl *sdl, t_grid *g, t_media *m, t_prog *p)
{
	int					s;

	if (!sdl || !m || !g || !p->redraw)
		return ;
	sdl_render_prep(sdl->rend);
	grid_re(g, m, (s = select_it(1, st_select, 0)), select_it(1, s_select, 0));
	if (s == NORMAL && p->btn_on == ISO_BTN)
		render_grid_iso(m->worlds[m->w], g, p);
	else
		render_grid(m->worlds[m->w], g, p, sdl->mouse);
	render_screen(sdl->rend, p->screen);
	if (p->btn_on != ISO_BTN)
		draw_itms(sdl->rend, m, g, p->t);
	if (s == SEC_EDIT)
		render_item_info(m, sdl, &p->modes[p->m_id], p->t);
	if (s == SEC_EDIT || s == WALL_EDIT)
		render_edit_menu(sdl, m, p, &m->worlds[m->w]);
	render_btns(p, sdl);
	if (s == NORMAL && p->btn_on == PLR_BTN)
		place_player_icons(m->worlds[m->w], g, sdl);
	if (s == WALL_SEARCH && p->btn_on == DOOR_ADD_BTN && p->btn_lit == -1)
		render_cursor(sdl->rend, sdl->mouse, p->t, TXTR_DOOR);
	SDL_RenderPresent(sdl->rend);
	p->redraw = 0;
}

unsigned short			u_editor(t_sdl *sdl, t_grid *grid, t_media *m,
																t_prog *prog)
{
	int					state;
	int					tmp;

	if (!sdl || !m || !grid || !prog)
		return (FAIL);
	if (prog->last != prog->m_id)
		return (mode_change(prog, m, grid, select_it(1, fc_select, -1)));
	if (prog->zoom != 0)
		zoom_grid(prog, sdl->mouse, grid);
	if (prog->move.x || prog->move.y)
		return (move_grid_keys(prog, grid));
	if (select_it(1, st_select, -1) == NORMAL && prog->btn_on == SAVE_BTN)
		return (save_media(m, prog));
	if ((tmp = manage_btn(m, prog, grid, sdl->mouse)) < 2)
		return (tmp);
	if ((state = select_it(1, st_select, -1)) == SEC_SEARCH)
		sec_search_st(prog, sdl->mouse, grid, &m->worlds[m->w]);
	else if (state == WALL_SEARCH && mouse_over(grid->box, sdl->mouse))
		wall_search_st(prog, sdl->mouse, grid, &m->worlds[m->w]);
	else if (state == SEC_EDIT)
		sec_edit_st(prog, sdl->mouse, grid, m);
	else
		normal_st(prog, sdl->mouse, grid, &m->worlds[m->w]);
	return (SUCCESS);
}

unsigned short			btn_down(t_prog *prog, t_vec mouse)
{
	int					state;

	if (prog)
	{
		prog->click = mouse;
		state = select_it(1, st_select, -1);
		if (!(state == SEC_EDIT &&
		(within(prog->btn_lit, F_UP_BTN - 1, C_DOWN_BTN + 1) ||
		within(prog->btn_on, F_UP_BTN - 1, C_DOWN_BTN + 1))))
			return (TRUE);
	}
	return (FALSE);
}

int						i_editor(t_sdl *sdl, t_grid *grid, t_media *media,
		t_prog *p)
{
	SDL_Event			e;

	while (sdl && media && grid && p && SDL_PollEvent(&e))
	{
		SDL_GetMouseState(&sdl->mouse.x, &sdl->mouse.y);
		if (e.type == SDL_QUIT || (e.type == SDL_KEYUP &&
		e.key.keysym.sym == SDLK_ESCAPE))
			return (TRUE);
		else if (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN)
			p->move = get_arrow_input(e.key.keysym.sym, p->move);
		else if (e.type == SDL_MOUSEWHEEL && e.wheel.y)
			p->zoom += e.wheel.y > 0 ? SCROLL_UP : SCROLL_DOWN;
		else if (e.type == SDL_MOUSEBUTTONDOWN && btn_down(p, sdl->mouse))
			break ;
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			if (select_it(1, st_select, -1) == NORMAL && p->btn_lit == BACK_BTN)
				return (return_to_levels(p, media));
			if (select_it(1, st_select, -1) == SEC_EDIT && within(p->btn_lit,\
			F_UP_BTN - 1, C_DOWN_BTN + 1))
				turn_btns_off(p);
			p->click = (t_vec){ 0, 0 };
		}
	}
	return (FALSE);
}
