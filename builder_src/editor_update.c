/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:51:56 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:41:46 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

unsigned short			save_media(t_media *media, t_prog *prog)
{
	if (!media || !prog || !prog->modes || !prog->modes[prog->m_id].btn\
	|| rewrite_media(media) == FAIL)
		return (FAIL);
	prog->btn_on = DRAG_BTN;
	prog->modes[prog->m_id].btn[prog->btn_on].vis_lit_on[2] = TRUE;
	prog->modes[prog->m_id].btn[SAVE_BTN].vis_lit_on[2] = FALSE;
	return (SUCCESS);
}

unsigned short			open_level(t_media *media, t_prog *prog, t_grid *grid)
{
	int					w;

	if (!media || !prog || !grid || \
	!within(media->w, -1, media->n_worlds + 1))
		return (FAIL);
	w = media->w;
	clean_grid(grid);
	if (w == media->n_worlds)
	{
		if (add_world(&media->worlds, media->n_worlds, media->extensions[0], \
		media->paths[0]) == FAIL)
			return (FAIL);
		media->n_worlds++;
	}
	else if (media->worlds[w].n_s > 0)
		zoom_to_box(grid, media->worlds[media->w].vecs, \
		media->worlds[media->w].n_v);
	fill_grid(media->worlds[w].n_v, media->worlds[w].vecs, grid);
	upd_sec(media->worlds[w].sec, media->worlds[w].walls, \
	media->worlds[w].vecs, media->worlds[w].n_s);
	prog->redraw = 1;
	return (SUCCESS);
}

unsigned short			mode_change(t_prog *prog, t_media *media, t_grid *grid,\
int fl_ceil)
{
	if (!prog || !media || !grid)
		return (FAIL);
	select_it(0, last_select, prog->last == mode_levels ? -2 : \
	select_it(1, last_select, 1));
	if (prog->last == mode_levels)
	{
		prog->last = prog->m_id;
		prog->btn_on = -1;
		prog->btn_lit = -1;
		return (open_level(media, prog, grid));
	}
	if (prog->last == mode_textures)
		edit_texture(fl_ceil, media->n_t, media->txtr, \
		&media->worlds[media->w]);
	if (prog->last == mode_sel_item)
		edit_item_name(media->n_itf, media->it_f, \
		&media->worlds[media->w]);
	prog->last = prog->m_id;
	return (SUCCESS);
}

unsigned short			return_to_levels(t_prog *prog, t_media *media)
{
	if (prog && media && prog->modes)
	{
		prog->last = prog->m_id;
		prog->m_id = mode_levels;
		turn_btns_off(prog);
		prog->btn_lit = -1;
		media->w = -1;
		refresh_level_list(media, &prog->modes[mode_levels]);
		return (FALSE);
	}
	return (TRUE);
}
