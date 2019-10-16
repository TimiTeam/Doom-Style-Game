/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_head.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:49:16 by ohavryle          #+#    #+#             */
/*   Updated: 2019/10/16 14:44:11 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAIN_HEAD_H
# define __MAIN_HEAD_H

# include <fcntl.h>
# include <pthread.h>
# include "sdl_head.h"
# include "sectors.h"
# define W 1390
# define H 980
# define EYEHEIGHT  5
# define THREADS 4
# define DELETE 	{tmp->next = all->next; ft_memdel((void**)&all); return ;}
# define DEL tmp = curr->next;delete_projectile(projectiles, curr);curr = tmp;
# define CON {DEL; continue;}
# define FRAME_VALUES 10

typedef	struct		s_fps_counter
{
	Uint32			frametimes[FRAME_VALUES];
	Uint32			frametimelast;
	Uint32			framecount;
	float			framespersecond;
}					t_fps_counter;

typedef struct		s_rect
{
	t_point			pos;
	t_point			size;
}					t_rect;

typedef struct		s_scaler
{
	int				result;
	int				bop;
	int				fd;
	int				ca;
	int				cache;
}					t_scaler;

typedef struct		s_draw_data
{
	short			ytop[W];
	short			ybottom[W];
	float			start;
	float			end;
	float			player_current_height;
	float			floor_y_e;
	float			floor_y_s;
	float			ceil_y_e;
	float			ceil_y_s;
	float			n_ceil_y_s;
	float			n_ceil_y_e;
	float			n_floor_y_s;
	float			n_floor_y_e;
	float			diff_ceil;
	float			diff_floor;
	float			calc_one;
	float			floor_calc;
	float			ceil_calc;
	short			recursion_deep;
	int				floor_height;
	int				ceil_height;
	int				n_floor_height;
	int				n_ceil_height;
}					t_draw_data;

typedef struct		s_player
{
	SDL_Surface		*sky;
	t_sector		*curr_sector;
	t_sector		*all;
	t_item			*inventar;
	t_gun			**all_guns;
	t_gun			*gun[3];
	Mix_Chunk		*damage_sound;
	Mix_Chunk		*get_item;
	Mix_Chunk		*door_sound;
	Mix_Chunk		*ambient;
	t_vector		pos;
	t_vector		end_pos;
	unsigned short	end_sector;
	t_point			half_win_size;
	t_gun			*current_gun;
	float			speed;
	float			yaw;
	float			angle;
	float			sin_angl;
	float			cos_angl;
	float			hfov;
	float			vfov;
	float			m_vfov;
	float			m_hfov;
	float			velocity;
	float			sky_w;
	float			sky_h;
	char			lift_near;
	char			door_near;
	short			height;
	short			health;
	short			end_sec;
	short			count_enemies;
	char			fall;
	char			sit;
	char			shooting;
	char			dead;
	char			curr_map;
	char			falling;
	char			win;
	char			jetpack;
}					t_player;

typedef struct		s_super_data
{
	int				start_x;
	int				end_x;
	t_sector		*sect;
	t_wall			drawing_line;
	t_wall			wall;
	t_player		player;
	int				u0;
	int				u1;
	float			scale_l;
	float			scale_h;
	t_draw_data		*data;
	SDL_Surface		*main_screen;
	SDL_Surface		*floor_texture;
	SDL_Surface		*ceil_texture;
}					t_super_data;

typedef struct		s_pr
{
	SDL_Surface		*texture;
	SDL_Surface		*background;
	SDL_Surface		*play_button;
	SDL_Surface		*exit_button;
	SDL_Surface		*logo;
	SDL_Surface		*choose_level_button;
	SDL_Rect		play_rect;
	SDL_Rect		exit_rect;
	SDL_Rect		logo_rect;
	SDL_Rect		choose_level_rect;
	SDL_Rect		font_rect;
	SDL_Color		font_color;
	TTF_Font		*font;
	char			**maps;
	int				sw;
	SDL_Event		event;
	int				i;
	int				maxi;
	int				win_h;
	int				win_w;
}					t_pr;

typedef struct		s_screen_inf
{
	int				cya;
	int				cyb;
	int				ya;
	int				yb;
	int				nya;
	int				nyb;
	int				n_cya;
	int				n_cyb;
	int				x;
	int				end;
	int				txtx;
	int				x_lenght;
	float			max_dist;
	int				z;
	float			dist;
	float			mapped;
	float			dx;
	float			scale_width_texture;
	t_vector		tex_pos;
	t_vector		vec;
}					t_screen_inf;

typedef struct		s_text_inf
{
	int				x;
	int				y1;
	int				y2;
	t_scaler		ty;
	unsigned		txtx;
	t_sector		*sect;
	SDL_Surface		*surface;
	SDL_Surface		*image;
	t_vector		tex_pos;
	float			scale_l;
	float			scale_h;
	t_light			**light_source;
	float			brightness;

}					t_text_inf;

typedef struct		s_ceil_inf
{
	SDL_Surface		*dst;
	SDL_Surface		*src;
	int				x;
	int				y;
	int				end_y;
	float			diff_height;
	t_player		player;
	t_sector		*sect;
	t_light			**light_source;
	float			mapx;
	float			mapz;
	unsigned		tx;
	unsigned		txtz;
	float			brightness;
	float			calc_one;
	float			calc_two;
}					t_ceil_inf;

typedef struct		s_world
{
	t_sector		*sec;
	t_wall			wall;
	t_player		*player;
	t_sdl			*sdl;
	t_draw_data		data;
	void			*thread_draw_sector;
}					t_world;

typedef struct		s_rot
{
	t_sector		*sec;
	t_wall			wall;
	t_player		*player;
	t_sdl			*sdl;
	t_draw_data		data;
	t_wall			line;
	void			*thread_draw_sector;
}					t_rot;

typedef struct		s_proj
{
	t_sector		*sec;
	t_wall			wall;
	t_player		*player;
	t_sdl			*sdl;
	t_draw_data		data;
	t_wall			line;
	int				u0;
	int				u1;
	float			scale_l;
	void			*thread_draw_sector;
}					t_proj;

typedef struct		s_again
{
	t_sector		*sec;
	t_wall			wall;
	t_player		*player;
	t_sdl			*sdl;
	t_draw_data		data;
}					t_again;

typedef struct		s_n
{
	t_player		player;
	t_wall			wall;
	t_wall			line;
	float			scale1;
	float			scale2;
}					t_n;

typedef struct		s_p_n_d
{
	t_player		player;
	t_draw_data		data;
}					t_p_n_d;

# define MIN(a,b)	(((a) < (b)) ? (a) : (b))
# define MAX(a,b)             (((a) > (b)) ? (a) : (b))
# define CLAMP(a, mi, ma)      MIN(MAX(a,mi),ma)
# define VXS(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))
# define OVP(a0,a1,b0,b1) MIN(a0,a1) <= MAX(b0,b1) && MIN(b0,b1) <= MAX(a0,a1)

# define YAW(y,z) (y + z * player.yaw)

void				fpsinit(t_fps_counter *fps);
void				fpsthink(t_fps_counter *fps);
void				change_player_state(t_player *player, t_sdl *sdl, int *run);
void				run_with_buff(t_player *player,
							t_sdl *sdl, unsigned int win_x);
void				initialize_sdl_win(t_pr *m);
void				load_textures(t_pr *m, t_sdl *sdl, t_read_holder *holder);
SDL_Surface			*txt_surf(TTF_Font *font, char *text, SDL_Color color);
void				renderallshit(t_pr *m);
int					render_menu(t_pr *m, t_sdl *sdl);
t_sector			*load_game(t_player *player, t_read_holder *holder);
int					menu_hooks(t_pr *m, t_read_holder *holder);
void				initialize_menu(t_pr *m);
int					load_menu_textures(t_pr *m, t_read_holder *holder);
SDL_Rect			change_size(SDL_Rect rect);
SDL_Rect			reset_size(SDL_Rect rect);
void				free_menu(t_pr *menu);
void				free_all(t_player **player, t_sdl **sdl,
					t_read_holder *holder, t_pr *m);
void				apply_filter(SDL_Surface *surface, float intensity);
void				check_door(t_player *player);
int					has_key(t_item *items);
t_sector			*get_sector_after_door(t_sector *door, t_sector *prev);
t_sector			*get_near_sector(t_player *player);
t_player			*new_t_player(int pos_x, int pos_y, t_point wid_size);
int					get_player_pos(char *line, t_vector *player_pos,
								unsigned *player_sec_id);
void				update_player_view(t_player *player);
void				free_player(t_player *player);
void				move_player(t_player *player, float sin_angle,
													float cos_angle);
void				move_player_vertically(t_player *player);
void				draw_scaled_image(SDL_Surface *screen, SDL_Surface *img,
													t_point pos, t_point size);
int					load_guns(t_gun **gun);
void				delete_guns(t_gun **all);
int					scaler_next(t_scaler *i);
t_sector			*get_new_player_sector(t_vector player_pos,
										t_sector *intersect_sector);
void				text_line(t_text_inf inf);
void				draw_world(t_world w);
void				draw_stripes(t_super_data *super, t_screen_inf inf);
void				draw_floor_or_ceil(t_ceil_inf inf);
void				draw_line(t_screen_inf inf, t_super_data *super);
void				threads(t_proj t);
void				again(t_again a);
void				draw_enemy_sprite(t_item *obj, t_draw_data data,
									t_player player, SDL_Surface *surface);
void				move_enemy_to_player(t_item *enemy, t_vector player_pos);
void				quicksort(t_item **head_ref, t_player *player);
t_item				*quick_sort_recur(t_item *head,
								t_item *end, t_player *player);
t_item				*tail_of(t_item *cur);
t_vector			point_of_intersec(t_vector p1, t_vector p2,
										t_vector p3, t_vector p4);
float				side_of_a_point(t_vector p, t_vector s, t_vector end);
int					box_intersection(t_vector p1, t_vector p2,
											t_vector p3, t_vector p4);
t_scaler			init_scaler(int n, t_point curr, t_point dst);
void				make_intersect(t_wall *wall);
void				get_gun_to_player(t_player *player,
						enum e_gun_type gun_type, SDL_Surface *icon);
void				rest_of_the_action_shit(t_pr *m, Uint8 *menu,
									t_sdl *sdl, t_read_holder *holder);
void				draw_hud(t_sdl *sdl, t_player *player);
void				print_player_gun(t_sdl *sdl, t_player *player);
t_projectile		*create_projectile(t_player player);
void				delete_projectile(t_projectile **head,
										t_projectile *proj);
Uint8				move_projectile(t_projectile *proj);
void				add_projectile(t_projectile **head, t_projectile *new);
void				draw_projectile(t_projectile *proj, t_draw_data data,
										t_player player, SDL_Surface *surface);
void				draw_projectiles(t_projectile **projectiles,
								t_p_n_d p, SDL_Surface *screen, t_item *items);
int					calc_floor_ceil(unsigned half_win_size_y,
									float floor_or_ceil_diff, float scale_y);
void				draw_image(SDL_Surface *screen, SDL_Surface *img,
											t_point pos, t_point size);
void				draw_image_with_criteria(SDL_Surface *screen,
								SDL_Surface *img, t_rect r, t_draw_data data);
void				delete_projectiles(t_projectile *head);
void				list_light(t_light	**arr, unsigned arr_size);
void				draw_skybox(SDL_Surface *dst, t_point pos,
												int end_y, t_player player);
void				fill_super_data(t_super_data *super, t_sector *sec,
											t_draw_data *data, t_wall wall);
void				fill_super_data_2(t_super_data *super,
											t_draw_data data, int step, int i);
void				fill_super_data_3(t_super_data *super,
								t_sector *sec, t_player player, t_sdl *sdl);
void				draw_sectors(t_sector *sec,
							t_player *player, t_sdl *sdl, t_draw_data data);
void				map_wall_text(int *u0, int *u1,
										t_vector diff, float scaled_tex);
int					compare_two_int_array(short *arr_one, short *arr_two,
											int from, int to);
void				floor_and_ceil_calculation(t_draw_data *data,
								t_player player, t_wall line, t_vector scale);
void				neighbour_calculation(t_draw_data *data, t_n n);
t_screen_inf		fill_inf(t_super_data *super, t_wall cp);
void				calculate_frame(t_screen_inf *inf,
											t_wall cp, t_super_data *super);
void				calculate_neighbours(t_screen_inf *inf,
									t_wall cp, t_draw_data *data);
void				render_neighbours(t_screen_inf inf,
								t_super_data *super, t_wall cp);
void				find_tex_pos(t_screen_inf *inf, t_super_data *super);
void				draw_sectors(t_sector *sectors,
					t_player *player, t_sdl *sdl, t_draw_data data);
void				update_player(t_player *player, unsigned char move[4]);
int					hook_event(t_player *player,
					unsigned char move[4]);
void				activate_lift(t_player *player);
void				draw_sector_items(t_item **items,
					t_player *player, t_draw_data data, SDL_Surface *screen);
int					game_loop(t_sdl *sdl, t_player *player, t_sector *sectors);
void				*thread_draw_sector(void *param);
void				draw_simple_wall(t_super_data super);
void				draw_sectors(t_sector *sec,
						t_player *player, t_sdl *sdl, t_draw_data data);
void				free_data_holder(t_read_holder *holder);
t_item				*del_cur_item_and_get_next(t_item **it_list, t_item *curr);
t_item				*change_item_animations(t_item **items,
									t_player *player, t_item *it);
#endif
