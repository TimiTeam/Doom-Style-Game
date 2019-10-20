/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:10:58 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/15 14:08:46 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					switch_mode(t_prog *prog, int new_m_id, int new_state)
{
	if (prog)
	{
		prog->modes[prog->m_id].btn[prog->btn_on].vis_lit_on[2] = FALSE;
		prog->last = prog->m_id;
		prog->m_id = new_m_id;
		prog->btn_lit = -1;
		select_it(0, st_select, new_state);
		prog->click = (t_vec){ 0, 0 };
	}
}

void					free_modes(t_mode *modes)
{
	int					i;

	if (!modes)
		return ;
	i = -1;
	while (++i < N_MODES)
	{
		if (modes[i].btn)
			free_btn(modes[i].btn, modes[i].n_btn);
	}
	free(modes);
	modes = NULL;
}

void					refresh_level_list(t_media *media, t_mode *mode)
{
	if (!media || !mode)
		return ;
	if (mode->n_btn == media->n_worlds + 1)
		return ;
	if (mode->btn)
		free_btn(mode->btn, mode->n_btn);
	mode->n_btn = (media->n_worlds + 1) * 3;
	mode->btn = init_btn(mode->n_btn);
	if (!mode->btn)
		return ;
	levels_btn(mode->btn, media->worlds, media->n_worlds);
	default_texture(0, -1, -1);
	default_heights(0, -1, -1);
}

void					get_loop_fun(t_mode *modes, t_media *media)
{
	if (!modes || !media)
		return ;
	modes[mode_main_menu].input = &i_mainmenu;
	modes[mode_main_menu].update = &u_mainmenu;
	modes[mode_main_menu].render = &r_mainmenu;
	modes[mode_levels].input = &i_levels;
	modes[mode_levels].update = &u_levels;
	modes[mode_levels].render = &r_levels;
	modes[mode_editor].input = &i_editor;
	modes[mode_editor].update = &u_editor;
	modes[mode_editor].render = &r_editor;
	modes[mode_textures].input = &i_textures;
	modes[mode_textures].update = &u_textures;
	modes[mode_textures].render = &r_textures;
	modes[mode_sel_item].input = &i_sel_item;
	modes[mode_sel_item].update = &u_sel_item;
	modes[mode_sel_item].render = &r_sel_item;
	modes[mode_settings].input = &i_settings;
	modes[mode_settings].update = &u_settings;
	modes[mode_settings].render = &r_settings;
	modes[mode_main_menu].n_btn = N_MM_BTNS;
	modes[mode_textures].n_btn = media->n_t;
	modes[mode_levels].n_btn = (media->n_worlds + 1) * 3;
	modes[mode_editor].n_btn = TOT_EDIT_BTNS;
	modes[mode_sel_item].n_btn = media->n_itf;
}

unsigned short			init_modes(t_media *media, t_prog *prog)
{
	int					i;

	if (!media || !prog || !(prog->modes = \
	(t_mode *)ft_memalloc(sizeof(t_mode) * N_MODES)))
		return (FAIL);
	ft_bzero(prog->modes, sizeof(t_mode) * N_MODES);
	get_loop_fun(prog->modes, media);
	prog->modes[mode_settings].n_btn = 10;
	i = -1;
	while (++i < N_MODES)
	{
		prog->modes[i].btn = NULL;
		if (prog->modes[i].n_btn > 0 && !(prog->modes[i].btn = \
		init_btn(prog->modes[i].n_btn)))
			return (FAIL);
	}
	main_menu_btn(prog->modes[mode_main_menu].btn);
	levels_btn(prog->modes[mode_levels].btn, media->worlds, media->n_worlds);
	default_texture(0, -1, -1);
	default_heights(0, -1, -1);
	textures_btn(prog->modes[mode_textures].btn, media->n_t);
	sel_item_btn(prog->modes[mode_sel_item].btn, media->it_f, media->n_itf);
	settings_btn(prog->modes[mode_settings].btn, \
	prog->modes[mode_settings].n_btn);
	return (SUCCESS);
}
