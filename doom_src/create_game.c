/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbujalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:55:45 by tbujalo           #+#    #+#             */
/*   Updated: 2019/10/15 15:55:46 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sectors.h"

static int		line_cmp_with_wall(char *line)
{
	if (line && ft_strncmp(line, "Walls", ft_strlen("Walls")) == 0)
		return (1);
	return (0);
}

static void		load_data_from_map(int fd, t_read_holder *h)
{
	t_vector	*vec;
	char		*line;

	vec = NULL;
	h->walls = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "Vectors", ft_strlen("Vectors")) == 0 && !vec)
			vec = get_vectors(fd, h->vect_count);
		else if (line_cmp_with_wall(line) && vec && !h->walls)
			h->walls = get_walls(fd, h, vec);
		else if (ft_strncmp(line, "Sectors", ft_strlen("Sectors")) == 0 &&
				h->walls && !h->all)
		{
			h->all = make_sectors_list(fd, h);
			h->light_source = create_all_light_source(h->all, h->light_count);
			fill_sectors_light_source(h->all, h->light_source, h->light_count);
		}
		else if (ft_strncmp(line, "Player", ft_strlen("Player")) == 0 && h->all)
			player_start_and_end(fd, h);
		ft_strdel(&line);
	}
	if (vec)
		ft_memdel((void**)&vec);
	ft_strdel(&line);
}

t_sector		*read_map(char *pth, t_read_holder *holder)
{
	int			fd;

	if ((fd = open(pth, O_RDONLY)) < 0)
		return (print_error_message_null("Error opening file:", pth));
	if (!get_count_struct_arrays(fd, &holder->vect_count, &holder->wall_count))
		return (print_error_message_null("Error reading map:", pth));
	load_data_from_map(fd, holder);
	delete_walls(holder->walls, holder->wall_count);
	close(fd);
	return (holder->all);
}
