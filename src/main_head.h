#ifndef __MAIN_HEAD_H
#define __MAIN_HEAD_H

#include <fcntl.h>
#include "sdl_head.h"
#include "sectors.h"
#include "scaler.h"

#define H 1000
#define W 1200
#define MAX_SECTORS 128

typedef struct		s_draw_data
{
	float 			start;
	float			end;
	int 			*ytop;
	int				*ybottom;
}					t_draw_data;


typedef struct		s_plyer
{	
	t_vector		pos;
	t_sector 		*curr_sector;
	float			yaw;
	float			height;
	float			angle;
	double			sin_angl;
	double			cos_angl;
	float 			hfov;
	float 			vfov;
	t_point			half_win_size;
}					t_player;

#define min(a,b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((t_vector) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })

int 				Scaler_Next(struct Scaler* i);
void 					textLine(int x, int y1,int y2, struct Scaler ty,unsigned txtx, SDL_Surface *surface, SDL_Surface *image);

#endif