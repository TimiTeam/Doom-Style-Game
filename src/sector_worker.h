#ifndef __SECTOR_WORKER_H
#define __SECTOR_WORKER_H

#define	MAX_PORTALS 16
#define	MAX_TEXTURES 8
#define NON -1
#include "sdl_head.h"
#include "libft.h"
#include <fcntl.h>

enum 					wall_type
{
	filled_wall,
	empty_wall,
	door
};

enum 					gun_type
{
	pistol,
	shotgun,
	plasmagun
};

enum 					item_type
{
	object,
	coin,
	super_bonus,
	health,
	gun,
	ammo,
	key,
	enemy
};

enum 					item_state
{
	waiting,
	walk,
	action,
	taking_damage,
	die
};


typedef struct			s_line
{
	t_point				start;
	t_point				end;
}						t_line;

typedef	struct			s_vector
{	
	float				x;
	float				y;
	float				z;
}						t_vector;

typedef struct			s_projectile
{
	t_vector			pos;
	float				anglecos;
	float				anglesin;
	float				speed;
	float				damage;
	float				yaw;
	SDL_Surface			*sprite;
	struct s_sector		*curr_sector;
	struct s_projectile	*next;
}						t_projectile;

typedef	struct 			s_animation
{
	SDL_Surface			*texture[MAX_TEXTURES];
	float				current_text;
	unsigned char 		max_textures;
}						t_animation;

typedef struct 			s_item
{
	t_animation			states[5];
	float				curr_frame;
	struct s_sector		*sector;
	float				speed;
	int					health;
	int					damage;
	int					ammo;
	struct s_item		*next;
	t_vector			pos;
	enum item_state		curr_state;
	enum item_type 		type;
	enum gun_type		gun_type;
	unsigned			id;
	unsigned 			size;
	float				dist_to_player;
	unsigned char		is_dying;
	unsigned char		players_hit;
}						t_item;

typedef	struct			s_wall
{
	struct s_sector		*sectors[2];
	SDL_Surface			*texture;
	t_vector			start;
	t_vector			end;
	enum wall_type		type;
	unsigned short		id;
	struct s_wall		*portal_ptr;
	unsigned char		close;
	unsigned char		opening;
}						t_wall;

typedef struct			s_sector
{
	t_wall				**wall;
	t_wall				*portals[MAX_PORTALS];
	t_wall 				*doors[MAX_PORTALS];
	SDL_Surface			*floor_tex;
	SDL_Surface			*ceil_tex;
	t_item				*items;
	struct s_sector		*next;
	t_projectile		*projectiles;
	float				floor;
	float				ceil;
	unsigned short 		sector;
	unsigned short		n_walls;
}						t_sector;

t_sector				*new_sector();
t_sector				*crate_new_sector(float	floor, float ceil);
t_item					*new_item();
t_item					*create_new_item(int x, int y);
	
void					add_next_sector(t_sector **main, t_sector *next);
void 					add_next_item(t_item **head, t_item *new); 
void 					from_list_to_another_list(t_item **current_list, t_item **next_list, t_item *elem);
	
void					delete_sectors(t_sector *sec);
void					delete_walls(t_wall **wals, unsigned count);
void					delete_items_list(t_item *items);
void					delete_items_list_with_animation(t_item *items);
void 					delete_item(t_item **item);
void					delete_item_by_ptr(t_item **head, t_item *item);
	
void					list_sectors(t_sector *head);
void					list_walls(t_wall **walls, int size);
void					list_items(t_item *items);
void 					swap_items(t_item *elem1, t_item *elem2);

#endif