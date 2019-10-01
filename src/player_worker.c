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

int				get_player_pos(char *line, t_vector *player_pos,
								unsigned *player_sec_id)
{
	char		*skiped;
	unsigned	p;

	if (line)
	{
		p = get_numbers(&player_pos->x, &player_pos->y,
					',', (skiped = skip_row_number(line)));
		*player_sec_id = get_num_from_str(&skiped[p]);
	}
	return (1);
}

int 			set_default_pos(t_sector *sector, t_vector *pos,
								unsigned sect_id, unsigned *player_sec)
{
	t_sector 	*sect;
	int 		ret;


	ret = 0;	
	if (!sector)
		return (0);
	sect = sector;
	while (sect)
	{
		if ((sect_id == 0 || (!sect->next && sect_id)) && sect->wall[0])
		{
			ret = 1;
			*player_sec = sect->sector;
			pos->x = sect->wall[0]->start.x;
			pos->y = sect->wall[0]->start.y;
			break ;
		}
		sect = sect->next;
	}
	return (ret);
}

int				player_start_and_end(int fd, t_read_holder *holder)
{
	char 		*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "0)", 2) == 0)
			get_player_pos(line, &holder->player_start, &holder->player_sector_id);
		if (ft_strncmp(line, "1)", 2) == 0)
			get_player_pos(line, &holder->player_end, &holder->player_end_sect);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (holder->player_start.x == 0 && holder->player_start.y == 0)
	{
		set_default_pos(holder->all, &holder->player_start, 0, &holder->player_sector_id);
		return (print_error_message("Value undefine at row, use default!", line));
	}
	if (holder->player_end.x == 0 && holder->player_end.y == 0)
	{
		set_default_pos(holder->all, &holder->player_end, 1, &holder->player_end_sect);
		return (print_error_message("Value undefine, use default!", line));
	}
	return (1);
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
	player->height = EYEHEIGHT;
	player->health = 100;
	return (player);
}
