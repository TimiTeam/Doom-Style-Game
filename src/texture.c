#include "main_head.h"

static float		distance3D(t_vector a, t_vector b)
{
	float			dx;
	float 			dy;
	float 			dz;

	dx = b.x - a.x;
	dy = b.y - a.y;
	dz = b.z - a.z;
	dx *= dx;
	dy *= dy;
	dz *= dx;
	return (sqrt(dx * dx + dy * dy + dz * dz));
}


float		len_between_points(t_vector a, t_vector b)
{
	float			dx;
	float 			dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (sqrt((dx) * (dx) + (dy) * (dy)));
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

	if (!dst || !src || src->w == 0 || src->h == 0)
		return ;
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
		//	dist_to_light = distance3D((t_vector){light->pos.x, light->pos.y, sect->ceil},  (t_vector){mapx, mapz, sect->ceil});
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

void 			textLine(int x, int y1, int y2, struct Scaler ty, unsigned txtx, t_sector *sect, SDL_Surface *surface, SDL_Surface *image, t_vector tex_pos, float scaleL, float scaleH, t_light **light_source_arr)
{
	int 		*pix;
	y1 = clamp(y1, 0, H	- 1);
	y2 = clamp(y2, 0, H	- 1);
	Uint8 		r, g, b;
	float 		brightness;
	float 		dist_to_light;
	float 		scale;;
	float 		sect_height;
	t_light	*light;
	unsigned	i;
	
	if (!surface || !image || image->w == 0 || image->h == 0)
		return ;
	pix = (int*) surface->pixels;
	pix += y1 * W + x;
	scale = image->h * scaleH;
	sect_height = sect->ceil - sect->floor;
	txtx %= image->w;
	for(int y = y1; y <= y2; ++y)
    {
 		brightness = 0.3;
		float txty = Scaler_Next(&ty);
		if (txty < 0)
			break ;
 		float texZ = sect_height - txty / scale * sect_height;
		i = 0;
		while (i < MAX_LIGHT_SRC && (light = light_source_arr[i]))
		{
		//	dist_to_light = distance3D((t_vector){tex_pos.x, tex_pos.y, texZ / 2}, (t_vector){light->pos.x, light->pos.y, sect->ceil});
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