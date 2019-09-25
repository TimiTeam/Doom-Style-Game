#include "sdl_head.h"

void			sdl_render(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst)
{
	if (!ren || !tex)
		return ;
	SDL_RenderCopy(ren, tex, src, dst);
}