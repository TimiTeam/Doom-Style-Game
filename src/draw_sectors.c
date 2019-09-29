/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:15:45 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:15:46 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void				draw_line(t_screen_inf inf, t_super_data *super)
{
	text_line((t_text_inf){inf.x, inf.cya, inf.cyb,
			init_scaler(inf.cya, (t_point){inf.ya, inf.yb},
			(t_point){0, super->wall.texture->h * super->scale_h / 20.0f}),
			inf.txtx, super->sect, super->main_screen,
			super->wall.texture, inf.tex_pos, super->scale_l,
			super->scale_h, super->sect->sector_light});
}

void				draw_ceil(t_screen_inf inf, t_super_data *super)
{
	draw_floor_or_ceil((t_ceil_inf){super->main_screen,
		super->ceil_texture, inf.x, super->data->ytop[inf.x],
		inf.cya, super->data->diff_ceil, super->player,
		super->sect, super->sect->sector_light});
}

void				draw_floor(t_screen_inf inf, t_super_data *super)
{
	draw_floor_or_ceil((t_ceil_inf){super->main_screen,
		super->floor_texture, inf.x, inf.cyb,
		super->data->ybottom[inf.x], super->data->diff_floor,
		super->player, super->sect, super->sect->sector_light});
}

void				*thread_draw_sector(void *param)
{
	t_wall			cp;
	t_screen_inf	inf;
	t_draw_data		*data;
	t_super_data	*super;

	super = (t_super_data*)param;
	cp = super->drawing_line;
	data = super->data;
	inf = fill_inf(super, cp);
	while (inf.x < inf.end)
	{
		calculate_frame(&inf, cp, super);
		draw_ceil(inf, super);
		draw_floor(inf, super);
		find_tex_pos(&inf, super);
		if (super->wall.type == filled_wall)
			draw_line(inf, super);
		else
			render_neighbours(inf, super, cp);
		inf.x++;
	}
	return (NULL);
}

void				draw_sectors(t_sector *sec, t_player *player,
									t_sdl *sdl, t_draw_data data)
{
	int				i;
	int				p;
	t_wall			*w;

	i = -1;
	p = -1;
	if (sec->door && sec->opening && sec->ceil <= sec->floor + 15)
		sec->ceil += 0.2f;
	data.diff_ceil = sec->ceil - data.player_current_height;
	data.diff_floor = sec->floor - data.player_current_height;
	if (data.diff_ceil < 0)
		player->fall = 1;
	while (++i < MAX_PORTALS && (w = sec->only_walls[i]))
		draw_world((t_world){sec, *w, *player, sdl, data, &thread_draw_sector});
	while (++p < MAX_PORTALS && (w = sec->portals[p]))
		draw_world((t_world){sec, *w, *player, sdl, data, &thread_draw_sector});
	quicksort(&sec->items, player);
	draw_sector_items(&sec->items, player, data, sdl->surf);
	draw_projectiles(&sec->projectiles,
				(t_p_n_d){*player, data}, sdl->surf, sec->items);
}
