/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:11:13 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:11:14 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_head.h"

SDL_Texture				*texture_from_surf(SDL_Surface *surf, SDL_Renderer *ren)
{
	SDL_Texture			*tex;

	if (!surf)
		return (error_message_null("Missing surface"));
	if (!ren)
		return (error_message_null("Missing renderer"));
	tex = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf);
	return (tex);
}

SDL_Texture				*new_fresh_texture(SDL_Renderer *ren,
											int width, int height)
{
	SDL_Texture			*tex;
	SDL_Surface			*surf;

	tex = NULL;
	if (width < 0 || height < 0 || width > 10000 || height > 10000)
		return (NULL);
	if ((surf = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0)))
		tex = texture_from_surf(surf, ren);
	return (tex);
}

SDL_Texture				*load_texture(const char *file_name, SDL_Renderer *ren)
{
	SDL_Surface			*surf;
	SDL_Texture			*tex;

	tex = NULL;
	if (!ren)
		return (error_message_null("Missing renderer"));
	if (ft_strstr(file_name, ".bmp"))
		surf = load_bmp(file_name);
	else
		surf = load_jpg_png(file_name);
	if (surf)
		tex = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf);
	return (tex);
}
