#include "sdl_head.h"

SDL_Surface				*load_jpg_png(const char *file_name)
{
	SDL_Surface			*surf;

	surf = IMG_Load(file_name);
	if (!surf)
		return (error_message_null(IMG_GetError()));
	return (surf);
}

SDL_Surface				*load_bmp(const char *file_name)
{
	SDL_Surface			*surf;

	surf = SDL_LoadBMP(file_name);
	if (!surf)
		return (error_message_null(IMG_GetError()));
	return (surf);
}

SDL_Surface				*load_optimize_bmp(const char *file_name)
{
	SDL_Surface			*surf;	
	SDL_Surface			*opt;

	opt = NULL;
	if ((surf = load_bmp(file_name)))
	{
		opt = SDL_ConvertSurface(surf, surf->format, 0);
		SDL_FreeSurface(surf);
	}
	return (opt);
}

SDL_Surface				*load_img(const char *file_name)
{
	SDL_Surface			*surf;

	if (ft_strstr(file_name, ".bmp"))
		surf = load_optimize_bmp(file_name);
	else
		surf = load_jpg_png(file_name);
	return (surf);
}	