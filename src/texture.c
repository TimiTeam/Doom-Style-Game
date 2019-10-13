/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:17:25 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 17:17:26 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

int				scaler_next(t_scaler *i)
{
	i->cache += i->fd;
	while (i->cache >= i->ca)
	{
		i->result += i->bop;
		i->cache -= i->ca;
	}
	return (i->result);
}

void			apply_light(t_text_inf inf, float txty,
								int *pix, t_light *light)
{
	int			i;
	float		dist_to_light;
	Uint8		r;
	Uint8		g;
	Uint8		b;
	Uint8		a;

	if (txty < 0)
		return ;
	i = -1;
	while (++i < MAX_LIGHT_SRC && (light = inf.light_source[i]))
	{
		dist_to_light = len_between_points(inf.tex_pos, light->pos);
		if (dist_to_light < light->max_dist)
			inf.brightness += 1.0f - CLAMP(dist_to_light, 0, light->max_dist)
															/ light->max_dist;
	}
	SDL_GetRGBA(get_pixel(inf.image, inf.txtx, (int)txty % inf.image->h),
											inf.image->format, &r, &g, &b, &a);
	if (a)
		*pix = SDL_MapRGB(inf.image->format, MIN(r * inf.brightness, 255),
				MIN(g * inf.brightness, 255), MIN(b * inf.brightness, 255));
}

void			text_line(t_text_inf inf)
{
	int			*pix;
	t_light		*light;
	int			y;

	light = NULL;
	if (!inf.surface || !inf.image || inf.image->w == 0 || inf.image->h == 0)
		return ;
	inf.y1 = CLAMP(inf.y1, 0, H - 1);
	inf.y2 = CLAMP(inf.y2, 0, H - 1);
	pix = (int*)inf.surface->pixels;
	pix += inf.y1 * W + inf.x;
	inf.txtx %= inf.image->w;
	y = inf.y1;
	while (y <= inf.y2)
	{
		inf.brightness = 0.3f;
		apply_light(inf, scaler_next(&(inf.ty)), pix, light);
		pix += W;
		y++;
	}
}
