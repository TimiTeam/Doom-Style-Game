#include "sdl_head.h"


SDL_Surface 			*get_empty_surface(unsigned width, unsigned height)
{
    SDL_Surface *surface;
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    surface = SDL_CreateRGBSurface(0, width, height, 32,
                                   rmask, gmask, bmask, 0);

    /* or using the default masks for the depth: */
   // surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    return (surface);
}

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
	//sdl->surf = SDL_CreateRGBSurface(0, sdl->win_size.x, sdl->win_size.y, 32, 0, 0, 0, 0);
	sdl->surf = get_empty_surface(sdl->win_size.x, sdl->win_size.y);
	if (!sdl->surf)
		return (error_message("Main Surface is not exist"));
	SDL_SetRenderDrawColor(sdl->ren, 0xFF, 0xFF, 0xFF, 0xFF);
	return (OK);
}
