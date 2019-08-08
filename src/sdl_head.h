#ifndef __SDL_HEAD_H
#define __SDL_HEAD_H

#include "libft.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define OK 1
#define ERROR 0

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef	struct		s_sdl
{
	t_point			win_size;
	char			*title;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface		*surf;
}					t_sdl;

//					CREATE
t_sdl				*new_t_sdl(int win_size_x, int win_size_y, const char *title);
int					init_sdl(t_sdl *sdl);

//					INFO
int					error_message(const char *error);
void				*error_message_null(const char *error);

//					IMAGES
SDL_Surface			*load_jpg_png(const char *file_name);
SDL_Surface			*load_bmp(const char *file_name);
SDL_Surface			*load_optimize_bmp(const char *file_name);
SDL_Surface			*load_img(const char *file_name);

//					TEXTURE
SDL_Texture			*load_texture(const char *file_name, SDL_Renderer *ren);
SDL_Texture			*texture_from_surf(SDL_Surface *surf, SDL_Renderer *ren);
SDL_Texture			*new_fresh_texture(SDL_Renderer *ren, int width, int height);

//					RENDER
void				sdl_render(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst);

//					FONT AND TEXT

SDL_Texture			*make_color_text(SDL_Renderer *ren, const char *str, const char *file_font, int size, SDL_Color col);
SDL_Texture			*make_black_text(SDL_Renderer *ren, const char *str, const char *path_to_font, int size);

//					DESTROY
void				quit_sdl();
void				free_t_sdl(t_sdl **s);
void				close_t_sdl(t_sdl *s);

#endif	