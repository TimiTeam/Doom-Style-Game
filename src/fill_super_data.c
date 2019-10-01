/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_super_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:16:11 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:16:12 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void			fill_super_data(t_super_data *super, t_sector *sec,
									t_draw_data *data, t_wall wall)
{
	super->data = data;
	super->drawing_line = wall;
	super->floor_texture = sec->floor_tex;
	super->ceil_texture = sec->ceil_tex;
}

void			fill_super_data_2(t_super_data *super,
							t_draw_data data, int step, int i)
{
	super->start_x = data.start + (step * i);
	super->end_x = i + 1 == THREADS ? data.end : super->start_x + step;
}

void			fill_super_data_3(t_super_data *super,
				t_sector *sec, t_player player, t_sdl *sdl)
{
	super->main_screen = sdl->surf;
	super->player = player;
	super->sect = sec;
	super->scale_h = sec->ceil - sec->floor;
}
