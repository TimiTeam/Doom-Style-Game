/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 21:30:46 by mshpakov          #+#    #+#             */
/*   Updated: 2019/10/16 14:44:26 by mshpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H

# ifdef __APPLE__

#  include <SDL.h>
#  include <SDL_mixer.h>
#  include <SDL_image.h>
#  include <SDL_ttf.h>
#  define SCROLL_UP					-1
#  define SCROLL_DOWN				1

# elif __linux

#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
#  include <SDL2/SDL_ttf.h>
#  include <SDL2/SDL_mixer.h>
#  define SCROLL_UP					1
#  define SCROLL_DOWN				-1

# endif

# include "../libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>

# define SUCCESS					0
# define FAIL						1

# define TRUE						1
# define FALSE						0

# define WHITE						0xffffff
# define GRAY						0xa9a9a9
# define PURPLE						0x621295
# define RED						0xc40b13
# define ORANGE						0xf69314
# define LIGHT_GRAY					0xdadddf
# define MILKY						0xffffd2
# define BABY_PINK					0xfcbad3
# define SOFT_PURPLE				0xAA96DA
# define SOFT_BLUE					0xa8d8ea
# define DARK_GRAY					0x222831
# define DARK_ORANGE				0xb55400
# define SOFT_GRAY					0x393e46
# define ALMOST_WHITE				0xeeeeee
# define DARK_PURPLE				0x681e21
# define YELLOW						0xfff000
# define BROWN						0x794913
# define NAVY						0x000080
# define GREEN						0x4AA21E

# define SOFT_ORANGE				0xF4511E
# define SOFT_TEAL					0x00897B

# define LIT_COLOR					WHITE

# define CONVEX_COLOR				0x207561
# define CONCAVE_COLOR				0xDA4302
# define ACTIVE_SEC_COLOR			0x3949AB
# define DOOR_COLOR					ORANGE
# define ELEV_COLOR					BABY_PINK
# define TMP_COLOR					SOFT_PURPLE
# define EMPTY_COLOR				DARK_GRAY
# define FULL_COLOR					BROWN
# define SEC_NOD_COLOR				NAVY
# define FULL_W_CLR					WHITE
# define EMPTY_W_CLR				GREEN
# define WINDOW_W_CLR				RED
# define TRANSPARENT_W_CLR			PURPLE
# define LIT_WALL_CLR				NAVY

/*
** STR = PRINTS OUT NAME OF MACRO; XSTR = PRINTS OUT VALUE OF MACRO
*/

# define STR(x)						#x
# define XSTR(x)					STR(x)

# define W_W						1000
# define W_H						850

# define WIN_NAME					"DOOM-NUKEM BUILDER"
# define FONT_NAME              	"./media/BebasNeue-Regular.ttf"
# define ED_CLR		DARK_GRAY

# define LEVELS						"Levels"
# define TEXTURES					"Textures"
# define ITEMS						"Items"
# define TOTAL_SECTIONS				3

# define MAX_LEVELS					5

# define R_VECTORS					1
# define R_WALLS					2
# define R_SECS						3
# define R_PLR						4

# define MIN_VERTEX_ID				0
# define MAX_VERTEX_ID				400

# define MIN_N_WALLS				0
# define MAX_N_WALLS				400

# define MIN_N_SECS					1
# define MAX_N_SECS					150

# define MIN_N_TXTRS				5
# define MAX_N_TXTRS				80

# define MIN_HEIGHT					-100
# define MAX_HEIGHT					100

# define MAX_SEC_WALLS				40

# define MAX_SEC_ITEMS				40
# define MAX_ITEMFULL				50

# define ASSET_FILE             	"./game_info.txt"

# define REG_IN      				(int)0
# define REG_LEFT        			(int)1
# define REG_RIGHT       			(int)2
# define REG_BOTTOM      			(int)4
# define REG_TOP         			(int)8

# define NODE_EMPTY					-1
# define NODE_FULL					-2
# define NODE_SEC					-3

# define N_MODES					6

# define N_MM_BTNS					2

