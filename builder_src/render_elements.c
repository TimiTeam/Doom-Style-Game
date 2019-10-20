/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:04:46 by mshpakov          #+#    #+#             */
/*   Updated: 2019/09/29 14:04:48 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

SDL_Texture				*get_text_txtr(char *str, t_sdl *sdl, t_txtb *textbox,\
t_vec *surfsize)
{
	SDL_Color			clr;
	SDL_Surface			*surf;
	t_rgb				rgb;
	SDL_Texture			*text;

	get_rgb(&rgb.r, &rgb.g, &rgb.b, textbox->text_color);
	clr = (SDL_Color){ rgb.r, rgb.g, rgb.b, 0 };
	surf = TTF_RenderText_Solid(sdl->font, str, clr);
	if (surf)
	{
		text = SDL_CreateTextureFromSurface(sdl->rend, surf);
		*surfsize = (t_vec){ surf->w, surf->h };
		SDL_FreeSurface(surf);
		if (text)
			return (text);
	}
	return (NULL);
}

void					write_txt(char *str, t_sdl *sdl, t_txtb textbox)
{
	int					w;
	float				ratio;
	SDL_Rect			rect;
	t_vec				surfsize;
	SDL_Texture			*text;

	if (!str || !sdl || !sdl->rend || !sdl->font)
		return ;
	surfsize = (t_vec){ 0, 0 };
	text = get_text_txtr(str, sdl, &textbox, &surfsize);
	if (text)
	{
		ratio = surfsize.y ? (float)surfsize.x / surfsize.y : 1.f;
		w = clamp(surfsize.y * ratio, 0, textbox.box.w);
		rect = (SDL_Rect){ textbox.box.x, textbox.box.y, w, textbox.box.h };
		if (textbox.h_center == TRUE)
			rect.x = textbox.box.x + (textbox.box.w - w) / 2;
		else
			rect.x = textbox.box.x + textbox.box.w * 0.05;
		SDL_RenderCopy(sdl->rend, text, NULL, &rect);
		SDL_DestroyTexture(text);
	}
}

void					rend_box(t_rec box, SDL_Texture *t, \
SDL_Renderer *rend)
{
	SDL_Rect			rect;

	if (!t || !rend || within(box.x, -1, W_W) == FALSE ||
		within(box.y, -1, W_H) == FALSE || box.w < 1 || box.y < 1)
		return ;
	rect = (SDL_Rect){ box.x, box.y, box.w, box.h };
	SDL_RenderCopy(rend, t, NULL, &rect);
}

void					render_screen(SDL_Renderer *rend, t_scr **screen)
{
	int					x;
	int					y;

	x = 0;
	while (x < W_W)
	{
		y = 0;
		while (y < W_H)
		{
			if (screen[x][y].color != 0)
				draw_dot(x, y, screen[x][y].color, rend);
			y++;
		}
		x++;
	}
}
