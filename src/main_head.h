#ifndef __MAIN_HEAD_H
#define __MAIN_HEAD_H

# include <fcntl.h>
# include <pthread.h>
# include "sdl_head.h"
# include "sectors.h"

#define W 1240
#define H 980
#define EyeHeight  5
#define DuckHeight 2.5
#define HeadMargin 1
#define KneeHeight 2

#define THREADS 4

static float m_vfov = 0.2f;
static float m_hfov = 0.73f*H/W;
static int h_w = W >> 1;
static int h_h = H >> 1;

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
	int 			ytop[W];
	int				ybottom[W];
	float 			start;
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
	float 			diff_ceil;
	float 			diff_floor;
	int				floor_height;
	int				ceil_height;
	int				n_floor_height;
	int				n_ceil_height;	
}					t_draw_data;

typedef struct		s_gun
{
	float 			state;
	SDL_Surface		*frame[10];
	SDL_Surface		*icon;
	enum gun_type	type;
	int				max_frames;
	int				ammo;
	float			damage;
	float			rate_of_fire;
}					t_gun;

typedef struct		s_plyer
{	
	SDL_Surface		*sky;
	t_sector 		*curr_sector;
	t_item			*inventar;
	t_gun			*gun[3];
	t_vector		pos;
	t_point			half_win_size;
	t_gun			*current_gun;
	float 			speed;
	float			yaw;
	float			angle;
	float			sin_angl;
	float			cos_angl;
	float 			hfov;
	float 			vfov;
	float			velocity;
	int				height;
	int				health;
	unsigned char	fall;
	char			sit;
	unsigned char	shooting;
	char			dead;
	char			curr_map;
	float			skyW;
	float			skyH;
	unsigned char	falling;
}					t_player;

typedef struct 		s_super_data
{
	int 			start_x;
	int 			end_x;
	t_sector		*sect;
	t_wall 			drawing_line;
	t_wall			wall;
	t_player 		player;
	int 			u0, u1;
	float 			scaleL;
	float 			scaleH ;
	t_draw_data 	*data;
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

#define min(a,b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi, ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0,a1,b0,b1) min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1)
// IntersectBox: Determine whether two 2D-boxes intersect.
/*
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((t_vector) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })
*/

#define Yaw(y,z) (y + z * player.yaw)

//MENU
void					initialize_sdl_win(t_pr *m);
void					load_textures(t_pr *m, t_sdl *sdl, t_read_holder *holder);
SDL_Surface				*get_text_surfcae(TTF_Font *font, char *text, SDL_Color color);
void					renderallshit(t_pr *m);
int						render_menu(t_pr *m, t_sdl *sdl);
int 					load_game(t_player *player, t_read_holder *holder);
int 					menu_hooks(t_pr *m, t_read_holder *holder);
SDL_Rect				change_size(SDL_Rect rect);
SDL_Rect				reset_size(SDL_Rect rect);
void 					free_menu(t_pr *menu);
void					apply_filter(SDL_Surface *surface, float intensity);

t_player				*new_t_player(int pos_x, int pos_y, t_point wid_size);
void					free_player(t_player *player);

void 					draw_scaled_image(SDL_Surface *screen, SDL_Surface *img, t_point pos, t_point size);

int 					scaler_next(t_scaler *i);

void 					textLine(int x, int y1, int y2, t_scaler ty, unsigned txtx, t_sector *sect, SDL_Surface *surface, SDL_Surface *image, t_vector tex_pos, float scaleL, float scaleH, t_light **light_source);

void 					draw_floor_or_ceil(SDL_Surface *dst, SDL_Surface *src, int x, int y, int end_y, float diff_height, t_player player, t_sector *sect, t_light **light_source);

void					draw_enemy_sprite(t_item *obj, t_draw_data data, t_player player, SDL_Surface *surface);

void    				move_enemy_to_player(t_item *enemy, t_vector player_pos);

void 					quickSort(t_item **headRef, t_player *player);

void					line(SDL_Surface *surface, t_point start, t_point end, int color);

t_vector				point_of_intersec(t_vector p1, t_vector p2, t_vector p3, t_vector p4);
float					side_of_a_point(t_vector p, t_vector s, t_vector end);
int						box_intersection(t_vector p1, t_vector p2, t_vector p3, t_vector p4);
t_scaler				init_scaler(int n, t_point curr, t_point dst);

void					rest_of_the_action_shit(t_pr *m, Uint8 *menu, t_sdl *sdl, t_read_holder *holder);
void					draw_hud(t_sdl *sdl, t_player *player);
t_projectile			*create_projectile(t_player player);
void					delete_projectile(t_projectile **head, t_projectile *proj);
Uint8					move_projectile(t_projectile *proj);
void 					add_projectile(t_projectile **head, t_projectile *new);
void					draw_projectile(t_projectile *proj, t_draw_data data, t_player player, SDL_Surface *surface);

void 					draw_image(SDL_Surface *screen, SDL_Surface *img, t_point pos, t_point size);
void 					draw_image_with_criteria(SDL_Surface *screen, SDL_Surface *img, t_point pos, t_point size, t_draw_data data);

void					delete_projectiles(t_projectile *head);
void 					list_light(t_light	**arr, unsigned arr_size);
void					draw_skybox(SDL_Surface *dst, SDL_Surface *src, int x, int y, int end_y, t_player player);
#endif
