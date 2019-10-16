/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:10:50 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/30 16:00:36 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void			free_player(t_player *player)
{
	if (!player)
		return ;
	delete_items_list(player->inventar);
	if (player->damage_sound)
		Mix_FreeChunk(player->damage_sound);
	if (player->ambient)
		Mix_FreeChunk(player->ambient);
	if (player->door_sound)
		Mix_FreeChunk(player->door_sound);
	if (player->get_item)
		Mix_FreeChunk(player->get_item);
	ft_memdel((void**)&player);
}

int				get_player_pos(char *line, t_vector *player_pos,
								unsigned *player_sec_id)
{
	char		*skiped;
	unsigned	p;

	p = 0;
	if (line)
	{
		p = get_numbers(&player_pos->x, &player_pos->y,
					',', (skiped = skip_row_number(line)));
		*player_sec_id = get_num_from_str(&skiped[p]);
	}
	return (p);
}

t_sector		*get_player_sector(t_sector *all, int sec_num)
{
	t_sector	*sectors;

	sectors = all;
	while (sectors)
	{
		if (sectors->sector == sec_num)
			return (sectors);
		sectors = sectors->next;
	}
	return (NULL);
}

t_player		*new_t_player(int pos_x, int pos_y, t_point win_size)
{
	t_player	*player;

	player = (t_player*)malloc(sizeof(t_player));
	ft_memset(player, 0, sizeof(t_player));
	player->pos = (t_vector){pos_x, pos_y, 0};
	player->curr_map = -1;
	player->half_win_size = (t_point){win_size.x / 2, win_size.y / 2};
	player->yaw = 0;
	player->m_vfov = 0.2f;
	player->m_hfov = 0.73f * H / W;
	player->hfov = win_size.x * player->m_hfov;
	player->vfov = win_size.y * player->m_vfov;
	player->fall = 0;
	player->speed = 0.5f;
	player->inventar = NULL;
	player->height = EYEHEIGHT;
	player->health = 100;
	player->damage_sound = Mix_LoadWAV("sounds/player_damaged.wav");
	player->ambient = Mix_LoadWAV("sounds/ambient.wav");
	player->door_sound = Mix_LoadWAV("sounds/door_sound.wav");
	player->get_item = Mix_LoadWAV("sounds/oh_yeah.wav");
	return (player);
}
