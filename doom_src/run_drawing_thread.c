/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_drawing_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 21:23:05 by tbujalo           #+#    #+#             */
/*   Updated: 2019/10/15 21:23:09 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

static void			filling_super_data(t_super_data *super, t_proj *t,
						int step, int i)
{
	fill_super_data(super, t->sec, &(t->data), t->line);
	fill_super_data_2(super, t->data, step, i);
	fill_super_data_3(super, t->sec, *t->player, t->sdl);
	super->scale_l = t->scale_l;
	super->u0 = t->u0;
	super->u1 = t->u1;
	super->wall = t->wall;
}

void				threads(t_proj t)
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
		filling_super_data(&super[i], &t, step, i);
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

void				*thread_draw_sector(void *param)
{
	t_screen_inf	inf;
	t_wall			cp;
	t_super_data	*super;

	super = (t_super_data*)param;
	cp = super->drawing_line;
	inf = fill_inf(super, cp);
	while (inf.x < inf.end)
	{
		calculate_frame(&inf, cp, super);
		draw_stripes(super, inf);
		find_tex_pos(&inf, super);
		if (super->wall.type != empty_wall && super->wall.type != transparent)
		{
			if (super->wall.type == window &&
				(!super->wall.sectors[0] || !super->wall.sectors[1]))
				draw_skybox(super->main_screen,
					(t_point){inf.x, inf.cya}, inf.cyb, super->player);
			draw_line(inf, super);
		}
		else
			render_neighbours(inf, super, cp);
		inf.x++;
	}
	return (NULL);
}
