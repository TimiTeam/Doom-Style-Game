/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_btn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 19:53:32 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/07 18:43:26 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					render_btn(t_btn *btn, t_sdl *sdl, SDL_Texture **t)
{
	if (!btn || !sdl || !sdl->rend || !t)
		return ;
	if (btn->vis_lit_on[1] == FALSE && btn->vis_lit_on[2] == FALSE &&
	within(btn->reg_i, -1, N_TXTR) && t[btn->reg_i])
		SDL_RenderCopy(sdl->rend, t[btn->reg_i], NULL, &(SDL_Rect){ btn->box.x,\
		btn->box.y, btn->box.w, btn->box.h });
	else if ((btn->vis_lit_on[1] == TRUE || btn->vis_lit_on[2] == TRUE) &&
	within(btn->lit_i, -1, N_TXTR) && t[btn->lit_i])
	{
		SDL_RenderCopy(sdl->rend, t[btn->lit_i], NULL,\
		&(SDL_Rect){ btn->box.x, btn->box.y, btn->box.w, btn->box.h });
	}
	if (btn->text)
	{
		if (btn->vis_lit_on[1] == TRUE)
			write_txt(btn->text, sdl, (t_txtb){ btn->box, TRUE, LIT_COLOR });
		else
			write_txt(btn->text, sdl, (t_txtb){ btn->box, TRUE, \
			btn->text_color });
	}
}

void					render_btn_big(t_btn *btn, t_sdl *sdl, SDL_Texture **t)
{
	if (!btn || !sdl || !sdl->rend || !t)
		return ;
	if (within(btn->reg_i, -1, N_TXTR) && t[btn->reg_i])
		SDL_RenderCopy(sdl->rend, t[btn->reg_i], NULL, &(SDL_Rect){ btn->box.x,\
		btn->box.y - btn->box.h * 0.3, btn->box.w * 1.3, btn->box.h * 1.3 });
}

void					render_btn2(t_btn *btn, t_sdl *sdl, SDL_Texture **t)
{
	if (!btn || !sdl || !sdl->rend || !t)
		return ;
	if (btn->vis_lit_on[1] == FALSE && btn->vis_lit_on[2] == FALSE &&
	btn->fake_lit == FALSE &&
		within(btn->reg_i, -1, N_TXTR) && t[btn->reg_i])
		SDL_RenderCopy(sdl->rend, t[btn->reg_i], NULL, &(SDL_Rect){ btn->box.x,\
		btn->box.y, btn->box.w, btn->box.h });
	else if ((btn->vis_lit_on[1] == TRUE || btn->vis_lit_on[2] == TRUE ||
	btn->fake_lit == TRUE) && within(btn->lit_i, -1, N_TXTR) && t[btn->lit_i])
	{
		SDL_RenderCopy(sdl->rend, t[btn->lit_i], NULL,\
		&(SDL_Rect){ btn->box.x, btn->box.y, btn->box.w, btn->box.h });
	}
	if (btn->text)
	{
		if (btn->vis_lit_on[1] == TRUE)
			write_txt(btn->text, sdl, (t_txtb){ btn->box, TRUE, LIT_COLOR });
		else
			write_txt(btn->text, sdl, (t_txtb){ btn->box, TRUE, \
			btn->text_color });
	}
}

void					render_btns(t_prog *prog, t_sdl *sdl)
{
	short				i;
	short				state;

	i = 0;
	state = select_it(1, st_select, -1);
	if (!prog || !prog->modes[prog->m_id].btn || !sdl)
		return ;
	while (i < prog->modes[prog->m_id].n_btn)
	{
		if (prog->modes[prog->m_id].btn[i].vis_lit_on[0] == TRUE)
		{
			if (prog->m_id == mode_editor &&
			(prog->modes[prog->m_id].btn[i].vis_lit_on[1] ||
			prog->modes[prog->m_id].btn[i].vis_lit_on[2]) &&
			state == SEC_EDIT && i > B_ITEM_DEL && i < B_NORM)
				render_btn_big(&prog->modes[prog->m_id].btn[i], sdl, prog->t);
			else if (prog->m_id == mode_editor && state == SEC_EDIT &&
			i >= B_NORM)
				render_btn2(&prog->modes[prog->m_id].btn[i], sdl, prog->t);
			else
				render_btn(&prog->modes[prog->m_id].btn[i], sdl, prog->t);
		}
		i++;
	}
}
