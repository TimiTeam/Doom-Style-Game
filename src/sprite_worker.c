#include "main_head.h"

int		transparent_pixel(Uint32 pixel, SDL_PixelFormat *format)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;
	Uint8	a;

	SDL_GetRGBA(pixel, format, &r, &g, &b, &a);
	if (a != 0)
		return (1);
	return (0);
}

void 			draw_scaled_image(SDL_Surface *screen, SDL_Surface *img, int x, int y, int width, int height, t_draw_data data)
{
	int 		i;
	int		j;
	Uint32		pix;
	t_vector	img_point;
	t_vector	step;
	
	step.x = (float)img->w / width;
	step.y = (float)img->h / height;
	img_point = (t_vector){};
	i = 0;
	while (i < width)
	{
		j = 0;
		img_point.x = 0;
		while (j < height)
		{
			pix = get_pixel(img, (int)img_point.x, (int)img_point.y); 
			if (j + x > data.start && j + x < data.end && i + y > data.ytop[j + x] && i + y < data.ybottom[j + x]
					&& transparent_pixel(pix, img->format))
				put_pixel(screen, j + x, i + y, pix);
			img_point.x += step.x;
			j++;
		}
		img_point.y += step.y;
		i++;
	}
}	

static float            len_between_points(t_vector a, t_vector b)
{
        return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}


void    		draw_enemy_sprite(t_item obj, t_draw_data data, t_player player, SDL_Surface *surface)
{
	t_vector	ob_pos;
	t_vector	scale;
	float		dist;
	float		tmp_x;

	dist = len_between_points(obj.pos, player.pos);
	ob_pos = (t_vector){obj.pos.x - player.pos.x, obj.pos.y - player.pos.y};
	tmp_x = ob_pos.x;
	ob_pos.x = ob_pos.x * player.sin_angl - ob_pos.y * player.cos_angl;
	ob_pos.y = tmp_x * player.cos_angl + ob_pos.y * player.sin_angl;
        
	if (ob_pos.y <= 0)
		return ;
       	scale.x = (W * m_hfov) / (ob_pos.y);
	scale.y = (H * m_vfov) / (ob_pos.y);
        ob_pos.x = player.half_win_size.x + (int)(-ob_pos.x * scale.x);
	ob_pos.y = player.half_win_size.y + (int)(-Yaw(5 - (player.height + player.jump) , ob_pos.y) * scale.y);
        
//	printf("dist = %f and ", dist);
 
	draw_scaled_image(surface, obj.id_text[0], ob_pos.x - obj.size / dist / 2, ob_pos.y - obj.size / dist / 2,
			obj.size / dist, obj.size / dist, data);
}
