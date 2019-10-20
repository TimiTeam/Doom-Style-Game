/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:01:15 by tbujalo           #+#    #+#             */
/*   Updated: 2019/10/15 16:01:17 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void				fpsinit(t_fps_counter *fps)
{
	ft_memset(fps->frametimes, 0, sizeof(fps->frametimes));
	fps->framecount = 0;
	fps->framespersecond = 0;
	fps->frametimelast = SDL_GetTicks();
}

void				fpsthink(t_fps_counter *fps)
{
	Uint32			frametimesindex;
	Uint32			getticks;
	Uint8			count;
	Uint8			i;

	frametimesindex = fps->framecount % FRAME_VALUES;
	getticks = SDL_GetTicks();
	fps->frametimes[frametimesindex] = getticks - fps->frametimelast;
	fps->frametimelast = getticks;
	fps->framecount++;
	if (fps->framecount < FRAME_VALUES)
		count = fps->framecount;
	else
		count = FRAME_VALUES;
	fps->framespersecond = 0;
	i = -1;
	while (++i < count)
		fps->framespersecond += fps->frametimes[i];
	fps->framespersecond /= count;
	fps->framespersecond = 1000.f / fps->framespersecond;
}
