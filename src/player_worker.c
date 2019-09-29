/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:10:50 by ohavryle          #+#    #+#             */
/*   Updated: 2019/09/29 05:10:51 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

void			free_player(t_player *player)
{
	int			i;

	if (!player)
		return ;
	delete_items_list(player->inventar);
	i = 0;
	while (i < 3)
	{
		if (!player->gun[i])
		{
			i++;
			continue;
		}
		ft_memdel((void**)&player->gun[i]);
		i++;
	}
	if (player->sky)
		SDL_FreeSurface(player->sky);
	ft_memdel((void**)&player);
}

int				get_player_pos(int fd, t_vector *player_pos, int *player_sec_id)
{
	char		*line;
	char		*skiped;
	unsigned	p;
	int			ret;

	line = NULL;
	ret = 1;
	if (get_next_line(fd, &line) > 0)
	{
		p = get_numbers(&player_pos->x, &player_pos->y,
					',', (skiped = skip_row_number(line)));
		*player_sec_id = get_num_from_str(&skiped[p]);
	}
	else
		ret = print_error_message("player pos is undefine at row", line);
	ft_strdel(&line);
	return (ret);
}

t_sector		*get_player_sector(t_sector *sectors, int sec_num)
{
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
	*player = (t_player){NULL};
	player->pos = (t_vector){pos_x, pos_y, 0};
	player->curr_map = -1;
	player->half_win_size = (t_point){win_size.x / 2, win_size.y / 2};
	player->yaw = 0;
	player->m_vfov = 0.2f;
	player->m_hfov = 0.73f * H / W;
	player->hfov = win_size.x * player->m_hfov;
	player->vfov = win_size.y * player->m_vfov;
	player->fall = 0;
	player->speed = 0.6f;
	player->inventar = NULL;
	player->height = EyeHeight;
	player->health = 100;
	return (player);
}
