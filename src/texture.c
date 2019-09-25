#include "main_head.h"

static float		distance3D(t_vector a, t_vector b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void 			draw_floor_or_ceil(SDL_Surface *dst, SDL_Surface *src, int x, int y, int end_y, int diff_height, t_player player, t_vector lightSource, t_sector *sect)
{
	float		mapx;
	float		mapz;
	float		tmp;
	Uint32		*pix;
	unsigned 	tx;
	unsigned	txtz;

	while(y < end_y)
	{
		mapz = diff_height * H * m_vfov / ((h_h - y) - H * m_vfov * player.yaw);
		mapx = mapz * (h_w - x) / (m_hfov * W);
		tmp = mapx;	
	
		mapx = mapz * player.cos_angl + tmp * player.sin_angl + player.pos.x;
		mapz = mapz * player.sin_angl - tmp * player.cos_angl + player.pos.y;

		tx = mapx * 50;
		txtz = mapz * 50;
		//tx = tx >= src->w ? src->w - 1 : tx;
		//txtz = txtz >= src->h ? src->h - 1 : txtz;
	/*
		pix = get_pixel(src, tx % src->w , txtz % src->h);
		put_pixel(dst, x, y, pix);*/
		float ceilDist = distance3D((t_vector){lightSource.x, lightSource.y, lightSource.z},  (t_vector){mapx, mapz, sect->ceil});
   // 	float floorDist = distance3D((t_vector){lightSource.x, lightSource.y, lightSource.z}, (t_vector){mapx, mapz, sect->floor});
    //	if (hei == yceil/* && ceilDist < maxDist*/){
    	 Uint8 r;
    	 Uint8 g;
    	 Uint8 b;
    	 float brightness = 0.2;
    	/* for (int i = 0; i < projCount; i++){ 
    	  if (!projectiles[i].alive)
    	   continue ;
    	 float dist_to_proj = distance3D(projectiles[i].pos.x, projectiles[i].pos.y, projectiles[i].pos.z,  mapx, mapz, sect->ceil);
    	 brightness += 1.0f - (clamp(dist_to_proj, 0, maxDist) - 0) / (maxDist - 0.0f) * (1.0f - 0.0f) + 0.0f;
    	 }*/
    	 float dist_to_light = ceilDist;
    	 brightness += 1.0f - clamp(dist_to_light, 0, 5.3f) / 5.3f;
    	 SDL_GetRGB(get_pixel(src, tx % src->w, txtz % src->h), src->format, &r, &g, &b);
    	/* surfacePix[y * W + x] */ put_pixel(dst, x, y, SDL_MapRGB(src->format, min(r * brightness, 255), min(g * brightness, 255), min(b * brightness, 255)));
    //	}
    //	else if (hei == yfloor/* && floorDist < maxDist*/){
    /*	 Uint8 r;
    	 Uint8 g;
    	 Uint8 b;
    	 float brightness = 0.3;
    	 for (int i = 0; i < projCount; i++){ 
    	  if (!projectiles[i].alive)
    	   continue ;
    	 float dist_to_proj = distance3D(projectiles[i].pos.x, projectiles[i].pos.y, projectiles[i].pos.z,  mapx, mapz, sect->floor);
    	 brightness += 1.5f - (clamp(dist_to_proj, 0, maxDist) - 0) / (maxDist - 0.0f) * (1.5f - 0.0f) + 0.0f;
    	 }
    	 float dist_to_light = floorDist;
    	 brightness += 1.5f - (clamp(dist_to_light, 0, maxDist) - 0) / (maxDist - 0.0f) * (1.5f - 0.0f) + 0.0f;
    	 SDL_GetRGB(getpixel(floorTexture, tx % floorTexture->w, txtz % floorTexture->h), floorTexture->format, &r, &g, &b);
    	 surfacePix[y * W + x] = SDL_MapRGB(floorTexture->format, clamp(r * brightness, 0, 255), clamp(g * brightness, 0, 255), clamp(b * brightness, 0, 255));
    	}*/
		++y;
	}
}


int				Scaler_Next(struct Scaler* i)
{
	for(i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca)
		i->result += i->bop;
	return i->result;
}
/*
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
}*/

void 			textLine(int x, int y1, int y2, struct Scaler ty, unsigned txtx, t_sector *sect, SDL_Surface *surface, SDL_Surface *image, t_vector tex_pos, float scaleL, float scaleH, float maxDist, t_vector lightSource)
{
	int			*pix = (int*) surface->pixels;
	Uint8 r, g, b;
	float brightness;
	float scale = image->h * scaleH;
	float sect_height = sect->ceil - sect->floor;
	
	y1 = clamp(y1, 0, H	- 1);
	y2 = clamp(y2, 0, H	- 1);
	pix += y1 * W + x;
	txtx %= image->w;
	for(int y = y1; y <= y2; ++y)
    {
 		brightness = 1;
		float txty = Scaler_Next(&ty);
 		float texZ = sect_height - txty / scale * sect_height;
		 if (txty < 0)
		 	continue ;
 		/*for (int i = 0; i < projCount; i++){
 		 if (!projectiles[i].alive)
 		  continue ;
 		 float dist_to_proj = distance3D(tex_pos.x, tex_pos.y, texZ / 2.737, projectiles[i].pos.x, projectiles[i].pos.y, projectiles[i].pos.z / 2.737);
 		 brightness += 1.0f - (clamp(dist_to_proj, 0, maxDist) - 0) / (maxDist - 0.0f) * (1.0f - 0.0f) + 0.0f;
 		}*/
		float dist_to_light = distance3D((t_vector){tex_pos.x, tex_pos.y, texZ / 2}, (t_vector){lightSource.x, lightSource.y, lightSource.z / 2});
		brightness += 1.0f - clamp(dist_to_light, 0, maxDist) / maxDist;
		SDL_GetRGB(get_pixel(image, txtx, (int)txty % image->h), image->format, &r, &g, &b);
 		*pix = SDL_MapRGB(image->format, min(r * brightness, 255), min(g * brightness, 255), min(b * brightness, 255));
 		pix += W;
    }
}