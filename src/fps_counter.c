#include "main_head.h"

void 				fpsinit(t_fps_counter *fps)
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
    Uint8 			i;

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
	
    i = 0;
	while (i < count)
	{
        fps->framespersecond += fps->frametimes[i];
		i++;
    }
    fps->framespersecond /= count;
    fps->framespersecond = 1000.f / fps->framespersecond;
}