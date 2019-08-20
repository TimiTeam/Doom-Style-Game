#include "main_head.h"

void 			draw_floor_or_ceil(SDL_Surface *dst, SDL_Surface *src, int x, int y, int end_y, int diff_height, t_player player)
{
	float		mapx;
	float		mapz;
	float		tmp;
	Uint32		pix;
	unsigned 	tx;
	unsigned	txtz;


	while(y < end_y)
	{
		mapz = diff_height * H * m_hfov / (h_h - y);
		mapx = mapz * (h_w - x) / (m_vfov * H);
		tmp = mapx;
	
		mapx = mapz * player.cos_angl + tmp * player.sin_angl;
		mapz = mapz * player.sin_angl - tmp * player.cos_angl;

		tx = (mapx + player.pos.x) * 50;
		txtz = (mapz + player.pos.y) * 50;
		//tx = tx >= src->w ? src->w - 1 : tx;
		//txtz = txtz >= src->h ? src->h - 1 : txtz;
	
		pix = get_pixel(src, tx % src->w , txtz % src->h);
		put_pixel(dst, x, y, pix);
		++y;
	}
}


int				Scaler_Next(struct Scaler* i)
{
	for(i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca)
		i->result += i->bop;
	return i->result;
}

void 			textLine(int x, int y1, int y2, struct Scaler ty, unsigned txtx, SDL_Surface *surface, SDL_Surface *image)
{
	int 		*pix = (int*) surface->pixels;
	unsigned 	txty;

	y1 = clamp(y1, 0, H - 1);
	y2 = clamp(y2, 0, H - 1);
	pix += y1 * W + x;
	txtx %= image->w;
	for(int y = y1; y <= y2; ++y)
	{
		txty = Scaler_Next(&ty);
		*pix = get_pixel(image, txtx, txty % image->h);
		pix += W;
	}
}
