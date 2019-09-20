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

void 			draw_image(SDL_Surface *screen, SDL_Surface *img, int x, int y, int width, int height)
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
	while (i < height)
	{
		j = 0;
		img_point.x = 0;
		while (j < width)
		{
			pix = get_pixel(img, (int)img_point.x, (int)img_point.y); 
			if (j + x > 0 && j + x < screen->w && i + y > 0 && i + y < screen->h && transparent_pixel(pix, img->format))
				put_pixel(screen, j + x, i + y, pix);
			img_point.x += step.x;
			j++;
		}
		img_point.y += step.y;
		i++;
	}
}

void    draw_crosshair(SDL_Surface *surface)
{
    t_point start1;
    t_point start2;
    t_point end1;
    t_point end2;
    start1.x = W / 2 - 30;
    start1.y = H / 2;
    end1.x = W / 2 + 30;
    end1.y = H / 2;
    start2.x = W / 2;
    start2.y = H / 2 - 30;
    end2.x = W / 2;
    end2.y = H / 2 + 30;
    line(surface, start1, end1, 0xffffffff);
    line(surface, start2, end2, 0xffffffff);
}

void 			draw_image_with_criteria(SDL_Surface *screen, SDL_Surface *img, int x, int y, int width, int height, t_draw_data data)
{
	int 		i;
	int			j;
	Uint32		pix;
	t_vector	img_point;
	t_vector	step;
	
	step.x = (float)img->w / width;
	step.y = (float)img->h / height;
	img_point = (t_vector){};
	i = 0;
	draw_crosshair(screen);
	while (i < height)
	{
		j = 0;
		img_point.x = 0;
		while (j < width)
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


void    		draw_enemy_sprite(t_item *obj, t_draw_data data, t_player player, SDL_Surface *surface)
{
	t_vector	ob_pos;
	t_vector	scale;
	float		tmp_x;
	t_point		screen_pos;
	float 		size;

	ob_pos = (t_vector){obj->pos.x - player.pos.x, obj->pos.y - player.pos.y};
	tmp_x = ob_pos.x;
	ob_pos.x = ob_pos.x * player.sin_angl - ob_pos.y * player.cos_angl;
	ob_pos.y = tmp_x * player.cos_angl + ob_pos.y * player.sin_angl;
	if (ob_pos.y <= 0)
		return ;
    scale.x = (W * m_hfov) / (ob_pos.y);
	scale.y = (H * m_vfov) / (ob_pos.y);
    ob_pos.x = player.half_win_size.x + (int)(-ob_pos.x * scale.x);
	ob_pos.y = player.half_win_size.y + (int)(-Yaw(obj->pos.z + data.diff_floor, ob_pos.y) * scale.y);
	size = 1000 / obj->dist_to_player * obj->size / 4.0f;
	if (obj->dist_to_player < 3)
		size = clamp(0, size, 1500);
	screen_pos.x = ob_pos.x - size / 2;
	screen_pos.y = ob_pos.y - size;
/*	t_point start = {x, y};
	t_point end = {x + size, y};
	line(surface, start, end, 0xffffffff);
	start = (t_point){x + size, y};
	end = (t_point){x + size, y + size};
	line(surface, start, end, 0xffffffff);
	start = (t_point){x + size, y + size};
	end = (t_point){x, y + size};
	line(surface, start, end, 0xffffffff);
	start = (t_point){x, y + size};
	end =(t_point) {x, y};
	line(surface, start, end, 0xffffffff);*/
	if (obj->type == enemy && player.shooting && obj->curr_state != die && player.current_gun->type != plasmagun && 
		data.start < player.half_win_size.x && data.end > player.half_win_size.x &&
			screen_pos.x < player.half_win_size.x && screen_pos.x + size > player.half_win_size.x && screen_pos.y < player.half_win_size.y && screen_pos.y + size > player.half_win_size.y)
	{
		obj->players_hit = 1;
	}
	t_animation	*anim;
	anim = &obj->states[obj->curr_state];
	
	if (anim->texture[(int)obj->curr_frame])
		draw_image_with_criteria(surface, anim->texture[(int)obj->curr_frame], screen_pos.x, screen_pos.y, size, size, data);
}


int						move_enemy(t_item *enemy, t_vector step)
{		
	t_wall				**wall;
	int					i;
	t_sector			*sector;
	t_sector			*next;

	if (!enemy)
		return (0);
	sector = enemy->sector;
	wall = sector->wall;
	i = 0;
	while (i < sector->n_walls)
	{
		if(IntersectBox(enemy->pos.x, enemy->pos.y, step.x, step.y, wall[i]->start.x, wall[i]->start.y, wall[i]->end.x, wall[i]->end.y)
        && PointSide(step.x, step.y, wall[i]->start.x, wall[i]->start.y, wall[i]->end.x, wall[i]->end.y) < 0)
        {
			if (wall[i]->type != empty_wall)
				return (0);
			if (wall[i]->sectors[0] && sector->sector != wall[i]->sectors[0]->sector)
				next = wall[i]->sectors[0];
			else if (wall[i]->sectors[1] && sector->sector != wall[i]->sectors[1]->sector)
				next = wall[i]->sectors[1];
			from_list_to_another_list(&enemy->sector->items, &next->items, enemy);
			enemy->sector = next;
			break;
        }
		i++;
	}
	return (1);
}

void    		move_enemy_to_player(t_item *enemy, t_vector player_pos)
{
	t_vector	step;
	t_vector	new_pos;
	float		dist;
	float 		dx;

	if (!enemy)
		return ;
	step = (t_vector){enemy->pos.x - player_pos.x, enemy->pos.y - player_pos.y};
	dist = sqrtf(step.x * step.x + step.y * step.y);
	dx = (dist - 0.3f) / dist;
	new_pos.x = step.x * dx + player_pos.x;
	new_pos.y = step.y * dx + player_pos.y;
	if (move_enemy(enemy, new_pos))
	{
		enemy->pos.x = new_pos.x;
		enemy->pos.y = new_pos.y;
	}
}

void   draw_projectile(t_projectile *proj, t_draw_data data, t_player player, SDL_Surface *surface)
{
	t_vector ob_pos;
	t_vector scale;
	float  tmp_x;
	t_vector screen_pos;
	float   size;
	ob_pos = (t_vector){proj->pos.x - player.pos.x, proj->pos.y - player.pos.y};
	tmp_x = ob_pos.x;
	ob_pos.x = ob_pos.x * player.sin_angl - ob_pos.y * player.cos_angl;
	ob_pos.y = tmp_x * player.cos_angl + ob_pos.y * player.sin_angl;
	if (ob_pos.y <= 0)
	 return ;
	   scale.x = (W * m_hfov) / (ob_pos.y);
	scale.y = (H * m_vfov) / (ob_pos.y);
	   ob_pos.x = player.half_win_size.x + (int)(-ob_pos.x * scale.x);
	ob_pos.y = player.half_win_size.y + (int)(-Yaw(proj->pos.z - player.pos.z, ob_pos.y) * scale.y);
	float dist = len_between_points(player.pos, proj->pos);
	screen_pos.x = ob_pos.x - 1000 / dist / 2;
	screen_pos.y = ob_pos.y - 1000 / dist / 2;
	size = 1000 /  dist;
	if (dist < 3)
	 return ;
	draw_image_with_criteria(surface, proj->sprite, screen_pos.x, screen_pos.y, size, size, data);
}