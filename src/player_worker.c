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

int 			set_default_pos(t_sector *sector, t_vector *pos,
								unsigned sect_id, unsigned *player_sec)
{
	t_sector 	*sect;
	t_wall		**wall;
	t_vector	vect;
	int			i;
	
	if (!sector)
		return (0);
	sect = sector;
	while (sect)
	{
		if (((sect_id == 0 && sect->sector == 0) || (!sect->next && sect_id)) && 
			(wall = sect->wall))
		{
			i = 0;
			*player_sec = sect->sector;
			while (i < sect->n_walls && wall[i])
			{
				vect = sect->wall[i]->start;
				vect.x += 2;
				vect.y += 2;
				if (dot_inside_sector(vect, wall, sect->n_walls))
				{
					pos->x = vect.x;
					pos->y = vect.y;
					return (1);
				}
				i++;
			}
		}
		sect = sect->next;
	}
	return (0);
}

unsigned char	correct_position_in_sector(t_vector pos, t_sector *supposed)
{
	if (!supposed)
		return (0);
	return (dot_inside_sector(pos, supposed->wall, supposed->n_walls));	
}

unsigned char	check_correct_satrt_end(t_read_holder *holder, int start, int end, char *line)
{
	t_sector	*s_sect;
	t_sector	*e_sect;
	int			res;
	int			res2;

	res = 1;
	res2 = 1;
	e_sect = 0;
	if (!holder)
		return (0);
	if(!(s_sect = get_player_sector(holder->all, holder->player_sector_id)) ||
		!(e_sect = get_player_sector(holder->all, holder->player_end_sect)))
		res2 = 0;
	if (!start || !correct_position_in_sector(holder->player_start, s_sect))
	{
		set_default_pos(holder->all, &holder->player_start, 0, &holder->player_sector_id);
		res = print_error_message("Wrong start position, use default!", line);
	}
	if (!end || !correct_position_in_sector(holder->player_end, e_sect))
	{
		if (!set_default_pos(holder->all, &holder->player_end, 1, &holder->player_end_sect))
			print_error_message("Can't find ", "End position");
		res2 = print_error_message("Wrong end position, use default!", line);
	}
	return (res * res2);
}

int				player_start_and_end(int fd, t_read_holder *holder)
{
	char 		*line;
	int 		s;
	int			e;
	int			ret;

	s = 0;
	e = 0;
	ret = 1;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "0)", 2) == 0)
			s = get_player_pos(line, &holder->player_start, &holder->player_sector_id);
		if (ft_strncmp(line, "1)", 2) == 0)
			e = get_player_pos(line, &holder->player_end, &holder->player_end_sect);
		ft_strdel(&line);
	}
	ret = check_correct_satrt_end(holder, s, e, line);
	ft_strdel(&line);
	return (ret);
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
	return (player);
}
