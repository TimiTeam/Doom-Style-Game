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

#include "sdl_head.h"

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

	if (x < 0 || x >= src->w || y < 0 || y >= src->h)
		return (0);
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
