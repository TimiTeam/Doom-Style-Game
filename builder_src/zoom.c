/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 17:06:36 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/07 17:21:00 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					zoom_displace(t_rec *grid_b, t_vec p,
										float old_scl,
										float new_scl)
{
	float				mapx;
	float				mapy;

	mapx = (float)(p.x - grid_b->x) / old_scl;
	mapy = (float)(p.y - grid_b->y) / old_scl;
	grid_b->x = (int)((float)p.x - (mapx * new_scl));
	grid_b->y = (int)((float)p.y - (mapy * new_scl));
}

void					zoom_grid(t_prog *prog, t_vec mouse, t_grid *grid)
{
	static float		min_scl = 1.f;
	float				new;
	float				old_scl;

	if (!prog || !grid)
		return ;
	if (mouse_over(grid->box, mouse))
	{
		old_scl = grid->scl;
		if (min_scl <= 1)
			get_min_scl(&min_scl);
		new = grid->scl + grid->scl * 0.3f * (float)prog->zoom;
		grid->scl = clamp_f(new, min_scl, 100);
		zoom_displace(&grid->box, mouse, old_scl, grid->scl);
		prog->redraw = 1;
	}
	prog->zoom = 0;
}

void					update_zoom_scale(t_grid *grid, t_vec desired, int n)
{
	float				tmp_scale;
	int					a;
	int					b;

	if (!grid)
		return ;
	a = W_W * 0.6;
	b = W_H * 0.6;
	tmp_scale = get_scl_to_sector(n, a, b);
	zoom_displace(&grid->box, desired, grid->scl, tmp_scale);
	grid->scl = tmp_scale;
}

void					zoom_to_box(t_grid *grid, t_vec *vecs, int n_vecs)
{
	static t_vec		desired = { W_W * 0.3, W_H * 0.5 };
	t_vec				min;
	t_vec				max;
	t_vec				center;
	int					n;

	if (!vecs || !grid)
		return ;
	bounding_box(&min, &max, vecs, n_vecs);
	highlight_sec_nod(vecs, n_vecs, grid);
	n = get_max(max.x - min.x, max.y - min.y);
	min = transform_to_screen(min, grid);
	max = transform_to_screen(max, grid);
	center = (t_vec){ min.x + (max.x - min.x) / 2, \
	min.y + (max.y - min.y) / 2 };
	grid->box.x = (grid->box.x - center.x) + desired.x;
	grid->box.y = (grid->box.y - center.y) + desired.y;
	update_zoom_scale(grid, desired, n);
}
