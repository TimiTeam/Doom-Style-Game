#include "sdl_head.h"

t_sdl				*new_t_sdl(int win_size_x, int win_size_y, const char *title)
{
	t_sdl			*new;

	if (win_size_x < 1 || win_size_y < 1 || !title)
		return (NULL);
	new = (t_sdl*)ft_memalloc(sizeof(t_sdl));
	*new = (t_sdl){};
	new->title = ft_strdup(title);
	new->win_size.x = win_size_x;
	new->win_size.y = win_size_y;
	return (new);
}

int					init_sdl(t_sdl *sdl)
{
	atexit(quit_sdl);	
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		return (error_message(SDL_GetError()));
	IMG_Init(IMG_INIT_PNG & IMG_INIT_PNG);
	if (TTF_Init() != 0)
		return (error_message(TTF_GetError()));
	sdl->win = SDL_CreateWindow(sdl->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		sdl->win_size.x, sdl->win_size.y, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
	if (!sdl->win)
		return (error_message(SDL_GetError()));
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE );
	if (!sdl->ren)
		return (error_message(SDL_GetError()));
	sdl->surf = SDL_CreateRGBSurface(0, sdl->win_size.x, sdl->win_size.y, 32, 0, 0, 0, 0);
	SDL_SetRenderDrawColor(sdl->ren, 0xFF, 0xFF, 0xFF, 0xFF);
	return (OK);
}