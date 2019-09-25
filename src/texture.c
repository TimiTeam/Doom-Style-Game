#include "main_head.h"

static float		distance3D(t_vector a, t_vector b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}


static float		len_between_points(t_vector a, t_vector b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void 			draw_floor_or_ceil(SDL_Surface *dst, SDL_Surface *src, int x, int y, int end_y, int diff_height, t_player player, t_sector *sect, t_light **light_source_arr)
{
	float		mapx;
	float		mapz;
	float		tmp;
	Uint32		*pix;
	unsigned 	tx;
	unsigned	txtz;
	float 		dist_to_light;
	Uint8 		r;
	Uint8 		g;
	Uint8 		b;
	float 		brightness;
	unsigned	i;
	t_light		*light;

	while(y < end_y)
	{
		brightness = 0.3;
		mapz = diff_height * H * m_vfov / ((h_h - y) - H * m_vfov * player.yaw);
		mapx = mapz * (h_w - x) / (m_hfov * W);
		tmp = mapx;			
		mapx = mapz * player.cos_angl + tmp * player.sin_angl + player.pos.x;
		mapz = mapz * player.sin_angl - tmp * player.cos_angl + player.pos.y;
		tx = mapx * 50;
		txtz = mapz * 50;
		i = 0;
		while (i < MAX_LIGHT_SRC && (light = light_source_arr[i]))
		{
			//dist_to_light = distance3D((t_vector){light->pos.x, light->pos.y, sect->ceil},  (t_vector){mapx, mapz, sect->ceil});
			dist_to_light = len_between_points(light->pos,  (t_vector){mapx, mapz});
			if (dist_to_light < light->max_dist)
		 		brightness += 1.0f - clamp(dist_to_light, 0, light->max_dist) / light->max_dist;
			i++;
		}
		SDL_GetRGB(get_pixel(src, tx % src->w, txtz % src->h), src->format, &r, &g, &b);
		put_pixel(dst, x, y, SDL_MapRGB(src->format, min(r * brightness, 255), min(g * brightness, 255), min(b * brightness, 255)));
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

void 			textLine(int x, int y1, int y2, struct Scaler ty, unsigned txtx, t_sector *sect, SDL_Surface *surface, SDL_Surface *image, t_vector tex_pos, float scaleL, float scaleH, t_light **light_source_arr)
{
	int 		*pix = (int*) surface->pixels;
	y1 = clamp(y1, 0, H	- 1);
	y2 = clamp(y2, 0, H	- 1);
	pix += y1 * W + x;
	Uint8 r, g, b;
	float brightness;
	float dist_to_light;
	float scale = image->h * scaleH;
	float sect_height = sect->ceil - sect->floor;
	t_light	*light;
	unsigned	i;
	
	txtx %= image->w;
	for(int y = y1; y <= y2; ++y)
    {
 		brightness = 0.3;
		float txty = Scaler_Next(&ty);
		if (txty < 0)
			break ;
 		float texZ = sect_height - txty / scale * sect_height;
 		/*for (int i = 0; i < projCount; i++){
 		 if (!projectiles[i].alive)
 		  continue ;
 		 float dist_to_proj = distance3D(tex_pos.x, tex_pos.y, texZ / 2.737, projectiles[i].pos.x, projectiles[i].pos.y, projectiles[i].pos.z / 2.737);
 		 brightness += 1.0f - (clamp(dist_to_proj, 0, maxDist) - 0) / (maxDist - 0.0f) * (1.0f - 0.0f) + 0.0f;
 		}*//*
		dist_to_light = distance3D((t_vector){tex_pos.x, tex_pos.y, texZ / 2}, (t_vector){lightSource.x, lightSource.y, lightSource.z});
		if (dist_to_light < maxDist)
			brightness += 1.0f - clamp(dist_to_light, 0, maxDist) / maxDist;*/
		i = 0;
		while (i < MAX_LIGHT_SRC && (light = light_source_arr[i]))
		{
			//dist_to_light = distance3D((t_vector){tex_pos.x, tex_pos.y, texZ / 2}, (t_vector){light->pos.x, light->pos.y, sect->ceil});
			dist_to_light = len_between_points(tex_pos, light->pos);
			if (dist_to_light < light->max_dist)
				brightness += 1.0f - clamp(dist_to_light, 0, light->max_dist) / light->max_dist;
			i++;
		}
		SDL_GetRGB(get_pixel(image, txtx, (int)txty % image->h), image->format, &r, &g, &b);
 		*pix = SDL_MapRGB(image->format, min(r * brightness, 255), min(g * brightness, 255), min(b * brightness, 255));
 		pix += W;
    }
}