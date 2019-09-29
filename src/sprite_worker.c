/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:11:39 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:11:40 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

int				enemy_hit(t_player player, t_draw_data data,
							t_point screen_pos, t_point size)
{
	if (player.shooting && player.current_gun
		&& player.current_gun->type != plasmagun
		&& player.current_gun->state < 2
		&& data.start < player.half_win_size.x
		&& data.end > player.half_win_size.x
		&& screen_pos.x < player.half_win_size.x
		&& screen_pos.x + size.x > player.half_win_size.x
		&& screen_pos.y < player.half_win_size.y
		&& screen_pos.y + size.y > player.half_win_size.y)
		return (1);
	return (0);
}

t_point			calculate_size(t_item *obj, t_player player,
								t_vector *ob_pos, t_draw_data data)
{
	t_vector	scale;
	t_point		size;
	float		tmp_x;

	*ob_pos = (t_vector){obj->pos.x - player.pos.x, obj->pos.y - player.pos.y};
	tmp_x = ob_pos->x;
	ob_pos->x = ob_pos->x * player.sin_angl - ob_pos->y * player.cos_angl;
	ob_pos->y = tmp_x * player.cos_angl + ob_pos->y * player.sin_angl;
	if (ob_pos->y <= 0)
		return ((t_point){-1, -1});
	scale.x = (W * m_hfov) / (ob_pos->y);
	scale.y = (H * m_vfov) / (ob_pos->y);
	ob_pos->x = player.half_win_size.x + (int)(-ob_pos->x * scale.x);
	ob_pos->y = player.half_win_size.y
	+ (int)(-Yaw(obj->pos.z + data.diff_floor, ob_pos->y) * scale.y);
	size.x = (obj->size.x / obj->dist_to_player) * 30;
	size.y = (obj->size.y / obj->dist_to_player) * 30;
	return (size);
}

void			draw_enemy_sprite(t_item *obj, t_draw_data data,
										t_player player, SDL_Surface *surface)
{
	t_point		size;
	t_point		screen_pos;
	t_animation	*anim;
	t_vector	ob_pos;

	size = calculate_size(obj, player, &ob_pos, data);
	if (size.x <= 0 || size.y <= 0)
		return ;
	if (obj->dist_to_player < 3)
	{
		size.x = clamp(0, size.x, 1500);
		size.y = clamp(0, size.y, 1500);
	}
	screen_pos.x = ob_pos.x - size.x / 2;
	screen_pos.y = ob_pos.y - size.y;
	if (obj->curr_state != die && enemy_hit(player, data, screen_pos, size))
		obj->players_hit = 1;
	anim = &obj->states[obj->curr_state];
	if (anim->texture[(int)obj->curr_frame])
		draw_image_with_criteria(surface,
		anim->texture[(int)obj->curr_frame], (t_rect){screen_pos, size}, data);
}

void			draw_projectile(t_projectile *proj, t_draw_data data,
								t_player player, SDL_Surface *surface)
{
	float		size;
	float		tmp_x;
	t_vector	ob_pos;
	t_vector	scale;
	t_point		screen_pos;

	ob_pos = (t_vector){proj->pos.x - player.pos.x, proj->pos.y - player.pos.y};
	tmp_x = ob_pos.x;
	ob_pos.x = ob_pos.x * player.sin_angl - ob_pos.y * player.cos_angl;
	ob_pos.y = tmp_x * player.cos_angl + ob_pos.y * player.sin_angl;
	if (ob_pos.y <= 0)
		return ;
	scale.x = (W * m_hfov) / (ob_pos.y);
	scale.y = (H * m_vfov) / (ob_pos.y);
	ob_pos.x = player.half_win_size.x + (int)(-ob_pos.x * scale.x);
	ob_pos.y = player.half_win_size.y
	+ (int)(-Yaw(proj->pos.z - player.pos.z, ob_pos.y) * scale.y);
	tmp_x = len_between_points(player.pos, proj->pos);
	if (tmp_x < 3)
		return ;
	screen_pos.x = ob_pos.x - 1000 / tmp_x / 2;
	screen_pos.y = ob_pos.y - 1000 / tmp_x / 2;
	size = 1000 / tmp_x;
	draw_image_with_criteria(surface, proj->sprite,
	(t_rect){screen_pos, (t_point){size, size}}, data);
}
