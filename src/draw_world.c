/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:15:52 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:15:53 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void			again(t_again a)
{
	t_wall		wall;
	t_player	player;

	wall = a.wall;
	player = *a.player;
	a.data.recursion_deep++;
	if ((wall.type == empty_wall || wall.type == transparent) && wall.sectors[1] && wall.sectors[0]
	 && !compare_two_int_array(a.data.ybottom, a.data.ytop, a.data.start, a.data.end) && a.data.recursion_deep < 100 && a.data.recursion_deep < 36)
	{
		if (wall.sectors[0]->sector != player.curr_sector->sector
				&& wall.sectors[0]->sector != a.sec->sector)
			draw_sectors(wall.sectors[0], a.player, a.sdl, a.data);
		else if (wall.sectors[1]->sector != player.curr_sector->sector
						&& wall.sectors[1]->sector != a.sec->sector)
			draw_sectors(wall.sectors[1], a.player, a.sdl, a.data);
	}
}

void			threads(t_proj t)
{
	pthread_t		thread[THREADS];
	t_super_data	super[THREADS];
	int				step;
	int				i;

	i = -1;
	t.data.start = MAX(t.line.start.x, t.data.start);
	t.data.end = MIN(t.line.end.x, t.data.end);
	step = (t.data.end - t.data.start) / THREADS;
	while (++i < THREADS)
	{
		fill_super_data(&super[i], t.sec, &(t.data), t.line);
		fill_super_data_2(&super[i], t.data, step, i);
		fill_super_data_3(&super[i], t.sec, *t.player, t.sdl);
		super[i].scale_l = t.scale_l;
		super[i].u0 = t.u0;
		super[i].u1 = t.u1;
		super[i].wall = t.wall;
		pthread_create(&thread[i], NULL, t.thread_draw_sector, &super[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(thread[i], NULL);
	again((t_again){t.sec, t.wall, t.player, t.sdl, t.data});
	if (super->wall.type == transparent)
	{
		super[0].start_x = t.data.start;
		super[0].end_x = t.data.end;
		draw_simple_wall(super[0]);
	}
}

void			draw_projected(t_proj p)
{
	t_vector	scl1;
	t_vector	scl2;
	t_player	player;
	t_wall		line;

	line = p.line;
	player = *p.player;
	scl1 = (t_vector){player.hfov / line.start.y, player.vfov / line.start.y, 0};
	scl2 = (t_vector){player.hfov / line.end.y, player.vfov / line.end.y, 0};
	line.start.x = player.half_win_size.x - (int)(line.start.x * scl1.x);
	line.end.x = player.half_win_size.x - (int)(line.end.x * scl2.x);
	if (line.start.x >= line.end.x || line.end.x < p.data.start
								|| line.start.x > p.data.end)
		return ;
	floor_and_ceil_calculation(&(p.data), player,
							line, (t_vector){scl1.y, scl2.y, 0});
	if ((p.wall.type == empty_wall || p.wall.type == transparent) && p.wall.sectors[1] && p.wall.sectors[0])
		neighbour_calculation(&(p.data), (t_n){player,
					p.wall, line, scl1.y, scl2.y});
	threads((t_proj){p.sec, p.wall, p.player, p.sdl, p.data,
				line, p.u0, p.u1, p.scale_l, p.thread_draw_sector});
}

void			get_rotated(t_rot r)
{
	int			u0;
	int			u1;
	float		scale_l;
	t_vector	org1;
	t_vector	org2;

	org1 = (t_vector){r.line.start.x, r.line.start.y, 0};
	org2 = (t_vector){r.line.end.x, r.line.end.y, 0};
	if (r.line.start.y <= 0 || r.line.end.y <= 0)
		make_intersect(&(r.line));
	if (fabsf(r.wall.start.x - r.wall.end.x)
		> fabsf(r.wall.start.y - r.wall.end.y))
		scale_l = fabsf(r.wall.start.x - r.wall.end.x) / 10;
	else
		scale_l = fabsf(r.wall.start.y - r.wall.end.y) / 10;
	if (fabs(r.line.end.x - r.line.start.x)
		> fabs(r.line.end.y - r.line.start.y))
		map_wall_text(&u0, &u1, (t_vector){r.line.start.x - org1.x,
		r.line.end.x - org1.x, 0}, ((r.wall.texture->w) * scale_l - 1)
		/ (org2.x - org1.x));
	else
		map_wall_text(&u0, &u1, (t_vector){r.line.start.y - org1.y, r.line.end.y
		- org1.y, 0}, ((r.wall.texture->w) * scale_l - 1) / (org2.y - org1.y));
	draw_projected((t_proj){r.sec, r.wall, r.player,
	r.sdl, r.data, r.line, u0, u1, scale_l, r.thread_draw_sector});
}

void			draw_world(t_world w)
{
	t_wall		line;
	t_player	player;
	t_wall		wall;

	player = *w.player;
	wall = w.wall;
	line.start = (t_vector){wall.start.x - player.pos.x,
							wall.start.y - player.pos.y, 0};
	line.end = (t_vector){wall.end.x - player.pos.x,
							wall.end.y - player.pos.y, 0};
	line.start = (t_vector){line.start.x * player.sin_angl
						- line.start.y * player.cos_angl,
				line.start.x * player.cos_angl
				+ line.start.y * player.sin_angl, .z = line.start.y};
	line.end = (t_vector){line.end.x * player.sin_angl
						- line.end.y * player.cos_angl,
			line.end.x * player.cos_angl
				+ line.end.y * player.sin_angl, .z = line.end.y};
	if (line.start.y <= 0 && line.end.y <= 0)
		return ;
	get_rotated((t_rot){w.sec, wall, w.player,
			w.sdl, w.data, line, w.thread_draw_sector});
}
