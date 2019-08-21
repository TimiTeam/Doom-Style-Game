#ifndef __SECTORS_H
#define __SECTORS_H
#include "sector_worker.h"

typedef struct 		s_read_holder
{
	SDL_Surface		**textures;
	t_wall			**walls;
	int				text_count;
	int				vect_count;
	int				wall_count;
	int 			fd;
}					t_read_holder;

t_sector		*read_map(char *pth, t_read_holder *holder);

//t_sector		*read_map(char *pth);

#endif