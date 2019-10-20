/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:10:44 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/28 20:10:45 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					draw_dot2(int x, int y, t_scr s, t_scr **screen)
{
	if (x >= 0 && x < W_W && y >= 0 && y < W_H)
	{
		if (s.color == EMPTY_COLOR && screen[x][y].color != 0)
			return ;
		if (s.color == EMPTY_W_CLR && screen[x][y].color != 0)
			return ;
		screen[x][y] = s;
	}
}

void					draw_dot(int x, int y, int color, SDL_Renderer *rend)
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	if (x >= 0 && x < W_W && y >= 0 && y < W_H)
	{
		get_rgb(&r, &g, &b, color);
		SDL_SetRenderDrawColor(rend, r, g, b, 255);
		SDL_RenderDrawPoint(rend, x, y);
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	}
}

void					draw_part(t_vec c, t_vec p, t_scr s, t_scr **screen)
{
	int					i;

	if (!screen)
		return ;
	i = c.x - p.x;
	while (i <= c.x + p.x)
	{
		draw_dot2(i, c.y + p.y, s, screen);
		draw_dot2(i, c.y - p.y, s, screen);
		i++;
	}
	i = c.x - p.y;
	while (i <= c.x + p.y)
	{
		draw_dot2(i, c.y + p.x, s, screen);
		draw_dot2(i, c.y - p.x, s, screen);
		i++;
	}
}

void					draw_circle_fill2(t_vec c, int radius, t_scr s, \
t_scr **screen)
{
	t_vec				p;
	t_vec				d;
	int					radius_err;

	p = (t_vec){radius, 0};
	d = (t_vec){1 - (radius << 1), 0};
	radius_err = 0;
	while (p.x >= p.y)
	{
		draw_part(c, p, s, screen);
		p.y++;
		radius_err += d.y;
		d.y += 2;
		if (((radius_err << 1) + d.x) > 0)
		{
			p.x--;
			radius_err += d.x;
			d.x += 2;
		}
	}
}
