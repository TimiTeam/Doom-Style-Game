#ifndef __SECTOR_WORKER_H
#define __SECTOR_WORKER_H

#define	MAX_PORTALS 32
#include "sdl_head.h"
#include "libft.h"
#include <fcntl.h>

enum 				wall_type
{
	fieled_wall,
	empty_wall
};

typedef struct		s_line
{	
	t_point			start;
	t_point			end;
}					t_line;

typedef	struct		s_vector
{	
	float			x;
	float			y;
	float			z;
}					t_vector;

typedef	struct		s_wall
{
	t_vector		start;
	t_vector		end;
	enum wall_type	type;
	unsigned short	id;
	struct s_sector	*sectors[2];
	SDL_Surface		*texture;
}					t_wall;

typedef struct		s_sector
{	
	t_wall			**wall;
	unsigned short 	sector;
	unsigned short	n_walls;
	signed short	portals[MAX_PORTALS];
	SDL_Surface		*floor_tex;
	SDL_Surface		*ceil_tex;
	float			floor;
	float			ceil;
	struct s_sector	*next;
}					t_sector;

t_sector			*new_sector();
t_sector			*crate_new_sector(float	floor, float ceil);
void				add_next_sector(t_sector **main, t_sector *next);

void				add_wall_to_sector(t_sector *sec,t_wall *wall);
void				create_and_add_wall_to_sector(t_sector *sec, float x1, float y1, float x2, float y2);

void				delete_sectors(t_sector *sec);
void				delete_walls(t_wall **wals, unsigned count);
void				list_sectors(t_sector *head);
void				list_walls(t_wall **walls, int size);

#endif