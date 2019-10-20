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
		(t_point){fabsf(super->sect->ceil - super->sect->floor) * 10, 0}),
		inf.txtx, super->sect, super->main_screen,
		super->wall.texture, inf.tex_pos, super->scale_l,
		super->scale_h, super->sect->sector_light, 0});
}

static void			draw_ceil(t_screen_inf inf, t_super_data *super)
{
	draw_floor_or_ceil((t_ceil_inf){super->main_screen,
		super->ceil_texture, inf.x, super->data->ytop[inf.x],
		inf.cya, super->data->diff_ceil, super->player,
		super->sect, super->sect->sector_light,
		.calc_one = super->data->calc_one,
		.calc_two = super->data->ceil_calc});
}

static void			draw_floor(t_screen_inf inf, t_super_data *super)
{
	draw_floor_or_ceil((t_ceil_inf){super->main_screen,
		super->floor_texture, inf.x, inf.cyb,
		super->data->ybottom[inf.x], super->data->diff_floor,
		super->player, super->sect, super->sect->sector_light,
		.calc_one = super->data->calc_one,
		.calc_two = super->data->floor_calc});
}

void				*draw_simple_wall(void *param)
{
	t_wall			cp;
	t_screen_inf	inf;
	t_super_data	*super;

	super = (t_super_data*)param;
	cp = super->drawing_line;
	inf = fill_inf(super, cp);
	while (inf.x < inf.end)
	{
		calculate_frame(&inf, cp, super);
		find_tex_pos(&inf, super);
		draw_line(inf, super);
		inf.x++;
	}
	return (NULL);
}

void				draw_stripes(t_super_data *super, t_screen_inf inf)
{
	if (super->sect->type != uncovered)
		draw_ceil(inf, super);
	else
		draw_skybox(super->main_screen,
		(t_point){inf.x, super->data->ytop[inf.x]}, inf.cya, super->player);
	if (super->sect->floor_visible)
		draw_floor(inf, super);
}
