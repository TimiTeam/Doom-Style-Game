#include "sdl_head.h"

SDL_Texture			*make_color_text(SDL_Renderer *ren, const char *str, const char *file_font, int size, SDL_Color col)
{
	SDL_Texture		*ret;
	SDL_Surface		*surf;
	TTF_Font 		*font;

	surf = NULL;
	ret = NULL;
	if (!str)
		return (error_message_null("Empty text message"));
	font = TTF_OpenFont(file_font, size);
	if (font)
	{
		surf = TTF_RenderText_Solid(font, str, col);
		TTF_CloseFont(font);
	}
	if (surf)
	{
		ret = SDL_CreateTextureFromSurface(ren, surf);
		SDL_FreeSurface(surf);
	}
	return (ret);
}

SDL_Texture			*make_black_text(SDL_Renderer *ren, const char *str, const char *path_to_font, int size)
{
	SDL_Color		col;

	col = (SDL_Color){.a = 250, .r = 5, .g = 5, .b = 5};
	return (make_color_text(ren, str, path_to_font, size, col));
}