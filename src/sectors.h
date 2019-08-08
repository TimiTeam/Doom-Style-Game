#ifndef __SECTORS_H
#define __SECTORS_H
#include "sector_worker.h"

typedef struct	s_draw_data
{
	int 		*ytop;
	int			*ybottom;
	int			start;
	int			end;
}				t_draw_data;


t_sector			*read_map(char *pth);

#endif