# define TXTR_RECG					0
# define TXTR_RECG_L				1
# define TXTR_RECY					2
# define TXTR_RECY_L				3
# define TXTR_PANEL_GR				4
# define TXTR_PANEL_GR_L			5
# define TXTR_ADD_MAP				6
# define TXTR_ADD_MAP_L				7
# define TXTR_YES					8
# define TXTR_NO					9
# define TXTR_MOVE					10
# define TXTR_MOVE_L				11
# define TXTR_DRAW					12
# define TXTR_DRAW_L				13
# define TXTR_DISTORT				14
# define TXTR_DISTORT_L				15
# define TXTR_ISO					16
# define TXTR_ISO_L					17
# define TXTR_SEC					18
# define TXTR_SEC_L					19
# define TXTR_WALL					20
# define TXTR_WALL_L				21
# define TXTR_DOOR_ADD				22
# define TXTR_DOOR_ADD_L			23
# define TXTR_DOOR_DEL				24
# define TXTR_DOOR_DEL_L			25
# define TXTR_PLR					26
# define TXTR_PLR_L					27
# define TXTR_SAVE					28
# define TXTR_SAVE_L				29
# define TXTR_EXIT					30
# define TXTR_EXIT_L				31
# define TXTR_BACK					32
# define TXTR_BACK_L				33
# define TXTR_DEL					34
# define TXTR_DEL_L					35
# define TXTR_EDIT					36
# define TXTR_EDIT_L				37
# define TXTR_UP					38
# define TXTR_UP_L					39
# define TXTR_DOWN					40
# define TXTR_DOWN_L				41
# define TXTR_COIN					42
# define TXTR_KEY					43
# define TXTR_OBJECT				44
# define TXTR_ENEMY					45
# define TXTR_SUPER					46
# define TXTR_HEALTH				47
# define TXTR_AMMO					48
# define TXTR_WEAPON				49
# define TXTR_LIGHT					50
# define TXTR_DOOR					51
# define TXTR_NORM					52
# define TXTR_NORM_L				53
# define TXTR_DSEC					54
# define TXTR_DSEC_L				55
# define TXTR_ELEV					56
# define TXTR_ELEV_L				57
# define TXTR_CEIL					58
# define TXTR_CEIL_L				59
# define TXTR_SKY					60
# define TXTR_SKY_L					61
# define TXTR_FL_SAFE				62
# define TXTR_FL_SAFE_L				63
# define TXTR_FL_UNSAFE				64
# define TXTR_FL_UNSAFE_L			65

# define N_TXTR						66

# define DRAG_BTN					0
# define DISTORT_BTN				1
# define DRAW_BTN					2
# define SEC_BTN					3
# define WALL_BTN					4
# define DOOR_ADD_BTN				5
# define SETTINGS_BTN				6
# define PLR_BTN					7
# define ISO_BTN					8
# define SAVE_BTN					9
# define BACK_BTN					10

# define DESELECT_BTN				0
# define DEL_SEC_BTN				1
# define F_UP_BTN					2
# define F_DOWN_BTN					3
# define C_UP_BTN					4
# define C_DOWN_BTN					5
# define FT_EDIT_BTN				6
# define CT_EDIT_BTN				7
# define B_ITEM_EDIT				8
# define B_ITEM_DEL					9
# define B_COIN						10
# define B_KEY						11
# define B_OBJECT					12
# define B_ENEMY					13
# define B_SUPER_BONUS				14
# define B_HEALTH					15
# define B_AMMO						16
# define B_WEAPON					17
# define B_LIGHT					18
# define B_NORM						19
# define B_DSEC						20
# define B_ELEV						21
# define B_CEIL						22
# define B_SKY						23
# define B_FL_SAFE					24
# define B_FL_UNSAFE				25

# define TOT_EDIT_BTNS				26

# define WT_EDIT_BTN				1
# define PORT_BTN					2

# define S_BACK_BTN					0
# define S_WT_BTN					1
# define S_FT_BTN					2
# define S_CT_BTN					3
# define S_DT_BTN					4
# define S_TT_BTN					5
# define S_F_UP_BTN					6
# define S_F_DOWN_BTN				7
# define S_C_UP_BTN					8
# define S_C_DOWN_BTN				9

# define TOT_SETTINGS_BTNS			10

