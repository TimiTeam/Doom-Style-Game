/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:00:15 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:41:16 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					r_levels(t_sdl *sdl, t_grid *grid, t_media *media,
		t_prog *prog)
{
	char				*input;

	if (!sdl || !sdl->rend || !grid || !media || !prog)
		return ;
	SDL_SetRenderDrawColor(sdl->rend, 55, 55, 55, 255);
	SDL_RenderClear(sdl->rend);
	render_btns(prog, sdl);
	if (select_it(1, st_select, -1) == INP)
	{
		input = get_input(NULL, 0);
		if (input)
			write_txt(input, sdl, (t_txtb){ (t_rec){ W_W / 4, W_H / 12, \
			W_W / 2, W_H / 10 }, TRUE, WHITE });
	}
	SDL_RenderPresent(sdl->rend);
}

int						get_w(int btn_id, int n_worlds, int *edit_del)
{
	if (!edit_del)
		return (-1);
	if (n_worlds % 2 == 0)
	{
		if (btn_id % 2 == 0)
		{
			*edit_del = 1;
			return ((btn_id - n_worlds - 2) / 2);
		}
		*edit_del = 0;
		return ((btn_id - n_worlds - 1) / 2);
	}
	else
	{
		if (btn_id % 2 == 0)
		{
			*edit_del = 0;
			return ((btn_id - n_worlds - 1) / 2);
		}
		*edit_del = 1;
		return ((btn_id - n_worlds - 2) / 2);
	}
}

unsigned short			rename_world(t_media *m, int world, t_prog *prog)
{
	char				*new;
	char				*tmp;

	if (!m || !prog || !m->worlds)
		return (FAIL);
	if (!within(select_it(1, world_select, -1), -1, m->n_worlds))
		return (SUCCESS);
	new = get_input(NULL, 0);
	if (new && (tmp = get_full_p(new, m->extensions[0], m->paths[0])))
	{
		if (my_rename(m->worlds[world].full_p, tmp) == SUCCESS)
		{
			if (m->worlds[world].name)
				free(m->worlds[world].name);
			if (m->worlds[world].full_p)
				free(m->worlds[world].full_p);
			m->worlds[world].name = ft_strdup(new);
			m->worlds[world].full_p = get_full_p(new, m->extensions[0],
					m->paths[0]);
		}
		free(tmp);
	}
	select_it(0, world_select, -1);
	refresh_level_list(m, &prog->modes[prog->m_id]);
	return (SUCCESS);
}

unsigned short			u_levels(t_sdl *sdl, t_grid *grid, t_media *m,
		t_prog *prog)
{
	int					w;
	int					ed_del;
	int					tmp2;

	if (!sdl || !grid || !m || !prog->modes)
		return (FAIL);
	if (select_it(1, st_select, -1) != NORMAL)
		return (SUCCESS);
	if ((tmp2 = manage_btn(m, prog, grid, sdl->mouse)) < 2)
		return (tmp2);
	if (within(prog->btn_on, m->n_worlds, prog->modes[prog->m_id].n_btn) &&
	within((w = get_w(prog->btn_on, m->n_worlds, &ed_del)), -1, m->n_worlds))
	{
		if (ed_del == 1)
		{
			delete_world(m, w);
			select_it(0, world_select, -1);
			refresh_level_list(m, &prog->modes[prog->m_id]);
		}
		else if (get_input(m->worlds[(select_it(0, world_select, w))].name, 0))
			select_it(0, st_select, INP);
		turn_btns_off(prog);
		return (SUCCESS);
	}
	return (rename_world(m, select_it(1, world_select, -1), prog));
}

int						i_levels(t_sdl *sdl, t_grid *grid, t_media *med,
		t_prog *prog)
{
	int					quit;
	SDL_Event			e;

	quit = sdl && grid && med && prog ? FALSE : TRUE;
	while (SDL_PollEvent(&e) && quit == FALSE)
	{
		SDL_GetMouseState(&sdl->mouse.x, &sdl->mouse.y);
		if (e.type == SDL_QUIT || (e.type == SDL_KEYUP &&
		e.key.keysym.sym == SDLK_ESCAPE))
			quit = TRUE;
		else if (e.type == SDL_KEYUP)
		{
			if (ft_isalnum(e.key.keysym.sym) || e.key.keysym.sym == 8)
				get_input(NULL, e.key.keysym.sym);
			if (e.key.keysym.sym == SDLK_RETURN && select_it(1, st_select, INP))
				select_it(0, st_select, NORMAL);
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
			prog->click = sdl->mouse;
		else if (e.type == SDL_MOUSEBUTTONUP &&
		within((med->w = prog->btn_on), -1, med->n_worlds + 1))
			switch_mode(prog, mode_editor, NORMAL);
	}
	return (quit);
}
