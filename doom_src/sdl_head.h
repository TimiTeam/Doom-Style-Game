/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_head.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:10:43 by atabala           #+#    #+#             */
/*   Updated: 2019/10/16 14:14:13 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SDL_HEAD_H
# define __SDL_HEAD_H

# include "libft.h"
# ifdef __APPLE__

#  include <SDL.h>
#  include <SDL_mixer.h>
#  include <SDL_ttf.h>
#  include <SDL_image.h>
#  define RMASK 0
#  define GMASK 0
#  define BMASK 0
# endif

# ifdef __linux__

#  include <SDL2/SDL.h>
#  include <SDL2/SDL_mixer.h>
#  include <SDL2/SDL_ttf.h>
#  include <SDL2/SDL_image.h>
#  if SDL_BYTEORDER == SDL_BIG_ENDIAN
#   define RMASK 0xff000000;
#   define GMASK 0x00ff0000;
#   define BMASK 0x0000ff00;
#  else
#   define RMASK 0x000000ff;
#   define GMASK 0x0000ff00;
#   define BMASK 0x00ff0000;
#  endif
# endif
# define OK 1
# define ERROR 0

/*
** timer status
*/

# define TIMER_OFF				0
# define TIMER_ON				1
# define TIMER_PAUSED			2

typedef struct		s_timer
{
	Uint32			when_started;
	Uint32			when_paused;
	int				status;
}					t_timer;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef	struct		s_sdl
{
	char			*title;
	t_point			win_size;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface		*surf;
	TTF_Font		*font;
	float			fps;
	unsigned		frame_id;
}					t_sdl;

/*
**					CREATE
*/
t_sdl				*new_t_sdl(int win_size_x, int win_size_y,
						const char *title);
int					init_sdl(t_sdl *sdl);

/*
**					SOUND
*/
int					init_sound();

/*
** 					INFO
*/
int					error_message(const char *error);
void				*error_message_null(const char *error);

/*
** 					IMAGES
*/
SDL_Surface			*load_jpg_png(const char *file_name);
SDL_Surface			*load_bmp(const char *file_name);
SDL_Surface			*load_optimize_bmp(const char *file_name);
SDL_Surface			*load_img(const char *file_name);

/*
**					TEXTURE
*/
SDL_Texture			*load_texture(const char *file_name, SDL_Renderer *ren);
SDL_Texture			*texture_from_surf(SDL_Surface *surf, SDL_Renderer *ren);
SDL_Texture			*new_fresh_texture(SDL_Renderer *ren, int width,
						int height);

/*
** 					RENDER
*/
void				sdl_render(SDL_Renderer *ren, SDL_Texture *tex,
						SDL_Rect *src, SDL_Rect *dst);
void				prepare_surf(SDL_Renderer *ren, SDL_Surface *surf);
void				render_tex(t_sdl *sdl);

/*
**					FONT AND TEXT
*/
SDL_Texture			*make_color_text(SDL_Renderer *ren, const char *str,
						const char *file_font, int size, SDL_Color col);
SDL_Texture			*make_black_text(SDL_Renderer *ren, const char *str,
						const char *path_to_font, int size);
SDL_Texture			*make_text_using_ttf_font(SDL_Renderer *ren,
						TTF_Font *font, const char *str, SDL_Color col);
SDL_Texture			*make_black_text_using_ttf_font(SDL_Renderer *ren,
						TTF_Font *font, const char *str);

/*
** 					DESTROY
*/
void				quit_sdl();
void				free_t_sdl(t_sdl **s);
void				close_t_sdl(t_sdl *s);

/*
** 					TIMER
*/
Uint32				get_ticks(t_timer timer);
void				stop_timer(t_timer *timer);
void				unpause_timer(t_timer *timer);
void				pause_timer(t_timer *timer);
void				start_timer(t_timer *timer);
t_timer				init_timer(void);

/*
** 					PIXELS
*/
void				put_pixel(SDL_Surface *dst, int x, int y,
						Uint32 pixel);
Uint32				get_pixel(SDL_Surface *src, int x, int y);

#endif