# define GRID_SIZE					150

# define SEC_CONVEX_CLOSED			1
# define SEC_CONCAVE_CLOSED			0
# define SEC_OPEN					-1

# define NORMAL						-1
# define SEC_SEARCH					0
# define SEC_EDIT					1
# define INP						2
# define VECTOR_EDIT				3
# define WALL_SEARCH				4
# define WALL_EDIT					5

# define COIN						0
# define KEY						1
# define OBJECT						2
# define ENEMY						3
# define SUPER_BONUS				4
# define HEALTH						5
# define AMMO						6
# define WEAPON						7
# define LIGHT						8
# define TOTAL_TYPES				9

enum						e_select
{
	fc_select,
	w_select,
	s_select,
	t_select,
	sel_i_select,
	st_select,
	last_select,
	world_select,
	i_select,
	def_t_select
};

enum						e_modes
{
	mode_main_menu,
	mode_levels,
	mode_editor,
	mode_textures,
	mode_sel_item,
	mode_settings
};

enum						e_screen
{
	screen_empty,
	screen_node,
	screen_wall,
	screen_sector,
	screen_pl_start,
	screen_pl_end
};

enum						e_default_txtr
{
	def_wall_t,
	def_floor_t,
	def_ceil_t,
	def_door_t,
	def_tran_t
};

enum						e_sec_type
{
	normal,
	door,
	elevator
};

enum						e_sec_ceil
{
	ceiling,
	skybox
};

enum						e_sec_floor
{
	safe,
	unsafe
};

enum						e_wall_type
{
	filled,
	empty,
	window,
	transparent
};

typedef struct				s_rgb
{
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
}							t_rgb;

typedef struct				s_vec
{
	int						x;
	int						y;
}							t_vec;

typedef struct				s_vec_d
{
	double					x;
	double					y;
}							t_vec_d;

typedef struct				s_vec_f
{
	float					x;
	float					y;
}							t_vec_f;

typedef struct				s_poly
{
	int						area;
	int						color;
	t_vec					*a;
	t_vec					*b;
	t_vec					*c;
	t_vec					*d;
}							t_poly;

typedef struct				s_line
{
	t_vec					p0;
	t_vec					p1;
}							t_line;

typedef struct				s_rec
{
	int						x;
	int						y;
	int						w;
	int						h;
}							t_rec;

typedef struct				s_txtb
{
	t_rec					box;
	char					h_center;
	int						text_color;
}							t_txtb;

typedef struct				s_grid
{
	t_rec					box;
	signed char				nod[GRID_SIZE][GRID_SIZE];
	float					scl;
	t_vec					p[2];
}							t_grid;

typedef struct				s_btn
{
	char					vis_lit_on[3];
	char					fake_lit;
	t_rec					box;
	int						text_color;
	char					*text;
	int						reg_i;
	int						lit_i;
}							t_btn;

typedef struct				s_sdl
{
	SDL_Window				*window;
	SDL_Renderer			*rend;
	t_vec					mouse;
	TTF_Font				*font;
}							t_sdl;

typedef struct				s_scr
{
	int						color;
	char					is;
	unsigned short			n;
}							t_scr;

typedef struct				s_prog
{
	t_scr					**screen;
	int						m_id;
	int						last;
	char					redraw;
	short					btn_lit;
	short					btn_on;
	short					zoom;
	t_vec					move;
	t_vec					click;
	SDL_Texture				**t;
	struct s_mode			*modes;
	int						n;
}							t_prog;

typedef struct				s_wall
{
	unsigned short			v1;
	unsigned short			v2;
	signed char				type;
	short					txtr;
}							t_wall;

typedef struct				s_item
{
	t_vec					p;
	int						id;
}							t_item;

typedef struct				s_sec
{
	int						*s_walls;
	int						*v;
	int						fl;
	int						ceil;
	short					fl_t;
	short					ceil_t;
	t_item					*items;
	unsigned short			n_it;
	unsigned short			n_w;
	unsigned short			n_v;
	char					status;
	char					type[3];
}							t_sec;

typedef struct				s_texture
{
	char					*name;
	char					*full_p;
	SDL_Texture				*sdl_t;
	t_vec					size;
}							t_texture;

