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
