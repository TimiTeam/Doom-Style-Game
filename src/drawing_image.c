/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 23:27:29 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/28 23:27:29 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

int					transparent_pixel(int pixel, SDL_PixelFormat *format)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;

	SDL_GetRGBA(pixel, format, &r, &g, &b, &a);
	if (a != 0)
		return (1);
	return (0);
}

int					point_in_image(int x, int y, SDL_Surface *image)
{
	if (x >= 0 && x < image->w && y >= 0 && y < image->h)
		return (1);
	return (0);
}

void				init_step(t_vector *step, t_vector *img_point,
							SDL_Surface *im, t_point size)
{
	step->x = (float)im->w / size.x;
	step->y = (float)im->h / size.y;
//	*img_point = (t_vector){0};
	ft_memset(img_point, 0, sizeof(t_vector));
}

void				draw_image(SDL_Surface *screen, SDL_Surface *img,
										t_point pos, t_point size)
{
	int				x;
	int				y;
	int				pix;
	t_vector		img_point;
	t_vector		step;

	if (!screen || !img)
		return ;
	init_step(&step, &img_point, img, size);
	y = -1;
	while (++y < size.y)
	{
		x = -1;
		img_point.x = 0;
		while (++x < size.x)
		{
			pix = get_pixel(img, (int)img_point.x, (int)img_point.y);
			if (point_in_image(x, y, screen)
			&& transparent_pixel(pix, img->format))
				put_pixel(screen, x + pos.x, y + pos.y, pix);
			img_point.x += step.x;
		}
		img_point.y += step.y;
	}
}

void				draw_image_with_criteria(SDL_Surface *screen,
			SDL_Surface *img, t_rect r, t_draw_data data)
{
	int				i;
	int				j;
	int				pix;
	t_vector		img_point;
	t_vector		step;

	if (!screen || !img)
		return ;
	init_step(&step, &img_point, img, r.size);
	i = -1;
	while (++i < r.size.y)
	{
		j = -1;
		img_point.x = 0;
		while (++j < r.size.x)
		{
			pix = get_pixel(img, (int)img_point.x, (int)img_point.y);
			if (j + r.pos.x > data.start && j + r.pos.x < data.end && i +
	r.pos.y > data.ytop[j + r.pos.x] && i + r.pos.y < data.ybottom[j + r.pos.x]
				&& transparent_pixel(pix, img->format))
				put_pixel(screen, j + r.pos.x, i + r.pos.y, pix);
			img_point.x += step.x;
		}
		img_point.y += step.y;
	}
}
