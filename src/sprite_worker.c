#include "main_head.h"



void    		draw_enemy_sprite(t_item *obj, t_draw_data data, t_player player, SDL_Surface *surface)
{
	t_vector	ob_pos;
	t_vector	scale;
	t_point		size;
	float		tmp_x;
	t_point		screen_pos;

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
	size.x = (obj->size.x / obj->dist_to_player) * 30;
	size.y = (obj->size.y / obj->dist_to_player) * 30;
	if (obj->dist_to_player < 3)
	{
		size.x = clamp(0, size.x, 1500);
		size.y = clamp(0, size.y, 1500);
	}
	screen_pos.x = ob_pos.x - size.x / 2;
	screen_pos.y = ob_pos.y - size.y;
	if (player.shooting && player.current_gun && player.current_gun->type != plasmagun && obj->curr_state != die && data.start < player.half_win_size.x && data.end > player.half_win_size.x &&
			screen_pos.x < player.half_win_size.x && screen_pos.x + size.x > player.half_win_size.x && screen_pos.y < player.half_win_size.y && screen_pos.y + size.y > player.half_win_size.y)
	{
		obj->players_hit = 1;
	}
	t_animation	*anim;
	anim = &obj->states[obj->curr_state];
	
	if (anim->texture[(int)obj->curr_frame])
		draw_image_with_criteria(surface, anim->texture[(int)obj->curr_frame], screen_pos, size, data);
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
			if (enemy->pos.z + 8 > next->ceil)
				return (0);
			printf("enemy->pos.z  %f, next->ceil %f\n", enemy->pos.z, next->ceil);
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
	dx = (dist - enemy->speed) / dist;
	new_pos.x = step.x * dx + player_pos.x;
	new_pos.y = step.y * dx + player_pos.y;
	if (move_enemy(enemy, new_pos))
	{
		enemy->pos.x = new_pos.x;
		enemy->pos.y = new_pos.y;
	}
}

void   			draw_projectile(t_projectile *proj, t_draw_data data, t_player player, SDL_Surface *surface)
{
	t_vector	ob_pos;
	t_vector	scale;
	float		tmp_x;
	t_point		screen_pos;
	float		size;

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
	if (dist < 3)
		return ;
	screen_pos.x = ob_pos.x - 1000 / dist / 2;
	screen_pos.y = ob_pos.y - 1000 / dist / 2;
	size = 1000 / dist;
	draw_image_with_criteria(surface, proj->sprite, screen_pos, (t_point){size, size}, data);
}