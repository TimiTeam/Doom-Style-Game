/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_player_pos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 21:46:31 by tbujalo           #+#    #+#             */
/*   Updated: 2019/10/15 21:46:52 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_head.h"

static int				is_it_good_place(t_sector *sect, t_wall wall,
		t_vector *new_pos)
{
	t_vector			vect;

	vect = wall.start;
	vect.x += 2;
	vect.y += 2;
	if (dot_inside_sector(vect, sect->wall, sect->n_walls))
	{
		new_pos->x = vect.x;
		new_pos->y = vect.y;
		return (1);
	}
	return (0);
}

static int				set_default_pos(t_sector *sect, t_vector *pos,
								unsigned sect_id, unsigned *player_sec)
{
	t_wall				**wall;
	int					i;

	if (!sect)
		return (0);
	while (sect)
	{
		if (((sect_id == 0 && sect->sector == 0) || (!sect->next && sect_id))
			&& (wall = sect->wall))
		{
			i = 0;
			*player_sec = sect->sector;
			while (i < sect->n_walls && wall[i])
			{
				if (is_it_good_place(sect, *wall[i], pos))
					return (1);
				i++;
			}
		}
		sect = sect->next;
	}
	return (0);
}

unsigned char			correct_position_in_sector(t_vector pos,
		t_sector *supposed)
{
	if (!supposed)
		return (0);
	return (dot_inside_sector(pos, supposed->wall, supposed->n_walls));
}

static unsigned char	check_correct_satrt_end(t_read_holder *h, int start,
				int end, char *line)
{
	t_sector			*s_sect;
	t_sector			*e_sect;
	int					res;
	int					res2;

	res = 1;
	res2 = 1;
	e_sect = 0;
	if (!h)
		return (0);
	if (!(s_sect = get_player_sector(h->all, h->player_sector_id)) ||
		!(e_sect = get_player_sector(h->all, h->player_end_sect)))
		res2 = 0;
	if (!start || !correct_position_in_sector(h->player_start, s_sect))
	{
		set_default_pos(h->all, &h->player_start, 0, &h->player_sector_id);
		res = print_error_message("Wrong start position, use default!", line);
	}
	if (!end || !correct_position_in_sector(h->player_end, e_sect))
	{
		if (!set_default_pos(h->all, &h->player_end, 1, &h->player_end_sect))
			print_error_message("Can't find ", "End position");
		res2 = print_error_message("Wrong end position, use default!", line);
	}
	return (res * res2);
}

int						player_start_and_end(int fd, t_read_holder *h)
{
	char				*line;
	int					s;
	int					e;
	int					ret;

	s = 0;
	e = 0;
	ret = 1;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "0)", 2) == 0)
			s = get_player_pos(line, &h->player_start, &h->player_sector_id);
		if (ft_strncmp(line, "1)", 2) == 0)
			e = get_player_pos(line, &h->player_end, &h->player_end_sect);
		ft_strdel(&line);
	}
	ret = check_correct_satrt_end(h, s, e, line);
	ft_strdel(&line);
	return (ret);
}
