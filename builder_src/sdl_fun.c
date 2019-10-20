/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:23:41 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:16:01 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builder.h"

void					quit_sdl(char proper)
{
	if (TTF_WasInit())
		TTF_Quit();
	IMG_Quit();
	if (proper == TRUE)
		SDL_Quit();
}

void					free_sdl(t_sdl *sdl, char proper)
{
	if (!sdl)
		return ;
	if (sdl->rend)
	{
		SDL_DestroyRenderer(sdl->rend);
		sdl->rend = NULL;
	}
	if (sdl->window)
	{
		SDL_DestroyWindow(sdl->window);
		sdl->window = NULL;
	}
	if (sdl->font)
	{
		TTF_CloseFont(sdl->font);
	}
	free(sdl);
	sdl = NULL;
	quit_sdl(proper);
}

SDL_Texture				*load_texture(char *name, SDL_Renderer *rend, \
t_vec *size)
{
	SDL_Texture			*texture;
	SDL_Surface			*image;

	if (!name || !rend)
		return (NULL);
	if (!(image = IMG_Load(name)))
	{
		ft_putendl(IMG_GetError());
		return (NULL);
	}
	if (size)
		*size = (t_vec){ image->w, image->h };
	texture = SDL_CreateTextureFromSurface(rend, image);
	SDL_FreeSurface(image);
	if (!texture)
	{
		ft_putendl(SDL_GetError());
		return (NULL);
	}
	return (texture);
}

int						start_sdl(t_sdl *sdl)
{
	int					img_flag;

	img_flag = IMG_INIT_PNG;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_putendl(SDL_GetError());
		return (FAIL);
	}
	if (!(IMG_Init(img_flag) & img_flag))
		return (FAIL);
	if (TTF_Init() != 0)
		return (FAIL);
	if (!(sdl->window = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_CENTERED, \
	SDL_WINDOWPOS_CENTERED, W_W, W_H, SDL_WINDOW_SHOWN | \
	SDL_WINDOW_MOUSE_FOCUS)))
		return (FAIL);
	if (!(sdl->rend = SDL_CreateRenderer(sdl->window, -1, \
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		return (FAIL);
	if (!(sdl->font = TTF_OpenFont(FONT_NAME, 30)))
		return (FAIL);
	SDL_SetRenderDrawColor(sdl->rend, 0xFF, 0xFF, 0xFF, 0xFF);
	return (SUCCESS);
}

t_sdl					*get_sdl(void)
{
	t_sdl				*sdl;

	if (!(sdl = (t_sdl*)ft_memalloc(sizeof(t_sdl))))
		return (NULL);
	ft_bzero(sdl, sizeof(t_sdl));
	sdl->window = NULL;
	sdl->rend = NULL;
	sdl->mouse = (t_vec){ 0, 0 };
	if (start_sdl(sdl) == FAIL)
	{
		ft_putendl("couldn't start sdl");
		free_sdl(sdl, FALSE);
		return (NULL);
	}
	return (sdl);
}
