#include "main_head.h"

void				apply_filter(SDL_Surface *surface, float intensity)
{
	Uint8 r, g, b;
	int y;
	int x;

	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			SDL_GetRGB(get_pixel(surface, x, y), surface->format, &r, &g, &b);
			put_pixel(surface, x, y, SDL_MapRGB(surface->format, r * intensity, g * intensity, b * intensity));
		}
	}
}

void    		draw_crosshair(SDL_Surface *surface)
{
	int			half_w;
	int			half_h;

	half_w = W >> 1;
	half_h = H >> 1;
    t_point start1;
    t_point start2;
    t_point end1;
    t_point end2;
    start1.x = half_w - 30;
    start1.y = half_h;
    end1.x = half_w + 30;
    end1.y = half_h;
    start2.x = half_w;
    start2.y = half_h - 30;
    end2.x = half_w;
    end2.y = half_h + 30;
    line(surface, start1, end1, 0xffffffff);
    line(surface, start2, end2, 0xffffffff);
}

int			transparent_pixel(Uint32 pixel, SDL_PixelFormat *format)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;
	Uint8	a;

	SDL_GetRGBA(pixel, format, &r, &g, &b, &a);
	if (a != 0)
		return (1);
	return (0);
}

void 			draw_image(SDL_Surface *screen, SDL_Surface *img, t_point pos, t_point size)
{
	int 		i;
	int		j;
	Uint32		pix;
	t_vector	img_point;
	t_vector	step;

	if (!screen || !img)
		return ;
	step.x = (float)img->w / size.x;
	step.y = (float)img->h / size.y;
	img_point = (t_vector){};
	i = 0;
	while (i < size.y)
	{
		j = 0;
		img_point.x = 0;
		while (j < size.x)
		{
			pix = get_pixel(img, (int)img_point.x, (int)img_point.y); 
			if (j + pos.x > 0 && j + pos.x < screen->w && i + pos.y > 0 && i + pos.y < screen->h && transparent_pixel(pix, img->format))
				put_pixel(screen, j + pos.x, i + pos.y, pix);
			img_point.x += step.x;
			j++;
		}
		img_point.y += step.y;
		i++;
	}
}

void 			draw_image_with_criteria(SDL_Surface *screen, SDL_Surface *img, t_point pos, t_point size, t_draw_data data)
{
	int 		i;
	int			j;
	Uint32		pix;
	t_vector	img_point;
	t_vector	step;
	
	if (!screen || !img)
		return ;
	step.x = (float)img->w / size.x;
	step.y = (float)img->h / size.y;
	img_point = (t_vector){};
	i = 0;
	draw_crosshair(screen);
	while (i < size.y)
	{
		j = 0;
		img_point.x = 0;
		while (j < size.x)
		{
			pix = get_pixel(img, (int)img_point.x, (int)img_point.y); 
			if (j + pos.x > data.start && j + pos.x < data.end && i + pos.y > data.ytop[j + pos.x] && i + pos.y < data.ybottom[j + pos.x]
					&& transparent_pixel(pix, img->format))
				put_pixel(screen, j + pos.x, i + pos.y, pix);
			img_point.x += step.x;
			j++;
		}
		img_point.y += step.y;
		i++;
	}
}