/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_worker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:16:51 by tbujalo           #+#    #+#             */
/*   Updated: 2019/05/14 18:48:23 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel_worker.h"

static	void	fill_pixel_3(Uint8 *dst, Uint32 src)
{
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
		dst[0] = (src >> 16) & 0xff;
		dst[1] = (src >> 8) & 0xff;
		dst[2] = src & 0xff;
	}
	else
	{
		dst[0] = src & 0xff;
		dst[1] = (src >> 8) & 0xff;
		dst[2] = (src >> 16) & 0xff;
	}
}

Uint32			get_pixel(SDL_Surface *src, int x, int y)
{
	int			bpp;
	Uint8		*p;

	bpp = src->format->BytesPerPixel;
	p = (Uint8*)src->pixels + y * src->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16*)p);
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	else if (bpp == 4)
		return (*(Uint32*)p);
	else
		return (0);
}

void			put_pixel(SDL_Surface *dst, int x, int y, Uint32 pixel)
{
	int			bpp;
	Uint8		*p;

	bpp = dst->format->BytesPerPixel;
	p = (Uint8*)dst->pixels + y * dst->pitch + x * bpp;
	if (bpp == 1)
		*p = pixel;
	else if (bpp == 2)
		*(Uint16*)p = pixel;
	else if (bpp == 3)
		fill_pixel_3(p, pixel);
	else if (bpp == 4)
		*(Uint32*)p = pixel;
}
/*
int				scale_image(SDL_Surface *dst, SDL_Surface *src)
{
	t_point		pix_dst;
	t_point		pix_src;
	t_point		div;

	if (!dst || !src)
		return (1);
	div.x = round((double)dst->w / (double)src->w);
	div.y = round((double)dst->h / (double)src->h);
	pix_dst.x = -1;
	pix_src.x = 0;
	while (++pix_dst.x < dst->w)
	{
		pix_dst.y = -1;
		pix_src.y = 0;
		while (++pix_dst.y < dst->h)
		{
			put_pixel(dst, pix_dst, get_pixel(src, pix_src));
			if (pix_dst.y % div.y == 0 && pix_src.y < src->h)
				pix_src.y++;
		}
		if (pix_dst.x % div.x == 0 && pix_src.x < src->w)
			pix_src.x++;
	}
	return (0);
}*/