typedef struct				s_world
{
	char					*name;
	char					*full_p;
	t_sec					*sec;
	t_wall					*walls;
	t_vec					*vecs;
	t_vec					p_start;
	t_vec					p_end;
	short unsigned			n_s;
	short unsigned			n_v;
	short unsigned			n_w;
}							t_world;

typedef struct				s_section
{
	short					id;
	char					*path;
	char					*extension;
	short					n_files;
	char					**tab;
	char					**names;
	int						*extra;
}							t_section;

typedef struct				s_it_f
{
	char					*name;
	char					*full_p;
	int						type;
}							t_it_f;

typedef struct				s_media
{
	short					w;
	char					paths[TOTAL_SECTIONS][20];
	char					extensions[TOTAL_SECTIONS][10];
	t_texture				*txtr;
	t_world					*worlds;
	t_it_f					*it_f;
	short unsigned			n_itf;
	short unsigned			n_worlds;
	short unsigned			n_t;
}							t_media;

typedef struct				s_mode
{
	unsigned short			n_btn;
	t_btn					*btn;
	int						(*input)(t_sdl*, t_grid*, t_media *, t_prog *);
	unsigned short			(*update)(t_sdl*, t_grid*, t_media *, t_prog *);
	void					(*render)(t_sdl*, t_grid*, t_media *, t_prog *);
}							t_mode;

typedef struct				s_value
{
	char					*text;
	int						t;
	char					m_p;
}							t_value;

int							start_sdl(t_sdl *sdl);
t_sdl						*get_sdl(void);
SDL_Texture					*load_texture(char *name, SDL_Renderer *rend, \
t_vec *size);
void						free_sdl(t_sdl *sdl, char proper);
void						quit_sdl(char proper);

