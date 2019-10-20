/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:33:38 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:40:45 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					place_player_icons(t_world world, t_grid *grid, \
t_sdl *sdl)
{
	t_vec				node;
	t_txtb				tb;

	node.x = (int)(grid->box.x + world.p_start.x * grid->scl);
	node.y = (int)(grid->box.y + world.p_start.y * grid->scl);
	tb = (t_txtb){ (t_rec){ node.x - 120, node.y + 5, 240, 50 }, TRUE, WHITE };
	write_txt("START", sdl, tb);
	node.x = (int)(grid->box.x + world.p_end.x * grid->scl);
	node.y = (int)(grid->box.y + world.p_end.y * grid->scl);
	tb = (t_txtb){ (t_rec){ node.x - 120, node.y + 5, 240, 50 }, TRUE, WHITE };
	write_txt("END", sdl, tb);
}

char					*write_typ(int type)
{
	static char			name[TOTAL_TYPES][25] = {	"TYPE: coin", \
													"TYPE: key", \
													"TYPE: object", \
													"TYPE: enemy", \
													"TYPE: super_bonus", \
													"TYPE: health", \
													"TYPE: ammo", \
													"TYPE: weapon", \
													"TYPE: light" };

	if (within(type, -1, TOTAL_TYPES))
		return (name[type]);
	return (NULL);
}

void					render_item_info(t_media *m, t_sdl *sdl, t_mode *mod,
		SDL_Texture **t)
{
	int					s;
	int					id;
	t_rec				b;
	char				*tmp;

	if (!m || !mod || !mod->btn || !m->it_f || B_ITEM_DEL >= mod->n_btn)
		return ;
	mod->btn[B_ITEM_EDIT].vis_lit_on[0] = FALSE;
	mod->btn[B_ITEM_DEL].vis_lit_on[0] = FALSE;
	if (sdl && within((s = select_it(1, s_select, 1)), -1, m->worlds[m->w\
	].n_s) && within((id = select_it(1, i_select, 1)), -1, m->worlds[m->w\
	].sec[s].n_it) && within((id = m->worlds[m->w].sec[s].items[id].id), -1,\
	m->n_itf) && within(TXTR_RECY, -1, N_TXTR) && t[TXTR_RECY] &&
	(tmp = get_full_p(m->it_f[id].name, "\"", "Name: \"")))
	{
		rend_box((b = (t_rec){ 20, 730, 350, 48 }), t[TXTR_RECY], sdl->rend);
		write_txt(write_typ(m->it_f[id].type), sdl, (t_txtb){ b, 0, ED_CLR });
		rend_box((b = (t_rec){ 20, 790, 350, 50 }), t[TXTR_RECY], sdl->rend);
		write_txt(tmp, sdl, (t_txtb){ b, 0, ED_CLR });
		free(tmp);
		mod->btn[B_ITEM_EDIT].box = (t_rec){ b.x + b.w, b.y, b.h, b.h };
		mod->btn[B_ITEM_DEL].box = (t_rec){ b.x + b.w + b.h, b.y, b.h, b.h };
		mod->btn[B_ITEM_EDIT].vis_lit_on[0] = TRUE;
		mod->btn[B_ITEM_DEL].vis_lit_on[0] = TRUE;
	}
}

void					render_cursor(SDL_Renderer *rend, t_vec mouse,
		SDL_Texture **t, int txtr_id)
{
	SDL_Rect			rect;

	if (rend && t && within(txtr_id, -1, N_TXTR))
	{
		rect = (SDL_Rect){ mouse.x, mouse.y, 30, 30 };
		SDL_RenderCopy(rend, t[txtr_id], NULL, &rect);
	}
}
