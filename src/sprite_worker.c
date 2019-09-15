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


void    		draw_enemy_sprite(t_item *obj, t_draw_data data, t_player player, SDL_Surface *surface)
{
	t_vector	ob_pos;
	t_vector	scale;
	float		dist;
	float		tmp_x;

	dist = obj->dist_to_player;
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
	float x = ob_pos.x - obj->size / dist / 2;
	float y = ob_pos.y - obj->size / dist / 2;
	float size = obj->size / dist;
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
	if (obj->type == enemy && player.shooting && obj->state != die && data.start < player.half_win_size.x && data.end > player.half_win_size.x &&  x < player.half_win_size.x && x + size > player.half_win_size.x && y < player.half_win_size.y && y + size > player.half_win_size.y)
	{
		obj->hp -= player.current_gun->damage;
		if (obj->hp <= 0){
			obj->state = die;
		}
		else{
			obj->state = taking_damage;
			obj->is_dying = 5;
		}
	
	}
	if (obj->state == waiting && obj->waiting.texture[0])
		draw_image_with_criteria(surface, obj->waiting.texture[(int)obj->waiting.current_text], ob_pos.x - obj->size / dist / 2, ob_pos.y - obj->size / dist / 2,
				obj->size / dist, obj->size / dist, data);
	else if (obj->state == walk && obj->walk.texture[(int)obj->walk.current_text])
		draw_image_with_criteria(surface, obj->walk.texture[(int)obj->walk.current_text], ob_pos.x - obj->size / dist / 2, ob_pos.y - obj->size / dist / 2,
				obj->size / dist, obj->size / dist, data);
	else if (obj->state == action)
		draw_image_with_criteria(surface, obj->action.texture[(int)obj->action.current_text], ob_pos.x - obj->size / dist / 2, ob_pos.y - obj->size / dist / 2,
				obj->size / dist, obj->size / dist, data);
	else if (obj->state == die)
		draw_image_with_criteria(surface, obj->die.texture[(int)obj->die.current_text], ob_pos.x - obj->size / dist / 2, ob_pos.y - obj->size / dist / 2,
				obj->size / dist, obj->size / dist, data);
}

void 					from_list_to_another_list(t_sector *current_sector, t_sector *next_sector, t_item *elem)
{
	t_item				*tmp;
	t_item				*curr;

	curr = current_sector->enemies;
	tmp = curr;

	if (curr == elem)
	{
		current_sector->enemies = elem->next;
		elem->next = NULL;
		if (next_sector->enemies)
			add_next_item(next_sector->enemies, elem);
		else
			next_sector->enemies = elem;
		return;
	}
	while (curr && (curr = curr->next))
	{
		if (curr == elem)
		{
			tmp->next = curr->next;
			elem->next = NULL;
			if (next_sector->enemies)
				add_next_item(next_sector->enemies, elem);
			else
				next_sector->enemies = elem;
			return;
		}
		tmp = curr;
	}
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
			from_list_to_another_list(enemy->sector, next, enemy);
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
		//printf("dist = %f; old pos %f %f new pos %f %f\n\n",dist, enemy->pos.x, enemy->pos.y,  new_pos.x, new_pos.y);
		enemy->pos.x = new_pos.x;
		enemy->pos.y = new_pos.y;
	}
}