void						r_mainmenu(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
unsigned short				u_mainmenu(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
int							i_mainmenu(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
void						r_levels(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
unsigned short				u_levels(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
int							i_levels(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
int							i_editor(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
unsigned short				u_editor(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
void						r_editor(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
int							i_textures(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
unsigned short				u_textures(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
void						r_textures(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
int							i_sel_item(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
unsigned short				u_sel_item(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
void						r_sel_item(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
void						r_settings(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
unsigned short				u_settings(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
int							i_settings(t_sdl *sdl, t_grid *grid, t_media *media,
							t_prog *prog);
t_media						*get_assets(void);
void						free_media(t_media *media);
unsigned short				rewrite_media(t_media *media);
unsigned short				rewrite_levels(t_media *media);
unsigned short				init_modes(t_media *media, t_prog *prog);
void						free_modes(t_mode *modes);
void						refresh_level_list(t_media *media, t_mode *mode);
void						render_btns(t_prog *prog, t_sdl *sdl);
void						render_btn_big(t_btn *button, t_sdl *sdl,
							SDL_Texture **t);
void						render_btn(t_btn *button, t_sdl *sdl,
							SDL_Texture **t);
unsigned short				manage_btn(t_media *media, t_prog *prog,
							t_grid *grid, t_vec mouse);
unsigned short				btn_press(t_prog *prog, t_grid *grid,
							t_media *media, int state);
void						turn_btn_on(t_prog *prog, t_grid *grid);
void						turn_btns_off(t_prog *prog);
unsigned short				btn_light(t_vec mouse, t_btn *btn, int n_btn,
							t_prog *prog);
unsigned short				btn_refresh(t_prog *prog, int state);
t_btn						*init_btn(int n_btn);
void						free_btn(t_btn *btn, int n);
void						get_btn(int state, t_mode *mode);
void						change_heights(int b, t_sec *sec);
void						edit_wall_type(int btn_on, t_world *world);
void						prep_texture_edit(t_world *world, t_prog *prog,
							int n_t);
void						zoom_grid(t_prog *prog, t_vec mouse, t_grid *grid);
void						move_grid_drag(t_prog *prog, t_vec mouse,
							t_grid *grid);
unsigned short				move_grid_keys(t_prog *prog, t_grid *grid);
void						move_player(t_prog *prog, t_vec mouse, t_grid *grid,
							t_world *world);
void						move_vector(t_prog *prog, t_vec mouse, t_grid *grid,
							t_world *world);
void						draw_dot(int x, int y, int color,
							SDL_Renderer *rend);
void						get_rgb(unsigned char *r, unsigned char *g,
							unsigned char *b, int color);
unsigned short				mouse_over(t_rec box, t_vec mouse);
void						render_grid(t_world world, t_grid *grid,
							t_prog *prog, t_vec mouse);
void						render_grid_iso(t_world world, t_grid *grid,
							t_prog *prog);
void						draw_dot2(int x, int y, t_scr s, t_scr **screen);
void						draw_line2(t_line l, t_scr s, t_scr **screen);
void						draw_circle_fill2(t_vec c, int radius, t_scr s,
							t_scr **screen);
void						draw_node(t_vec c, int r, t_scr s, t_scr **screen);
void						thick_l(t_line l, t_scr s, int r,
							t_scr **screen);
unsigned short				fill_polygon(t_vec *p, int n_p, t_scr **screen,
							int color);
void						free_prog(t_prog *prog);
t_prog						*get_prog(SDL_Renderer *rend);
void						render_screen(SDL_Renderer *rend, t_scr **screen);
unsigned short				add_world(t_world **worlds, short n_worlds,
							char *ext, char *path);
void						upd_sec(t_sec *sec, t_wall *walls, t_vec *vecs,
							int n_s);
t_vec						find_node(int p_x, int p_y, t_grid *grid);
t_vec_d						make_iso(t_vec v, int z);
void						rend_box(t_rec box, SDL_Texture *t,
							SDL_Renderer *rend);
unsigned short				add_wall(t_wall **walls, short n_w, int one,
							int two);
char						*lines(int id, int i, int w_type);
void						render_edit_menu(t_sdl *sdl, t_media *media,
							t_prog *prog, t_world *w);
t_rec						layout(char i, char n);
void						render_values(t_value *values, t_sdl *sdl,
							t_prog *prog, t_media *media);
void						free_values(t_value *values, int n);
t_value						*init_values(int n);
void						add_door(t_world *world, int id, t_grid *grid);
void						delete_wall(int id, t_world *world);
void						draw_item(int type, t_rec box, SDL_Renderer *rend,
							SDL_Texture **t);
void						delete_item(t_sec *sector, int id);
void						move_item(t_prog *prog, t_vec mouse, t_grid *grid,
							t_sec *sector);
void						add_item(int default_id, t_vec mouse, t_grid *grid,
							t_sec *sector);
int							find_def_item(int type, t_it_f *it_f, int n);
void						fill_grid(int n_v, t_vec *vecs, t_grid *grid);
void						fill_grid_items(t_sec *sector, t_grid *grid);
void						clean_grid(t_grid *grid);
t_grid						*get_grid(void);
void						grid_re(t_grid *grid, t_media *media, int state,
							int sector);
short						find_vec(t_vec *vecs, t_vec p, int n);
short						find_wall(short one, short two, t_wall *walls,
							short n_w);
unsigned short				dot_in_sector(int x, int y, t_vec *p, int n);
int							nod_in_sec(t_vec grid_p, t_world *world);
int							mouse_in_stor(t_vec p, t_world *world,
							t_grid *grid);
int							sector_closed(int *tmp, int n);
unsigned short				sec_is_convex(t_vec *vecs, int *v, int n);
void						delete_world(t_media *media, int id);
void						free_world(t_world *world);
void						copy_world(t_world *new, t_world *old);
void						delete_sector(int id, t_world *world);
void						copy_sector(t_sec *new, t_sec *old);
void						free_sector(t_sec *sector);
void						delete_vector(int id, t_world *world);
void						validate_media(t_media *media);
int							my_rename(const char *oldname, const char *newname);
unsigned					open_for_read(const char *path, int *fd);
unsigned					open_for_write(const char *path, int *fd);
unsigned					close_file(int fd);
int							get_sec_v(t_sec *sector, t_wall *walls);
int							clamp(int n, int min, int max);
float						clamp_f(float n, float min, float max);
t_vec						scl(t_vec vec, int scl);
t_vec						sub_one_from_two(t_vec one, t_vec two);
int							get_max(int one, int two);
int							get_min(int one, int two);
unsigned short				within(int value, int min, int max);
int							select_it(char set_get_unset, unsigned short id,
							int value);
int							lit_it(char set_get_unset, unsigned short id,
							int value);
char						*get_full_p(char *name, char *ext, char *path);
void						bounding_box(t_vec *min, t_vec *max, t_vec *p,
							int n_p);
void						*realloc_tab(void *old_tab, size_t new_size, size_t
							old_size);
void						free_tab(void **tab, int size);
void						swap_ints(int *one, int *two);
void						write_txt(char *str, t_sdl *sdl, t_txtb textbox);
void						turn_btns_off(t_prog *prog);
unsigned short				add_sector(t_sec **sec, short n_s);
unsigned short				add_vec(t_vec **vecs, short n_v, t_grid *grid,
							short i);
float						get_slope(t_vec p1, t_vec p2);
t_vec_f						lines_intersect(t_line a, t_line b,
							unsigned short *i);
float						get_perp_slope(t_vec p1, t_vec p2);
unsigned short				intersects(t_vec p, t_vec l1, t_vec l2);
int							find_wall_inter(t_vec p, t_world world);
t_vec						*get_point_at_d(t_vec origin, int dist, int slope);
void						vec_set(t_vec *vec, int x, int y, int n);
unsigned short				vec_same(t_vec one, t_vec two);
void						bubble_sort(int *tab, int n);
void						pair_sort(int *a, int n);
char						*get_input(char *init, char change);
void						switch_mode(t_prog *prog, int new_m_id,
							int new_state);
void						drawing(t_world *world, t_prog *prog, t_grid *grid,
							t_vec mouse);
unsigned short				already_in_sector(int id, int *vecs, int n_v);
unsigned short				can_place_v(t_vec v, t_world world, t_grid *grid,
							int wall);
unsigned short				add_secwall(int **secwalls, short n_swalls,
							int wall);
unsigned short				add_sector_v(int **v, short n_v, int id);
void						normal_st(t_prog *prog, t_vec mouse, t_grid *grid,
							t_world *world);
void						wall_search_st(t_prog *prog, t_vec node,
							t_grid *grid, t_world *world);
void						sec_search_st(t_prog *prog, t_vec mouse,
							t_grid *grid, t_world *world);
void						sec_edit_st(t_prog *prog, t_vec mouse, t_grid *grid,
							t_media *media);
int							s_items(t_sec *sec, char *l);
char						*get_name(int i);
unsigned short				edit_texture(int fl_ceil, int n_t, t_texture *txtr,
							t_world *world);
t_vec						get_arrow_input(SDL_Keycode key, t_vec old);
void						edit_item_name(int n_itf, t_it_f *it_f,
							t_world *world);
void						render_cursor(SDL_Renderer *rend, t_vec mouse,
							SDL_Texture **t, int txtr_id);
void						render_item_info(t_media *med, t_sdl *sdl,
							t_mode *mode, SDL_Texture **t);
void						place_player_icons(t_world world, t_grid *grid,
							t_sdl *sdl);
unsigned short				save_media(t_media *media, t_prog *prog);
unsigned short				mode_change(t_prog *prog, t_media *media,
							t_grid *grid, int fl_ceil);
unsigned short				return_to_levels(t_prog *prog, t_media *media);
void						draw_itms(SDL_Renderer *rend, t_media *media,
							t_grid *grid, SDL_Texture **t);
unsigned short				ingrid(t_vec p);
void						clean_screen(t_scr **screen);
void						place_player(t_world world, t_grid *grid,
							t_scr **screen, int radius);
void						delete_double_walls(t_world *world);
void						delete_unused_walls(t_world *world);
void						delete_unused_v(t_world *world);
void						delete_double_v(t_world *world);
void						replace_vector(int to_replace, int new,
							t_world *world);
void						replace_wall(int to_replace, int new,
							t_world *world);
void						validate_clockwise(t_world *world, int sec);
unsigned short				write_section(int fd, t_media *media, int section);
unsigned short				write_level(int fd, t_world world);
unsigned short				write_level_section(int fd, t_world world,
							int section);
short						identify_section(const char *line);
char						*identify_path(const char *line);
char						*identify_extension(const char *line);
unsigned					get_map(t_world *world, unsigned short world_no);
unsigned short				count_w(char const *s, int n);
unsigned short				get_n(char *line, unsigned short min,
							unsigned short max);
int							read_item_type(char *line);
void						read_section_names(char *line, t_section *section);
unsigned short				empty_sect(t_section *section);
unsigned short				free_section(t_section *section);
unsigned short				refresh_section(t_section *section);
unsigned					update_media(t_media *media, t_section *section);
unsigned					read_levels(t_media *media, t_section *section);
int							s_walls(t_sec *sector, char *line, int n_w);
void						get_walls(t_wall *wall, char *line, t_vec p);
int							fl_ceil(t_sec *sector, char *line);
unsigned short				init_vec(char *line, t_world *world);
unsigned short				init_sec(char *line, t_world *world);
unsigned short				init_walls(char *line, t_world *world);
unsigned					read_line(char *str, unsigned short status, t_world
							*world, unsigned short world_no);
unsigned short				add_media_elements(t_world *world, t_grid *grid,
							short *wall_id_done, int *f_s_l);
void						existing_vec(short *wall_id_done, int *f_s_l,
							t_world *world, t_grid *grid);
void						done_condition(t_grid *grid, int *tab, short done);
void						set_min1(int *one, int *two);
void						update_min_max(t_vec *min, t_vec *max, t_vec p);
t_vec						transform_to_screen(t_vec old, t_grid *grid);
void						highlight_sec_nod(t_vec *p, int n_w, t_grid *grid);
void						zoom_to_box(t_grid *grid, t_vec *vecs, int n_vecs);
t_vec						*make_vec_tab(t_sec *sector, t_vec *vecs,
							int n_vecs);
float						get_scl_to_sector(int size, int max_w, int max_h);
void						get_min_scl(float *res_min_scl);
void						edit_mng_btn(t_prog *prog, t_media *m, t_grid *grid,
							int s);
unsigned short				distribute_btn_v(t_btn *btn, t_vec from_to,
							t_rec box, int padding);
unsigned short				distribute_btn_h(t_btn *btn, t_vec from_to,
							t_rec box, int padding);
void						get_txtr_btn_boxes(t_btn *btn, int n_t, int scroll);
unsigned short				add_wall_door(t_wall **walls, short n_w, int one,
							int two);
unsigned short				levels_btn(t_btn *btn, t_world *worlds,
							int n_worlds);
unsigned short				sel_item_btn(t_btn *btn, t_it_f *it_f, int n_itf);
unsigned short				textures_btn(t_btn *btn, int n_t);
unsigned short				main_menu_btn(t_btn *btn);
void						set_false(char *one, char *two);
unsigned short				check_for_light(t_media *media, int id, int sec);
int							clip_line(t_line *l);
unsigned short				settings_btn(t_btn *btn, int n);
t_rec						settings_boxes(int h_box_val_btn, int id);
void						change_def_heights(int b);
void						change_def_textures(t_prog *prog, int n_t);
unsigned short				edit_def_texture(int n_t, t_texture *txtr);
int							default_texture(char set_get, char of_what,
							int value);
int							default_heights(char set_get, char of_what,
							int value);
void						add_to_media(t_grid *grid, t_world *world,
							int wall);
void						make_continuous(t_sec *sec, t_world *world,
							int sec_no);
unsigned short				will_inter(t_world *world, t_vec one, t_vec two);
void						get_new_p(t_vec *new, t_grid *grid, t_world *world);
char						*get_txtr_name(int i);
void						settings_mng_btn(t_prog *prog, t_media *media);
void						prep_settings(t_prog *prog, t_grid *grid,
							t_media *media);
unsigned short				break_wall(t_world *world, int vec, int wall,
							int s);
void						get_sec_boxes(t_mode *m);
t_rec						sec_descr_boxes(int row, int col);
void						light_sec_types(t_sec sec, t_prog *prog);
void						write_wall_type(int type, int fd);

#endif
