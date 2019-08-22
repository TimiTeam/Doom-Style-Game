#ifndef __MAIN_HEAD_H
#define __MAIN_HEAD_H

# include <fcntl.h>
# include <pthread.h>
# include "sdl_head.h"
# include "sectors.h"

#define W 1240
#define H 980
#define MAX_SECTORS 128

static float m_vfov = 0.2f;
static float m_hfov = 0.73f*H/W;
static int h_w = W >> 1;
static int h_h = H >> 1;

typedef struct		s_draw_data
{
	float 			start;
	float			end;
	int 			diff_ceil;
	int 			diff_floor;
	int 			*ytop;
	int				*ybottom;
}					t_draw_data;


typedef struct		s_plyer
{	
	t_sector 		*curr_sector;
	t_vector		pos;
	t_point			half_win_size;
	float 			speed;
	float			yaw;
	float			angle;
	float			sin_angl;
	float			cos_angl;
	float 			hfov;
	float 			vfov;
	int				height;
	char			fall;
	unsigned short	jump;
}					t_player;

typedef struct 		s_super_data
{
	t_sector 		*sec;
	t_wall 			wall;
	t_player 		player;
	t_sdl 			*sdl;
	t_draw_data 	data;
}					t_super_data;

#define CeilingFloorScreenCoordinatesToMapCoordinates(mapY, screenX, screenY, X, Z, player) \
            Z = (mapY)* H * m_hfov /  ((h_h - (screenY))); \
        	X = (Z) * (h_w - (screenX)) / ((m_vfov * H)); \
        	RelativeMapCoordinatesToAbsoluteOnes(X,Z,player);

#define RelativeMapCoordinatesToAbsoluteOnes(X,Z,player) \
            float rtx = (Z) * player.cos_angl + (X) * player.sin_angl; \
        	float rtz = (Z) * player.sin_angl - (X) * player.cos_angl; \
         	X = rtx + player.pos.x; Z = rtz + player.pos.y; \

#define Scaler_Init(a,b,c,d,f) \
    { d + (b-1 - a) * (f-d) / (c-a), ((f<d) ^ (c<a)) ? -1 : 1, \
      fabs(f-d), abs(c-a), (int)((b-1-a) * abs((int)(f-d))) % abs(c-a) }

typedef struct 		Scaler {
	int result, bop, fd, ca, cache;
} 					Scaler;


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


int 			Scaler_Next(Scaler *i);

void 			textLine(int x, int y1,int y2, Scaler ty,unsigned txtx, SDL_Surface *surface, SDL_Surface *image);

void 			draw_floor_or_ceil(SDL_Surface *dst, SDL_Surface *src, int x, int start_y, int end_y, int diff_height, t_player player);

#endif
