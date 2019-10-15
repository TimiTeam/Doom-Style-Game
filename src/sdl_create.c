/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:11:00 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:11:01 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_head.h"

SDL_Surface			*get_empty_surface(unsigned width, unsigned height)
{
#ifdef __LINUX__
Uint32			rmask;
Uint32			gmask;
Uint32			bmask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
#endif
	return (SDL_CreateRGBSurface(0, width, height, 32,
				rmask, gmask, bmask, 0));
#endif
	return (SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0));
}

t_sdl				*new_t_sdl(int win_size_x, int win_size_y,
											const char *title)
{
	t_sdl			*new;

	if (win_size_x < 1 || win_size_y < 1 || !title)
		return (NULL);
	new = (t_sdl*)ft_memalloc(sizeof(t_sdl));
	ft_memset(new, 0, sizeof(t_sdl));
	new->title = ft_strdup(title);
	new->win_size.x = win_size_x;
	new->win_size.y = win_size_y;
	return (new);
}

int					init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		return (error_message(SDL_GetError()));
	IMG_Init(IMG_INIT_PNG & IMG_INIT_PNG);
	if (TTF_Init() != 0)
		return (error_message(TTF_GetError()));
	sdl->win = SDL_CreateWindow(sdl->title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		sdl->win_size.x, sdl->win_size.y,
		SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
	if (!sdl->win)
		return (error_message(SDL_GetError()));
	sdl->ren = SDL_CreateRenderer(sdl->win, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	| SDL_RENDERER_TARGETTEXTURE);
	if (!sdl->ren)
		return (error_message(SDL_GetError()));
	sdl->surf = get_empty_surface(sdl->win_size.x, sdl->win_size.y);
	if (!sdl->surf)
		return (error_message("Main Surface is not exist"));
	SDL_SetRenderDrawColor(sdl->ren, 0xFF, 0xFF, 0xFF, 0xFF);
	return (OK);
}

int				init_sound()
{
	int			audio_rate;
	int			audio_channels;
	int			audio_buffers;
	Uint16		audio_format;

	audio_rate = 22050;
	audio_format = AUDIO_S16SYS;
	audio_channels = 6;
	audio_buffers = 1024;
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
		error_message(Mix_GetError());
	return (1);
}
