/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_and_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:15:27 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:15:29 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

int				calc_floor_ceil(unsigned half_win_size_y,
			float floor_or_ceil_diff, float scale_y)
{
	return (half_win_size_y - floor_or_ceil_diff * scale_y);
}

void			apply_ceil_light(t_ceil_inf inf, t_light *light)
{
	int			i;
	float		dist_to_light;
	Uint8		r;
	Uint8		g;
	Uint8		b;

	i = -1;
	while (++i < MAX_LIGHT_SRC && (light = inf.light_source[i]))
	{
		dist_to_light = len_between_points(light->pos,
								(t_vector){inf.mapx, inf.mapz, 0});
		if (dist_to_light < light->max_dist)
			inf.brightness += 1.0f - CLAMP(dist_to_light, 0, light->max_dist)
															/ light->max_dist;
	}
	SDL_GetRGB(get_pixel(inf.src, inf.tx % inf.src->w, inf.txtz % inf.src->h),
												inf.src->format, &r, &g, &b);
	put_pixel(inf.dst, inf.x, inf.y, SDL_MapRGB(inf.src->format,
						MIN(r * inf.brightness, 255),
						MIN(g * inf.brightness, 255),
						MIN(b * inf.brightness, 255)));
}

void			draw_floor_or_ceil(t_ceil_inf inf)
{
	float		tmp;
	t_light		*light;

	if (!inf.dst || !inf.src || inf.src->w == 0 || inf.src->h == 0)
		return ;
	light = NULL;
	while (inf.y < inf.end_y)
	{
		inf.mapz = inf.calc_two
		/ ((inf.player.half_win_size.y - inf.y) - inf.calc_one);
		inf.mapx = inf.mapz *
		(inf.player.half_win_size.x - inf.x) / (inf.player.m_hfov * W);
		tmp = inf.mapx;
		inf.mapx = inf.mapz * inf.player.cos_angl
		+ tmp * inf.player.sin_angl + inf.player.pos.x;
		inf.mapz = inf.mapz * inf.player.sin_angl
		- tmp * inf.player.cos_angl + inf.player.pos.y;
		inf.tx = inf.mapx * 50;
		inf.txtz = inf.mapz * 50;
		inf.brightness = 0.3f;
		apply_ceil_light(inf, light);
		++inf.y;
	}
}

void			floor_and_ceil_calculation(t_draw_data *data,
			t_player player, t_wall line, t_vector scale)
{
	data->ceil_y_s = calc_floor_ceil(player.half_win_size.y,
		YAW(data->diff_ceil, line.start.y), scale.x);
	data->ceil_y_e = calc_floor_ceil(player.half_win_size.y,
		YAW(data->diff_ceil, line.end.y), scale.y);
	data->floor_y_s = calc_floor_ceil(player.half_win_size.y,
		YAW(data->diff_floor, line.start.y), scale.x);
	data->floor_y_e = calc_floor_ceil(player.half_win_size.y,
		YAW(data->diff_floor, line.end.y), scale.y);
	data->floor_height = data->floor_y_e - data->floor_y_s;
	data->ceil_height = data->ceil_y_e - data->ceil_y_s;
}

void			neighbour_calculation(t_draw_data *data, t_n n)
{
	t_player player;

	player = n.player;
	data->n_ceil_y_s = calc_floor_ceil(n.player.half_win_size.y,
			YAW(MIN(n.wall.sectors[0]->ceil, n.wall.sectors[1]->ceil)
			- data->player_current_height, n.line.start.y), n.scale1);
	data->n_ceil_y_e = calc_floor_ceil(n.player.half_win_size.y,
			YAW(MIN(n.wall.sectors[0]->ceil, n.wall.sectors[1]->ceil)
			- data->player_current_height, n.line.end.y), n.scale2);
	data->n_floor_y_s = calc_floor_ceil(n.player.half_win_size.y,
			YAW(MAX(n.wall.sectors[0]->floor, n.wall.sectors[1]->floor)
			- data->player_current_height, n.line.start.y), n.scale1);
	data->n_floor_y_e = calc_floor_ceil(n.player.half_win_size.y,
			YAW(MAX(n.wall.sectors[0]->floor, n.wall.sectors[1]->floor)
			- data->player_current_height, n.line.end.y), n.scale2);
	data->n_floor_height = data->n_floor_y_e - data->n_floor_y_s;
	data->n_ceil_height = data->n_ceil_y_e - data->n_ceil_y_s;
}
