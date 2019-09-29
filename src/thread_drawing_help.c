/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_drawing_help.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:17:00 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:17:03 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

t_screen_inf		fill_inf(t_super_data *super, t_wall cp)
{
	t_screen_inf	inf;

	inf.maxDist = 15;
	inf.vec = (t_vector){super->wall.start.x - super->wall.end.x,
		super->wall.start.y - super->wall.end.y};
	inf.dist = sqrtf(inf.vec.x * inf.vec.x + inf.vec.y * inf.vec.y);
	inf.x = super->start_x;
	inf.end = super->end_x;
	inf.x_lenght = cp.end.x - cp.start.x;
	inf.scale_width_texture = super->wall.texture->w * super->scale_l;
	return (inf);
}

void				calculate_frame(t_screen_inf *inf,
								t_wall cp, t_super_data *super)
{
	inf->ya = (inf->x - cp.start.x) * (super->data->ceil_height)
		/ inf->x_lenght + super->data->ceil_y_s;
	inf->cya = clamp(inf->ya, super->data->ytop[inf->x],
		super->data->ybottom[inf->x]);
	inf->yb = (inf->x - cp.start.x) * (super->data->floor_height)
		/ inf->x_lenght + super->data->floor_y_s;
	inf->cyb = clamp(inf->yb, super->data->ytop[inf->x],
		super->data->ybottom[inf->x]);
	inf->txtx = (super->u0 * ((cp.end.x - inf->x) * cp.end.y) + super->u1
	* ((inf->x - cp.start.x) * cp.start.y)) / ((cp.end.x - inf->x)
	* cp.end.y + (inf->x - cp.start.x) * cp.start.y);
}

void				calculate_neighbours(t_screen_inf *inf,
										t_wall cp, t_draw_data *data)
{
	inf->nya = (inf->x - cp.start.x) * (data->n_ceil_height)
					/ inf->x_lenght + data->n_ceil_y_s;
	inf->nyb = (inf->x - cp.start.x) * (data->n_floor_height)
					/ inf->x_lenght + data->n_floor_y_s;
	inf->n_cya = clamp((inf->x - cp.start.x) * (data->n_ceil_height)
				/ inf->x_lenght + data->n_ceil_y_s,
						data->ytop[inf->x], data->ybottom[inf->x]);
	inf->n_cyb = clamp((inf->x - cp.start.x) * (data->n_floor_height)
				/ inf->x_lenght + data->n_floor_y_s,
						data->ytop[inf->x], data->ybottom[inf->x]);
}

void				render_neighbours(t_screen_inf inf,
									t_super_data *super, t_wall cp)
{
	calculate_neighbours(&inf, cp, super->data);
	if (inf.nya - 1 != inf.ya && inf.cya != inf.n_cya)
	{
		text_line((t_text_inf){inf.x, inf.cya, inf.n_cya - 1,
		init_scaler(inf.cya, (t_point){inf.ya, inf.nya - 1},
		(t_point){0, super->scaleH * 10}), inf.txtx,
		super->sect, super->main_screen,
		super->wall.texture, inf.tex_pos,
		super->scale_l, super->scaleH, super->sect->sector_light});
	}
	if (inf.yb - 1 != inf.nyb && inf.n_cyb != inf.cyb)
		text_line((t_text_inf){inf.x, inf.n_cyb + 1, inf.cyb,
		init_scaler(inf.n_cyb, (t_point){inf.nyb, inf.yb - 1},
		(t_point){0, super->scaleH * 10}), inf.txtx,
		super->sect, super->main_screen, super->wall.texture,
		inf.tex_pos, super->scale_l, super->scaleH,
		super->sect->sector_light});
	super->data->ytop[inf.x] = inf.n_cya;
	super->data->ybottom[inf.x] = inf.n_cyb;
}

void				find_tex_pos(t_screen_inf *inf, t_super_data *super)
{
	inf->mapped = inf->txtx / (inf->scale_width_texture) * inf->dist;
	inf->dx = (inf->dist - inf->mapped) / inf->dist;
	inf->tex_pos = (t_vector){inf->vec.x * inf->dx
	+ super->wall.end.x, inf->vec.y * inf->dx + super->wall.end.y};
}
