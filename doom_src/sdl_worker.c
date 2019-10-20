/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_worker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:11:19 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:11:20 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_head.h"

void			sdl_render(SDL_Renderer *ren, SDL_Texture *tex,
									SDL_Rect *src, SDL_Rect *dst)
{
	if (!ren || !tex)
		return ;
	SDL_RenderCopy(ren, tex, src, dst);
}

void			prepare_surf(SDL_Renderer *ren, SDL_Surface *surf)
{
	SDL_SetRenderDrawColor(ren, 0, 200, 0, 255);
	SDL_RenderClear(ren);
	SDL_FillRect(surf, NULL, 0x00);
}

void			render_tex(t_sdl *sdl)
{
	SDL_Texture	*tex;

	tex = SDL_CreateTextureFromSurface(sdl->ren, sdl->surf);
	sdl_render(sdl->ren, tex, NULL, NULL);
	SDL_DestroyTexture(tex);
	SDL_RenderPresent(sdl->ren);
}
